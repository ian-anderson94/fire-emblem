#ifndef SRC_INGAME_H_
#define SRC_INGAME_H_

#include "GameCursor.h"
#include "InputManager.h"
#include "MapManager.h"
#include "TextureManager.h"
#include "ViewPort.h"
#include "SDL2/SDL.h"

class InGame {
    public:
        InGame(int resX, int resY, int ts);
        void Render(SDL_Renderer* rend);
        int HandleEvents(SDL_Event event);

    private:
        int resolutionX;
        int resolutionY;
        int tileSize;

        GameCursor* cursor;
        ViewPort* viewPort;
        const char* backgroundTextureFile;
        SDL_Texture* backgroundTexture;
        MapManager* mapManager;

        void RenderBackground(SDL_Renderer* rend);
};

#endif /* SRC_INGAME_H_ */
