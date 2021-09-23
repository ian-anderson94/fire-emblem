#ifndef SRC_GAMECURSOR_H_
#define SRC_GAMECURSOR_H_

#include "SDL2/SDL.h"
#include "TextureManager.h"

class GameCursor {
    public:
        struct Position {
            int x, y, size;
        };

        GameCursor(int tileSize);
        void Render(SDL_Renderer* rend, int xOffset, int yOffset);
        void Move(int dx, int dy);

        Position GetPosition() { return Position {x, y, size}; };

    private:
        int x, y, size;
        SDL_Texture* cursorTexture;
        const char* cursorImage;
};

#endif /* SRC_GAMECURSOR_H_ */