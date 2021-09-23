#include "GameCursor.h"
#include <iostream>

GameCursor::GameCursor(int tileSize) {
    x = y = 0;
    size = tileSize;

    cursorImage = "./assets/cursor.png";
    cursorTexture = TextureManager::loadTexture(cursorImage);
}

void GameCursor::Render(SDL_Renderer* rend, int xOffset, int yOffset) {
    SDL_Rect dst {
        x + xOffset,
        y + yOffset,
        size,
        size
    };

    SDL_RenderCopy(rend, cursorTexture, NULL, &dst);
}

void GameCursor::Move(int dx, int dy) {
    x += dx * size;
    y += dy * size;
}