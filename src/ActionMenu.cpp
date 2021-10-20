#include "ActionMenu.h"

#include <iostream>

ActionMenu::ActionMenu(int ts) {
    currSelection = Enums::ACTM_Move;
    active = false;

    tileSize = ts;

    w = tileSize * 2;
    h = tileSize * 3;
    x = y = 0;

    menuImagePath = "./assets/infopanel.png";
    menuTexture = TextureManager::loadTexture(menuImagePath);

    if (!menuTexture) {
        std::cout << "Error loading tex" << std::endl;
    }
}

void ActionMenu::Render(SDL_Renderer* rend) {
    if (active) {
        SDL_Rect dst {
            x, 
            y, 
            w, 
            h
        };

        SDL_RenderCopy(rend, menuTexture, NULL, &dst);
        RenderMenuOptions(rend);
        RenderSelector(rend);
    }
}

void ActionMenu::RenderMenuOptions(SDL_Renderer* rend) {
    SDL_Color white = { 255, 255, 255 };
    const char* fontFile = "fonts/OpenSans-Regular.ttf";

    int yOffset = 0;
    std::vector<std::string> options = { "Move", "Attack", "Inspect", "End" };

    int mx = x + (tileSize / 2);
    int mw = w - (tileSize / 2);

    for (auto const& option : options) {
        TextManager::LoadFontAndPrint(rend, option.c_str(), mx, y + yOffset);
        yOffset += tileSize / 2;
    }
}

void ActionMenu::RenderSelector(SDL_Renderer* rend) {
    int sh = tileSize / 2;
    int sw = tileSize / 2;
    int sx = x;
    int sy = y + (currSelection * (tileSize / 2));

    SDL_Texture* tex = TextureManager::loadTexture("./assets/selector_arrow.png");

    SDL_Rect src {0, 0, tileSize, tileSize};
    SDL_Rect dst {sx, sy, sw, sh};

    SDL_RenderCopy(rend, tex, &src, &dst); 
}

void ActionMenu::Update(int cursorX, int cursorY) {
    x = (cursorX * tileSize) + (tileSize * 1.5);
    y = cursorY * tileSize;
}

void ActionMenu::IncrementSelection() {
    currSelection++;
    BoundSelection();
}

void ActionMenu::DecrementSelection() {
    currSelection--;
    BoundSelection();
}

void ActionMenu::BoundSelection() {
    if (currSelection > Enums::ACTM_End) {
        currSelection = Enums::ACTM_Move;
    } else if (currSelection < Enums::ACTM_Move) {
        currSelection = Enums::ACTM_End;
    }
}