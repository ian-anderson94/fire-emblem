#ifndef SRC_HUBSCREEN_H_
#define SRC_HUBSCREEN_H_

#include "Enums.h"
#include "InputManager.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "Utils.h"

#include <unordered_map>

using namespace std;

class HubScreen {
    public:
        HubScreen(int resX, int resY, int tileSize);
        Enums::Scene HandleEvents(SDL_Event event);
        void Render(SDL_Renderer* rend);
        void Update();

    private:
        int resX, resY, tileSize, currSelection;

        const char* recruitmentImagePath;
        const char* embarkImagePath;

        unordered_map<Enums::HubSelection, SDL_Texture*> selectionTextures;

        Enums::Scene MapHubSelectionToScene();
        void IncrementSelection();
        void DecrementSelection();

};

#endif /* SRC_HUBSCREEN_H_ */