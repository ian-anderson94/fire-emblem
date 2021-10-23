#include "InGame.h"

InGame::InGame(int resX, int resY, int tileSize) : Scene(resX, resY, tileSize) {
    matchStarted = false;

    mapManager = new MapManager(tileSize);
    mapManager->LoadMapFromFile("./maps/test.txt");

    activeActor = nullptr;
    selectedActor = nullptr;
    actorUnderCursor = nullptr;

    actionMenu = new ActionMenu({ "Move", "Attack", "Inspect", "End" }, tileSize);
    actorManager = new ActorManager(resX, resY, tileSize);
    infoPanel = new InformationPanel(resX, resY, tileSize);
    pathingManager = new PathingManager(mapManager->GetMap(), tileSize);
    viewPort = new ViewPort(resX, resY, tileSize);
    cursor = new GameCursor(tileSize, viewPort->GetPosition().cameraX, viewPort->GetPosition().cameraY);
    turnManager = new TurnManager(resX, resY, tileSize);

    /*
    Actor* testActor1 = new Actor("./assets/PH_warrior.png", "./assets/knight.png", 3, 3, tileSize, Actor::Stats{0, 0, 0, 0, 0, 0, 0, 3});
    Actor* testActor2 = new Actor("./assets/PH_warrior.png", "./assets/knight.png", 6, 6, tileSize, Actor::Stats{0, 0, 0, 0, 0, 0, 0, 3});
    Actor* testActor3 = new Actor("./assets/PH_warrior.png", "./assets/knight.png", 9, 9, tileSize, Actor::Stats{0, 0, 0, 0, 0, 0, 0, 3});
    Actor* testEnemy1 = new Enemy("./assets/PH_mage.png", "./assets/man.png", 10, 7, tileSize, Actor::Stats{0, 0, 0, 0, 0, 0, 0, 3}, mapManager->GetMap(), new BasicAI(), actorManager->GetPlayerControlled());
    actorManager->Add(testActor1);
    actorManager->Add(testActor2);
    actorManager->Add(testActor3);
    actorManager->Add(testEnemy1);

    mapManager->SetTilesOccupied(actorManager->GetAllActors());
    */
}

void InGame::StartMatch() {
    if (!matchStarted) {        
        actorManager->PopulateFromParty();
        mapManager->SetTilesOccupied(actorManager->GetAllActors());
    }

    matchStarted = true;
}

void InGame::Update(double dt) {
    StartMatch();

    GameCursor::Position cursorPos = cursor->GetPosition();
    Tile* tileUnderCursor = mapManager->GetTile(cursorPos.x, cursorPos.y);
    actorUnderCursor = actorManager->GetActor(cursorPos.x, cursorPos.y);

    cursor->UpdateKnownViewportLocation(viewPort->GetPosition().cameraX, viewPort->GetPosition().cameraY);
    infoPanel->Update(cursorPos.x, cursorPos.y, tileUnderCursor);

    actionMenu->Update(cursorPos.x, cursorPos.y);
    actorManager->Update(dt, mapManager->GetMap());

    if (activeActor && !activeActor->ActionsAvailable()) {
        EndTurn();
    }

    // Wait until all movement is finished before starting next turn. The incorrect tiles are set as occupied if 
    // the turn ends while an actor is in transit.
    if (turnManager->IsCurrentTurnOver() && !actorManager->AnyActorsMoving()) {
        mapManager->SetTilesOccupied(actorManager->GetAllActors());

        activeActor = turnManager->GetNextTurn(actorManager->GetAllActors());

        Actor::Position actorPos = activeActor->GetPosition();
        viewPort->MoveToActor(actorPos.x, actorPos.y);
        cursor->MoveToActor(actorPos.x, actorPos.y);
    }
}

void InGame::Render(SDL_Renderer* rend) {
    ViewPort::Position pos = viewPort->GetPosition();
    GameCursor::Position cursorPos = cursor->GetPosition();

    mapManager->Render(rend, pos.x, pos.y, pos.tilesX, pos.tilesY, pos.cameraX, pos.cameraY);
    viewPort->Render(rend);
    actorManager->Render(rend, pos.x, pos.y, pos.tilesX, pos.tilesY, pos.cameraX, pos.cameraY);
    cursor->Render(rend, pos.x, pos.y);
    turnManager->Render(rend);
    infoPanel->Render(rend);
    actionMenu->Render(rend);

    if (selectedActor && selectedActor->IsPlanningMove()) {
        Actor::Position actorPos = selectedActor->GetPosition();

        if (cursorPos.x != actorPos.x || cursorPos.y != actorPos.y)
            pathingManager->Render(rend, pos.cameraX, pos.cameraY, pos.x, pos.y);
    }
}

