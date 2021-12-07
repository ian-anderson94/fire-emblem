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
}

void InGame::StartMatch() {
    if (!matchStarted) {
        PlayerAccount* account = PlayerAccount::GetInstance();

        mapManager->LoadMapFromFile(account->GetActiveQuest()->GetMapFilePath().c_str());
        pathingManager = new PathingManager(mapManager->GetMap(), tileSize);      
        actorManager->PopulateFromParty(mapManager->GetPlayerSpawns());
        actorManager->PopulateEnemiesFromQuestBlueprint(account->GetActiveQuest()->GetEnemyBlueprint(), mapManager->GetMap());
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
            MoveCursor(0, -1);
        }
    }

    if (Utils::Contains(actions, Enums::ACTION_Down)) {
        if (actionMenu->IsActive()) {
            actionMenu->IncrementSelection();
        } else {
            MoveCursor(0, 1);
        }
    }

    if (Utils::Contains(actions, Enums::ACTION_Left)) {
        if (!actionMenu->IsActive()) {
            MoveCursor(-1, 0);
        }
    }

    if (Utils::Contains(actions, Enums::ACTION_Right)) {
        if (!actionMenu->IsActive()) {
            MoveCursor(1, 0);
        }
    }

    if (Utils::Contains(actions, Enums::ACTION_Select)) {
        if (actionMenu->IsActive()) {
            switch (actionMenu->GetSelection()) {
                case Enums::ACTM_Move:
                    if (selectedActor->GetActionsAvailable()[Enums::TRN_Move]) {
                        selectedActor->SetPlanningMove(true);
                        actionMenu->SetActive(false);
                    }

                    break;
                case Enums::ACTM_Attack:
                    if (selectedActor->GetActionsAvailable()[Enums::TRN_Attack]) {
                        selectedActor->SetPlanningAttack(true);
                        actionMenu->SetActive(false);
                    }

                    break;
                case Enums::ACTM_Inspect:
                    actionMenu->SetActive(false);
                    break;
                case Enums::ACTM_End:
                    actionMenu->SetActive(false);
                    EndTurn();
                    break;
            }

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

void InGame::MoveCursor(int dx, int dy) {
    GameCursor::Position cursorPos = cursor->GetPosition();
    ViewPort::Position vpPos = viewPort->GetPosition();
    Map::Dimensions mapSize = mapManager->GetMapSize();

    if (cursorPos.y == vpPos.cameraY) {
        if (vpPos.cameraY != 0) {
            viewPort->MoveCamera(dx, dy);
        }
    } 
    
    int nextX = cursorPos.x + dx;
    int nextY = cursorPos.y + dy;

    if (nextX >= 0 && nextX < mapSize.w) {
        if (nextY >=0 && nextY < mapSize.h) {
            cursor->Move(dx, dy);
        }
    }

    if (selectedActor) {
        GameCursor::Position cPos = cursor->GetPosition();
        Actor::Position aPos = selectedActor->GetPosition();
        Tile* tileUnderCursor = mapManager->GetTile(cPos.x, cPos.y);

        if (tileUnderCursor->IsPassable()) {
            pathingManager->CalculatePath(aPos.x, aPos.y, cPos.x, cPos.y);
        }
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