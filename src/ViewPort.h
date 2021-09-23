#ifndef SRC_VIEWPORT_H_
#define SRC_VIEWPORT_H_

#include "TextureManager.h"
#include "SDL2/SDL.h"

#include <math.h>

class ViewPort {
    public:
        struct Position {
            int x, y, w, h, cameraX, cameraY, tilesX, tilesY;
        };

        ViewPort(int resX, int resY, int ts);
        Position GetPosition() { return Position{x, y, w, h, cameraX, cameraY, maxTilesHorizontal, maxTilesVertical }; };
        void Render(SDL_Renderer* rend);
        void MoveCamera(int dx, int dy);

    private:
        int resolutionX;
        int resolutionY;
        int tileSize;
        int x, y, w, h, cameraX, cameraY;
        int maxTilesHorizontal, maxTilesVertical;

        const char* viewPortBorder;
        SDL_Texture* viewPortTexture;
};

#endif /* SRC_VIEWPORT_H_ */