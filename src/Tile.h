#ifndef SRC_TILE_H_
#define SRC_TILE_H_

#include "TextureManager.h"
#include "TileDefinition.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Tile {

public:
    struct Position {
        int x, y, size;
    };

	Tile(TileDefinition* tileDef, int xPos, int yPos, int tileSize);
    Position GetPosition() { return Position{x, y, size}; };
    void Render(SDL_Renderer* rend);
    void RenderRelativeToViewPort(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY);

private:
    SDL_Texture* tileTexture;
    TileDefinition* definition;
    int x, y, size;
    bool passable;

    
};

#endif /* SRC_TILE_H_ */
