#include "InGame.h"

InGame::InGame(int resX, int resY, int ts) {
    resolutionX = resX;
    resolutionY = resY;
    tileSize = ts;

    mapManager = new MapManager(tileSize);
    mapManager->LoadMapFromFile("./maps/test.txt");

    viewPort = new ViewPort(resX, resY, ts);
    cursor = new GameCursor(tileSize);

    backgroundTextureFile = "./assets/mainmenu_background.png";
    backgroundTexture = TextureManager::loadTexture(backgroundTextureFile);
}

void InGame::Render(SDL_Renderer* rend) {
    ViewPort::Position pos = viewPort->GetPosition();

    RenderBackground(rend);
    mapManager->Render(rend, pos.x, pos.y, pos.tilesX, pos.tilesY, pos.cameraX, pos.cameraY);
    cursor->Render(rend, pos.x, pos.y);
    viewPort->Render(rend);
}

void InGame::RenderBackground(SDL_Renderer* rend) {
    SDL_Rect src {0, 0, resolutionX, resolutionY};
    SDL_Rect dst {0, 0, resolutionX, resolutionY};

    SDL_RenderCopy(rend, backgroundTexture, &src, &dst);
}

int InGame::HandleEvents(SDL_Event event) {
    InputManager* input = InputManager::getInstance();
	std::unordered_set<int> actions = input->getActionsDown();

    GameCursor::Position cursorPos = cursor->GetPosition();
    ViewPort::Position vpPos = viewPort->GetPosition();

    if (Utils::Contains(actions, Enums::ACTION_Up)) {
        cursor->Move(0, -1);
    }

    if (Utils::Contains(actions, Enums::ACTION_Down)) {
        cursor->Move(0, 1);
    }

    if (Utils::Contains(actions, Enums::ACTION_Left)) {
        cursor->Move(-1, 0);
    }

    if (Utils::Contains(actions, Enums::ACTION_Right)) {
        cursor->Move(1, 0);
    }

    return Enums::MMS_GameStart;
}