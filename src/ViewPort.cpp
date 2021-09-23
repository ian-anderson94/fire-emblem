#include "ViewPort.h"
#include <iostream>

ViewPort::ViewPort(int resX, int resY, int ts) {
    resolutionX = resX;
    resolutionY = resY;
    tileSize = ts;

    viewPortBorder = "./assets/viewport_border.png";
    viewPortTexture = TextureManager::loadTexture(viewPortBorder);

    maxTilesHorizontal = floor(resolutionX / tileSize) - 2;
    maxTilesVertical = floor(resolutionY / tileSize) - 2;

    w = maxTilesHorizontal * tileSize;
    h = maxTilesVertical * tileSize;

    x = (resolutionX - w) / 2;
    y = (resolutionY - h) / 2;

    cameraX = cameraY = 1;
}

void ViewPort::Render(SDL_Renderer* rend) {
    SDL_Rect dst {x, y, w, h};
    SDL_RenderCopy(rend, viewPortTexture, NULL, &dst);
}

void ViewPort::MoveCamera(int dx, int dy) {
    cameraX += dx;
    cameraY += dy;
}