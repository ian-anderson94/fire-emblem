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

void ViewPort::MoveToActor(int x, int y) {
    if (x < cameraX) {
        MoveCamera(x - cameraX, 0);
    }

    if (x > cameraX + maxTilesHorizontal - 1) {
        MoveCamera(x - (cameraX + maxTilesHorizontal - 1), 0);
    }

    if (y < cameraY) {
        MoveCamera(0, y - cameraY);
    }

    if (y > cameraY + maxTilesVertical - 1) {
        MoveCamera(0, y - (cameraY + maxTilesVertical - 1));
    }
}