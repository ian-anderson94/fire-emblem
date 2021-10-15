#ifndef SRC_BACKGROUND_H_
#define SRC_BACKGROUND_H_

#include "TextureManager.h"

class Background {
    public:
        Background(int resX, int resY);
        void Render(SDL_Renderer* rend);

    private:
        int resX, resY;
        const char* backgroundImagePath;
        SDL_Texture* backgroundTexture;
};

#endif /* SRC_BACKGROUND_H_ */