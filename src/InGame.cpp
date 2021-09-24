#include "InGame.h"

InGame::InGame(int resX, int resY, int ts) {
    resolutionX = resX;
    resolutionY = resY;
    tileSize = ts;

    mapManager = new MapManager(tileSize);
    mapManager->LoadMapFromFile("./maps/test.txt");

    infoPanel = new InformationPanel(resX, resY, ts);
    viewPort = new ViewPort(resX, resY, ts);
    cursor = new GameCursor(tileSize, viewPort->GetPosition().cameraX, viewPort->GetPosition().cameraY);

    backgroundTextureFile = "./assets/mainmenu_background.png";
    backgroundTexture = TextureManager::loadTexture(backgroundTextureFile);
}

void InGame::Update(double dt) {
    GameCursor::Position cursorPos = cursor->GetPosition();
    Tile* tileUnderCursor = mapManager->GetTile(cursorPos.x, cursorPos.y);

    cursor->UpdateKnownViewportLocation(viewPort->GetPosition().cameraX, viewPort->GetPosition().cameraY);
    infoPanel->Update(cursorPos.x, cursorPos.y, tileUnderCursor);
}

void InGame::Render(SDL_Renderer* rend) {
    ViewPort::Position pos = viewPort->GetPosition();

    RenderBackground(rend);
    mapManager->Render(rend, pos.x, pos.y, pos.tilesX, pos.tilesY, pos.cameraX, pos.cameraY);
    cursor->Render(rend, pos.x, pos.y);
    viewPort->Render(rend);
    infoPanel->Render(rend);
}

void InGame::RenderBackground(SDL_Renderer* rend) {
    SDL_Rect src {0, 0, resolutionX, resolutionY};
    SDL_Rect dst {0, 0, resolutionX, resolutionY};

    SDL_RenderCopy(rend, backgroundTexture, &src, &dst);
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