Enums::Scene InGame::HandleEvents(SDL_Event event) {
    if (!actorManager->AnyActorsMoving()) {
        activeActor->IsPlayerControlled()
            ? HandlePlayerTurn(event)
            : HandleEnemyTurn(event);
    }

    return Enums::SCN_InGame;
}

void InGame::HandleEnemyTurn(SDL_Event event) {
    Actor::Position actorPos = activeActor->GetPosition();
    mapManager->GetTile(actorPos.x, actorPos.y)->SetOccupied(false);

    activeActor->DoTurn();
    EndTurn();
}

void InGame::HandlePlayerTurn(SDL_Event event) {
    InputManager* input = InputManager::getInstance();
	std::unordered_set<int> actions = input->getActionsDown();

    if (Utils::Contains(actions, Enums::ACTION_Up)) {
        if (actionMenu->IsActive()) {
            actionMenu->DecrementSelection();
        } else {
            MoveCursorUp();
        }
    }

    if (Utils::Contains(actions, Enums::ACTION_Down)) {
        if (actionMenu->IsActive()) {
            actionMenu->IncrementSelection();
        } else {
            MoveCursorDown();
        }
    }

    if (Utils::Contains(actions, Enums::ACTION_Left)) {
        if (!actionMenu->IsActive()) {
            MoveCursorLeft();
        }
    }

    if (Utils::Contains(actions, Enums::ACTION_Right)) {
        if (!actionMenu->IsActive()) {
            MoveCursorRight();
        }
    }

    if (Utils::Contains(actions, Enums::ACTION_Select)) {
        if (actionMenu->IsActive()) {
            switch (actionMenu->GetSelection()) {
                case Enums::ACTM_Move:
                    selectedActor->SetPlanningMove(true);
                    break;
                case Enums::ACTM_Attack:
                    selectedActor->SetPlanningAttack(true);
                    break;
                case Enums::ACTM_Inspect:
                    break;
                case Enums::ACTM_End:
                    EndTurn();
                    break;
            }

            actionMenu->SetActive(false);
        } else if (!selectedActor) {
            if (actorUnderCursor && actorUnderCursor->IsPlayerControlled()) {
                selectedActor = actorUnderCursor;
                actionMenu->SetActive(true);
            }
        } else if (selectedActor->IsPlanningMove()) {
            GameCursor::Position cursorPos = cursor->GetPosition();
            Actor::Position actorPos = selectedActor->GetPosition();
            Actor::Stats stats = selectedActor->GetStats();

            vector<GridLocation> path = pathingManager->GetPath();
            Tile* nextTile = mapManager->GetTile(cursorPos.x, cursorPos.y);
            Tile* prevTile = mapManager->GetTile(actorPos.x, actorPos.y);

            if (nextTile->IsPassable() && !nextTile->IsOccupied()) {
                if (actorPos.x != cursorPos.x || actorPos.y != cursorPos.y) {
                    if ((abs(cursorPos.x - actorPos.x) + abs(cursorPos.y - actorPos.y) <= stats.mov)) {
                        nextTile->SetOccupied(true);
                        prevTile->SetOccupied(false);
                        selectedActor->Move(path);

                        selectedActor->SetPlanningMove(false);
                        selectedActor->UseAction(Enums::TRN_Move);

                        if (selectedActor->ActionsAvailable()) {
                            actionMenu->SetActive(true);
                        }
                    }
                }
            }
        } else if (selectedActor->IsPlanningAttack()) {
            if (actorUnderCursor && !actorUnderCursor->IsPlayerControlled()) {
                selectedActor->Attack(actorUnderCursor);

                selectedActor->SetPlanningAttack(false);
                selectedActor->UseAction(Enums::TRN_Attack);

                if (selectedActor->ActionsAvailable()) {
                    actionMenu->SetActive(true);
                }
            }
        }
    }

    if (Utils::Contains(actions, Enums::ACTION_Cancel)) {
        if (selectedActor) {
            if (selectedActor->IsPlanningMove() || selectedActor->IsPlanningAttack()) {
                selectedActor->SetPlanningAttack(false);
                selectedActor->SetPlanningMove(false);
                actionMenu->SetActive(true);
            } else if (actionMenu->IsActive()) {
                actionMenu->SetActive(false);
                selectedActor->SetSelected(false);
                selectedActor = nullptr;
            }
        } else {
            Actor::Position actorPos = activeActor->GetPosition();
            viewPort->MoveToActor(actorPos.x, actorPos.y);
            cursor->MoveToActor(actorPos.x, actorPos.y);
        }
    }
}

