#include "InGame.h"

InGame::InGame(int resX, int resY, int ts) {
    resolutionX = resX;
    resolutionY = resY;
    tileSize = ts;

    mapManager = new MapManager(tileSize);
    mapManager->LoadMapFromFile("./maps/test.txt");

    activeActor = nullptr;
    selectedActor = nullptr;
    actorUnderCursor = nullptr;

    actorManager = new ActorManager(resX, resY, ts);
    infoPanel = new InformationPanel(resX, resY, ts);
    pathingManager = new PathingManager(mapManager->GetMap());
    viewPort = new ViewPort(resX, resY, ts);
    cursor = new GameCursor(tileSize, viewPort->GetPosition().cameraX, viewPort->GetPosition().cameraY);
    turnManager = new TurnManager(resX, resY, ts);

    backgroundTextureFile = "./assets/mainmenu_background.png";
    backgroundTexture = TextureManager::loadTexture(backgroundTextureFile);

    Actor* testActor1 = new Actor("./assets/man.png", "./assets/man.png", 3, 3, tileSize, Actor::Stats{0, 0, 0, 0, 0, 0, 3});
    Actor* testActor2 = new Actor("./assets/man.png", "./assets/man.png", 6, 6, tileSize, Actor::Stats{0, 0, 0, 0, 0, 0, 3});
    Actor* testActor3 = new Actor("./assets/man.png", "./assets/man.png", 9, 9, tileSize, Actor::Stats{0, 0, 0, 0, 0, 0, 3});
    actorManager->Add(testActor1);
    actorManager->Add(testActor2);
    actorManager->Add(testActor3);
}

void InGame::Update(double dt) {
    GameCursor::Position cursorPos = cursor->GetPosition();
    ViewPort::Position vpPos = viewPort->GetPosition();
    Tile* tileUnderCursor = mapManager->GetTile(cursorPos.x, cursorPos.y);
    actorUnderCursor = actorManager->GetActor(cursorPos.x, cursorPos.y);

    cursor->UpdateKnownViewportLocation(viewPort->GetPosition().cameraX, viewPort->GetPosition().cameraY);
    infoPanel->Update(cursorPos.x, cursorPos.y, tileUnderCursor);

    actorManager->Update(mapManager->GetMap());

    if (turnManager->IsCurrentTurnOver()) {
        activeActor = turnManager->GetNextTurn(actorManager->GetAllActors());

        Actor::Position actorPos = activeActor->GetPosition();
        cursor->MoveToActor(actorPos.x, actorPos.y);
        viewPort->MoveToActor(actorPos.x, actorPos.y);
    }
}

void InGame::Render(SDL_Renderer* rend) {
    ViewPort::Position pos = viewPort->GetPosition();
    GameCursor::Position cursorPos = cursor->GetPosition();
    Actor::Position actorPos = selectedActor->GetPosition();

    RenderBackground(rend);
    mapManager->Render(rend, pos.x, pos.y, pos.tilesX, pos.tilesY, pos.cameraX, pos.cameraY);
    viewPort->Render(rend);
    actorManager->Render(rend, pos.x, pos.y, pos.tilesX, pos.tilesY, pos.cameraX, pos.cameraY);
    cursor->Render(rend, pos.x, pos.y);
    turnManager->Render(rend);
    infoPanel->Render(rend);

    if (selectedActor) {
        RenderPathingArrow(cursorPos.x, cursorPos.y, actorPos.x, actorPos.y);
    }
}

void InGame::RenderBackground(SDL_Renderer* rend) {
    SDL_Rect src {0, 0, resolutionX, resolutionY};
    SDL_Rect dst {0, 0, resolutionX, resolutionY};

    SDL_RenderCopy(rend, backgroundTexture, &src, &dst);
}

void InGame::RenderPathingArrow(int cursorX, int cursorY, int actorX, int actorY) {

}

int InGame::HandleEvents(SDL_Event event) {
    InputManager* input = InputManager::getInstance();
	std::unordered_set<int> actions = input->getActionsDown();

    Map::Dimensions mapSize = mapManager->GetMapSize();
    GameCursor::Position cursorPos = cursor->GetPosition();
    ViewPort::Position vpPos = viewPort->GetPosition();

    if (Utils::Contains(actions, Enums::ACTION_Up)) {
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

    if (Utils::Contains(actions, Enums::ACTION_Down)) {
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

    if (Utils::Contains(actions, Enums::ACTION_Left)) {
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

    if (Utils::Contains(actions, Enums::ACTION_Right)) {
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

    if (!selectedActor) {
        if (Utils::Contains(actions, Enums::ACTION_Select)) {
            if (actorUnderCursor != nullptr && actorUnderCursor->GetPlayerControlled() == true && actorUnderCursor == activeActor) {
                selectedActor = actorUnderCursor;
                selectedActor->SetSelected(true);
            }
        }
    } else {
        if (Utils::Contains(actions, Enums::ACTION_Select)) {
            GameCursor::Position cursorPos = cursor->GetPosition();
            Actor::Position actorPos = selectedActor->GetPosition();
            Actor::Stats stats = selectedActor->GetStats();

            if (mapManager->GetTile(cursorPos.x, cursorPos.y)->IsPassable()) {
                if ((abs(cursorPos.x - actorPos.x) + abs(cursorPos.y - actorPos.y) <= stats.mov)) {
                    selectedActor->Move(cursorPos.x, cursorPos.y);
                    selectedActor->SetSelected(false);
                    selectedActor = nullptr;
                    turnManager->EndTurn();
                }
            }
        }
    }

    if (Utils::Contains(actions, Enums::ACTION_Jump)) {
        PrintPositions();
    }

    return Enums::MMS_GameStart;
}

void InGame::PrintPositions() {
    Map::Dimensions mapSize = mapManager->GetMapSize();
    GameCursor::Position cursorPos = cursor->GetPosition();
    ViewPort::Position vpPos = viewPort->GetPosition();

    cout << printf("camera: %d %d %d\n", vpPos.cameraX, vpPos.cameraY, vpPos.h);
    cout << printf("cursor: %d %d\n", cursorPos.x, cursorPos.y);
    cout << printf("mapSize: %d %d\n", mapSize.w, mapSize.h);
}