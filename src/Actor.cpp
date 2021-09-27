#include "Actor.h"

Actor::Actor(const char* image, const char* icon, int xPos, int yPos, int ts, Stats actorStats) {
    x = xPos;
    y = yPos;
    size = ts;
    stats = actorStats;

    selected = false;
    playerControlled = true;

    imagePath = image;
    iconPath = icon;
    moveTilePath = "./assets/moveTile.png";
    moveTileTexture = TextureManager::loadTexture(moveTilePath);
    actorTexture = TextureManager::loadTexture(imagePath);
    iconTexture = TextureManager::loadTexture(iconPath);
}

void Actor::RenderRelativeToViewport(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY) {
    if (selected) {
        RenderPossibleMoves(rend, xOffset, yOffset, camX, camY);
    }

    SDL_Rect dst {
        ((x - camX) * size) + xOffset, 
        ((y - camY) * size) + yOffset, 
        size, 
        size
    };

    SDL_RenderCopy(rend, actorTexture, NULL, &dst);
}

void Actor::RenderPossibleMoves(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY) {
    for (int i = (stats.mov * -1); i < stats.mov; i++) {
        for (int j = (stats.mov * -1); j < stats.mov; j++) {
            if (abs(i) + abs(j) < stats.mov) {
                SDL_Rect dst {
                    ((x + i - camX) * size) + xOffset,
                    ((y + j - camY) * size) + yOffset,
                    size,
                    size
                };

                SDL_RenderCopy(rend, moveTileTexture, NULL, &dst);
            }
        }
    }
}

void Actor::Move(int newX, int newY) {
    x = newX;
    y = newY;
}
