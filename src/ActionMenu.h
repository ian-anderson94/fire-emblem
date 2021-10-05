#ifndef SRC_ACTIONMENU_H_
#define SRC_ACTIONMENU_H_

#include "Enums.h"
#include "SDL2/SDL.h"
#include "TextManager.h"
#include "TextureManager.h"

#include <string>
#include <vector>

class ActionMenu {
    public:
        ActionMenu(int ts);
        void Render(SDL_Renderer* rend);
        void Update(int cursorX, int cursorY);
        void IncrementSelection();
        void DecrementSelection();
        
        void SetActive(bool val) { active = val; };
        bool IsActive() { return active; };
        int GetSelection() { return currSelection; };

    private:
        bool active;
        int currSelection, tileSize, x, y, w, h;

        const char* menuImagePath;
        SDL_Texture* menuTexture;

        void BoundSelection();
        void RenderMenuOptions(SDL_Renderer* rend);
        void RenderSelector(SDL_Renderer* rend);
};

#endif /* SRC_ACTIONMENU_H_ */
