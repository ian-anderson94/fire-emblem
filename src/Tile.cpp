#include "Tile.h"
#include <iostream>

Tile::Tile(TileDefinition* tileDef, int xPos, int yPos, int tileSize) {
    definition = tileDef;
    x = xPos;
    y = yPos;
    size = tileSize;

    passable = definition->GetPassable();

    string image = definition->GetImageFile();
    tileTexture = TextureManager::loadTexture(definition->GetImageFile().c_str());
}

void Tile::Render(SDL_Renderer* rend) {
    SDL_Rect src {0, 0, size, size};
    SDL_Rect dst {x, y, size, size};

    SDL_RenderCopy(rend, tileTexture, &src, &dst);
}

void Tile::RenderRelativeToViewPort(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY) {
    SDL_Rect dst {
        ((x - camX) * size) + xOffset,
        ((y - camY) * size) + yOffset,
        size,
        size
    };

    SDL_RenderCopy(rend, tileTexture, NULL, &dst);
}

