#ifndef SRC_INGAME_H_
#define SRC_INGAME_H_

#include "TextureManager.h"
#include "ViewPort.h"
#include "SDL2/SDL.h"

class InGame {
    public:
        InGame(int resX, int resY, int ts);
        void Render(SDL_Renderer* rend);

    private:
        int resolutionX;
        int resolutionY;
        int tileSize;

        ViewPort* viewPort;
        const char* backgroundTextureFile;
        SDL_Texture* backgroundTexture;

        void RenderBackground(SDL_Renderer* rend);
};

#endif /* SRC_INGAME_H_ */
