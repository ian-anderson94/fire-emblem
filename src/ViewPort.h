#ifndef SRC_VIEWPORT_H_
#define SRC_VIEWPORT_H_

#include "TextureManager.h"
#include "SDL2/SDL.h"

class ViewPort {
    public:
        ViewPort(int resX, int resY, int ts);
        void Render(SDL_Renderer* rend);

    private:
        int resolutionX;
        int resolutionY;
        int tileSize;
        int x, y, w, h;

        const char* viewPortBorder;
        SDL_Texture* viewPortTexture;
};

#endif /* SRC_VIEWPORT_H_ */