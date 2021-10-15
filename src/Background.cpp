#include "Background.h"

Background::Background(int resX, int resY) {
    this->resX = resX;
    this->resY = resY;
    backgroundImagePath = "./assets/mainmenu_background.png";
    backgroundTexture = TextureManager::loadTexture(backgroundImagePath);
}

void Background::Render(SDL_Renderer* rend) {
    SDL_Rect dst {0, 0, resX, resY};
    SDL_RenderCopy(rend, backgroundTexture, NULL, &dst);
}