void InGame::EndTurn() {
    if (selectedActor) {
        selectedActor->SetPlanningMove(false);
        selectedActor->SetPlanningAttack(false);
        selectedActor->ResetAvailableActions();
        selectedActor->SetSelected(false);
    }

    selectedActor = nullptr;
    turnManager->EndTurn();
}

void InGame::MoveCursorUp() {
    GameCursor::Position cursorPos = cursor->GetPosition();
    ViewPort::Position vpPos = viewPort->GetPosition();

    if (cursorPos.y == vpPos.cameraY) {
        if (vpPos.cameraY != 0) {
            viewPort->MoveCamera(0, -1);
        }
    } 
    
    if (cursorPos.y != 0) {
        cursor->Move(0, -1);
    }

    if (selectedActor) {
        GameCursor::Position cPos = cursor->GetPosition();
        Actor::Position aPos = selectedActor->GetPosition();

        pathingManager->CalculatePath(aPos.x, aPos.y, cPos.x, cPos.y);
    }
}

void InGame::MoveCursorDown() {
    GameCursor::Position cursorPos = cursor->GetPosition();
    ViewPort::Position vpPos = viewPort->GetPosition();
    Map::Dimensions mapSize = mapManager->GetMapSize();

    if (cursorPos.y + 1 == vpPos.cameraY + (vpPos.h / tileSize)) {
        if (vpPos.cameraY + (vpPos.h / tileSize) < mapSize.h) {
            viewPort->MoveCamera(0, 1);
        }
    } 
    
    if (cursorPos.y + 1 < mapSize.h) {
        cursor->Move(0, 1);
    }

    if (selectedActor) {
        GameCursor::Position cPos = cursor->GetPosition();
        Actor::Position aPos = selectedActor->GetPosition();

        pathingManager->CalculatePath(aPos.x, aPos.y, cPos.x, cPos.y);
    }
}

void InGame::MoveCursorLeft() {
    GameCursor::Position cursorPos = cursor->GetPosition();
    ViewPort::Position vpPos = viewPort->GetPosition();

    if (cursorPos.x == vpPos.cameraX) {
        if (vpPos.cameraX != 0) {
            viewPort->MoveCamera(-1, 0);
        }
    } 
    
    if (cursorPos.x != 0) {
        cursor->Move(-1, 0);
    }

    if (selectedActor) {
        GameCursor::Position cPos = cursor->GetPosition();
        Actor::Position aPos = selectedActor->GetPosition();

        pathingManager->CalculatePath(aPos.x, aPos.y, cPos.x, cPos.y);
    }
}

void InGame::MoveCursorRight() {
    GameCursor::Position cursorPos = cursor->GetPosition();
    ViewPort::Position vpPos = viewPort->GetPosition();
    Map::Dimensions mapSize = mapManager->GetMapSize();

    if (cursorPos.x + 1 == vpPos.cameraX + (vpPos.w / tileSize)) {
        if (vpPos.cameraX + (vpPos.w / tileSize) < mapSize.w) {
            viewPort->MoveCamera(1, 0);
        }
    }
    
    if (cursorPos.x + 1 < mapSize.w) {
        cursor->Move(1, 0);
    }

    if (selectedActor) {
        GameCursor::Position cPos = cursor->GetPosition();
        Actor::Position aPos = selectedActor->GetPosition();

        pathingManager->CalculatePath(aPos.x, aPos.y, cPos.x, cPos.y);
    }
}

void InGame::PrintPositions() {
    Map::Dimensions mapSize = mapManager->GetMapSize();
    GameCursor::Position cursorPos = cursor->GetPosition();
    ViewPort::Position vpPos = viewPort->GetPosition();

    cout << printf("camera: %d %d %d\n", vpPos.cameraX, vpPos.cameraY, vpPos.h);
    cout << printf("cursor: %d %d\n", cursorPos.x, cursorPos.y);
    cout << printf("mapSize: %d %d\n", mapSize.w, mapSize.h);
}