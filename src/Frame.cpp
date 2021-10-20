#include "Frame.h"

Frame::Frame(Position pos) {
    this->pos = pos;
    frameTexture = TextureManager::loadTexture(frameImagePath);
}

void Frame::Render(SDL_Renderer* rend) {
    SDL_Rect dst { pos.x, pos.y, pos.w, pos.h };
    SDL_RenderCopy(rend, frameTexture, NULL, &dst);
}