#include "GameCursor.h"
#include <iostream>

GameCursor::GameCursor(int tileSize, int xPos, int yPos) {
    x = xPos;
    y = yPos;
    vpX = xPos;
    vpY = yPos;
    size = tileSize;

    cursorImage = "./assets/cursor.png";
    cursorTexture = TextureManager::loadTexture(cursorImage);
}

void GameCursor::Render(SDL_Renderer* rend, int xOffset, int yOffset) {
    SDL_Rect dst {
        ((x - vpX) * size) + xOffset,
        ((y - vpY) * size) + yOffset,
        size,
        size
    };

    SDL_RenderCopy(rend, cursorTexture, NULL, &dst);
}

void GameCursor::Move(int dx, int dy) {
    x += dx;
    y += dy;
}

void GameCursor::MoveToActor(int x, int y) {
    this->x = x;
    this->y = y;
}

void GameCursor::UpdateKnownViewportLocation(int xPos, int yPos) {
    vpX = xPos;
    vpY = yPos;
}