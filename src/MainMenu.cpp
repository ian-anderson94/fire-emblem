#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(int resX, int resY, int tileSize) : Scene(resX, resY, tileSize) {
	screenCenterX = resX / 2;
	screenCenterY = resY / 2;
	currSelection = Enums::MMS_GameStart;

    xMenuAnchor = tileSize;
    yMenuAnchor = tileSize;

    selector = new Selector<Enums::Scene>(sceneVals);

    mainMenuTextSize = 60;
    selectorVerticalOffset = 0;

    selectorTexture = TextureManager::loadTexture("./assets/selector_arrow.png");
	selectionsTexture = nullptr;

    /*
    int buttonWidth = resX / 2;
    int buttonHeight = resY / 8;
    int buttonX = (resX - buttonWidth) / 2;
    int buttonY = resY / 4;
    int yOffset = 0, yIncrement = (resY / 16) + buttonHeight;

    for (int i = 0; i < sizeof(menuSelections) / sizeof(menuSelections[0]); i++) {
        Enums::Scene (*pFunc)(Enums::Scene);
        pFunc = &Button::GetSceneEnum;

        buttons.push_back(new MainMenuButton(
            menuSelections[i], 
            buttonX, buttonY + yOffset, 
            buttonWidth, 
            buttonHeight,
            Enums::SCN_MainMenu,
            sceneVals[i],
            pFunc
        ));

        yOffset += yIncrement;
    }
    */
}

void MainMenu::Render(SDL_Renderer* rend){
	//renderMenu(rend);
    //renderSelector(rend);

    /*
    for (auto const& button : buttons) {
        button->Render(rend);
    }
    */

   Position sPos = RenderMenuSelections(rend);
   selector->RenderRelativeToSelection(rend, sPos);
}

void MainMenu::Update(double dt) {
    // Nothing atm
}

Enums::Scene MainMenu::HandleEvents(SDL_Event event) {
    InputManager* input = InputManager::getInstance();
	unordered_map<int, bool> actions = input->GetActionMap();

    Enums::Scene menuSelectionValue = Enums::SCN_MainMenu;

    if (actions[Enums::ACTION_Up]) {
        selector->SetAndBoundCurrSelection(-1);
    }

    if (actions[Enums::ACTION_Down]) {
        selector->SetAndBoundCurrSelection(1);
    }

    if (actions[Enums::ACTION_Select]) {
        menuSelectionValue = selector->GetSelection();
    }

    return menuSelectionValue;

    /*
    InputManager* input = InputManager::getInstance();
    std::unordered_set<int> actions = input->getActionsDown();

    Enums::Scene menuSelectionValue = Enums::SCN_MainMenu;

    if (Globals::Contains(actions, Enums::ACTION_Up)) {
        currSelection--;
        selectorVerticalOffset -= resY / 8;
        currSelection = boundCurrSelection();
    }
    else if (Globals::Contains(actions, Enums::ACTION_Down)) {
        currSelection++;
        selectorVerticalOffset += resY / 8;
        currSelection = boundCurrSelection();
    }
    else if (Globals::Contains(actions, Enums::ACTION_Select)) {
        menuSelectionValue = MapMainMenuSelectionToScene();
    }
    */

    /*
    for (auto const& button : buttons) {
        Enums::Scene menuSelection = button->HandleEvents(event);
        if (menuSelection != Enums::SCN_NULL) {
            return menuSelection;
        }
    }

    return Enums::SCN_MainMenu;
    */

    //return menuSelectionValue;
}

Enums::Scene MainMenu::MapMainMenuSelectionToScene() {
    Enums::Scene scene;

    switch (currSelection) {
        case Enums::MMS_GameStart:
            scene = Enums::SCN_HubMenu;
            break;
    }

    return scene;
}

// Returns a position for the selector based on current selected option
Position MainMenu::RenderMenuSelections(SDL_Renderer* rend) {
    Position sPos;
    int yOffset = 0;
    int mx = xMenuAnchor + (tileSize / 2);

    for (int i = 0; i < (int) menuSelections.size(); i++) {
        Position tPos = TextManager::LoadFontAndPrint(rend, menuSelections[i].c_str(), mx, yMenuAnchor + yOffset);

        if (selector->GetSelectionIndex() == i) {
            sPos.x = xMenuAnchor - (tileSize / 2);
            sPos.y = yMenuAnchor + yOffset;
            sPos.w = tPos.h;
            sPos.h = tPos.h;
        }

        yOffset += tileSize / 2;
    }

    return sPos;
}

void MainMenu::renderMenu(SDL_Renderer* rend) {
    const char* menuOptions[] = { "GAME START", "OPTIONS", "EXIT" };
    int verticalOffset = 0, x = 0, y = 0, w = 0, h = 0;

    for (int index = 0; index < (sizeof(menuOptions) / sizeof(menuOptions[0])); index++) {
        w = resX / 4;
        h = resY / 8;
        x = screenCenterX - (w / 2);
        y = screenCenterY - (h / 2) + verticalOffset;

        verticalOffset += h;

        TextManager::LoadFontAndPrint(rend, menuOptions[index], x, y);
    }
}

void MainMenu::renderSelector(SDL_Renderer* rend) {
    int frame = AnimationManager::GetInstance()->GetFrameIndex(6);
    int selectorSize = resY / 8;
    SDL_Rect src {0, 0, 0, 0};
    SDL_Rect dest {0, 0, 0, 0};

    src.x = frame * 64;
    src.y = 0;
    src.w = 64;
    src.h = 64;

    dest.w = dest.h = selectorSize;
    dest.x = screenCenterX - (resX / 8) - (selectorSize * 2);
    dest.y = screenCenterY - (resY / 16) + selectorVerticalOffset;

    SDL_RenderCopy(rend, selectorTexture, &src, &dest);
}

int MainMenu::boundCurrSelection() {
	if (currSelection > Enums::MMS_Exit) {
		return Enums::MMS_GameStart;
	} else if (currSelection < Enums::MMS_GameStart) {
		return Enums::MMS_Exit;
	} else {
		return currSelection;
	}
}





