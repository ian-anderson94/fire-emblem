#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include "Enums.h"
#include "InputManager.h"
#include "Mouse.h"
#include "SDL2/SDL.h"
#include "TextManager.h"
#include "TextureManager.h"
#include "Utils.h"

#include <string>
#include <unordered_set>

using namespace std;

class Button {
    public:
        struct Position {
            int x, y, w, h;
        };

        Button(const char* text, int x, int y, int w, int h, Enums::Scene currScene, Enums::Scene (*functionality)(Enums::Scene));
        virtual void Render(SDL_Renderer* rend);
        Enums::Scene HandleEvents(SDL_Event event);
        virtual Enums::Scene Execute();
        bool IsClicked();

        static Enums::Scene GetSceneEnum(Enums::Scene scene) { return scene; };

    protected:
        int x, y, w, h;
        const char* text;
        const char* backgroundImagePath;
        SDL_Texture* backgroundTexture;
        Enums::Scene currScene;

        Enums::Scene (*functionality)(Enums::Scene);
};

#endif /* SRC_BUTTON_H_ */