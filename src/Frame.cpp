#include "Frame.h"

Frame::Frame(Position pos) {
    this->pos = pos;
    frameTexture = TextureManager::loadTexture(frameImagePath);
}

void Frame::Render(SDL_Renderer* rend, float scale = 1) {
    SDL_Rect dst { pos.x, pos.y, (int) (pos.w * scale), (int) (pos.h * scale) };
    SDL_RenderCopy(rend, frameTexture, NULL, &dst);
}