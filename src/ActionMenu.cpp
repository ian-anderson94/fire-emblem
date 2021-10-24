#include "ActionMenu.h"

#include <iostream>

ActionMenu::ActionMenu(vector<string> menuOptions, int tileSize) {
    this->menuOptions = menuOptions;
    this->tileSize = tileSize;

    selector = new Selector<string>(menuOptions);
    currSelection = 0;
    active = false;

    Position mPos = TextManager::SizeListOfText(menuOptions);
    int selectorSize = mPos.h / (int) (menuOptions.size());

    w = mPos.w + selectorSize;
    h = mPos.h;
    x = y = 0;

    menuImagePath = "./assets/infopanel.png";
    menuTexture = TextureManager::loadTexture(menuImagePath);
}

void ActionMenu::Render(SDL_Renderer* rend) {
    if (active) {
        SDL_Rect dst { x, y, w, h };
        SDL_RenderCopy(rend, menuTexture, NULL, &dst);
        Position sPos = RenderMenuOptions(rend);
        selector->RenderRelativeToSelection(rend, sPos);
    }
}

Position ActionMenu::RenderMenuOptions(SDL_Renderer* rend) {
    Position sPos;
    int yOffset = 0;
    int mx = x + (tileSize / 2);

    for (int i = 0; i < menuOptions.size(); i++) {
        Position tPos = TextManager::LoadFontAndPrint(rend, menuOptions[i].c_str(), mx, y + yOffset);
        yOffset += tileSize / 2;

        if (selector->GetSelectionIndex() == i) {
            sPos.x = tPos.x - (tPos.h / 2);
            sPos.y = tPos.y;
            sPos.w = tPos.h / 2;
            sPos.h = tPos.h;
        }
    }

    return sPos;
}

void ActionMenu::Update(int cursorX, int cursorY) {
    x = (cursorX * tileSize) + (tileSize * 1.5);
    y = cursorY * tileSize;
}

void ActionMenu::Update(Position pos) {
    x = pos.x;
    y = pos.y;
}

void ActionMenu::IncrementSelection() {
    selector->SetAndBoundCurrSelection(1);
}

void ActionMenu::DecrementSelection() {
    selector->SetAndBoundCurrSelection(-1);
}