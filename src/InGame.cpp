#include "InGame.h"

InGame::InGame(int resX, int resY, int ts) {
    resolutionX = resX;
    resolutionY = resY;
    tileSize = ts;

    viewPort = new ViewPort(resX, resY, ts);

    backgroundTextureFile = "./assets/mainmenu_background.png";
    backgroundTexture = TextureManager::loadTexture(backgroundTextureFile);
}

void InGame::Render(SDL_Renderer* rend) {
    RenderBackground(rend);
    viewPort->Render(rend);
}

void InGame::RenderBackground(SDL_Renderer* rend) {
    SDL_Rect src {0, 0, resolutionX, resolutionY};
    SDL_Rect dst {0, 0, resolutionX, resolutionY};

    SDL_RenderCopy(rend, backgroundTexture, &src, &dst);
}

