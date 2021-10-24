#ifndef SRC_ACTIONMENU_H_
#define SRC_ACTIONMENU_H_

#include "Enums.h"
#include "Position.h"
#include "SDL2/SDL.h"
#include "Selector.h"
#include "TextManager.h"
#include "TextureManager.h"

#include <string>
#include <vector>

using namespace std;

class ActionMenu {
    public:
        ActionMenu(vector<string> menuOptions, int tileSize);
        void Render(SDL_Renderer* rend);
        void Update(int cursorX, int cursorY);
        void Update(Position pos);
        void IncrementSelection();
        void DecrementSelection();
        
        void SetActive(bool val) { active = val; currSelection = 0; };
        bool IsActive() { return active; };
        int GetSelection() { return selector->GetSelectionIndex(); };

    private:
        bool active;
        int currSelection, tileSize, x, y, w, h;
        vector<string> menuOptions;

        Selector<string>* selector;
        const char* menuImagePath;
        SDL_Texture* menuTexture;

        Position RenderMenuOptions(SDL_Renderer* rend);
};

#endif /* SRC_ACTIONMENU_H_ */
