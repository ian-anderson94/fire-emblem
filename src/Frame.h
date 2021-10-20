#ifndef SRC_FRAME_H_
#define SRC_FRAME_H_

#include "Position.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"

class Frame {
    public:
        Frame(Position pos);
        void Render(SDL_Renderer* rend, float scale);

        Position GetPosition() { return pos; };

    private:
        Position pos;

        const char* frameImagePath = "./assets/viewport_border.png";
        SDL_Texture* frameTexture;

};

#endif /* SRC_FRAME_H_ */