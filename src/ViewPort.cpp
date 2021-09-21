#include "ViewPort.h"

ViewPort::ViewPort(int resX, int resY, int ts) {
    resolutionX = resX;
    resolutionY = resY;
    tileSize = ts;

    viewPortBorder = "./assets/viewport_border.png";
    viewPortTexture = TextureManager::loadTexture(viewPortBorder);

    x = y = tileSize;
    w = h = resolutionY - y - tileSize;
}

void ViewPort::Render(SDL_Renderer* rend) {
    SDL_Rect src {0, 0, tileSize, tileSize};
    SDL_Rect dst {x, y, w, h};

    SDL_RenderCopy(rend, viewPortTexture, &src, &dst);
}