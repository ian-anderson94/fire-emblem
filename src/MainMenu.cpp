#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(int resX, int resY, int tileSize, TextManager* textManager) : Scene(resX, resY, tileSize) {
	screenCenterX = resX / 2;
	screenCenterY = resY / 2;
	currSelection = Enums::MMS_GameStart;

    mainMenuTextSize = 60;

    selectorVerticalOffset = 0;

    MainMenu::textManager = textManager;

    selectorTexture = TextureManager::loadTexture("./assets/selector_arrow.png");
	selectionsTexture = nullptr;

    const char* menuSelections[] = { "New Game", "Continue", "Options", "Exit" };
    const Enums::Scene sceneVals[] { Enums::SCN_HubMenu, Enums::SCN_HubMenu, Enums::SCN_HubMenu, Enums::SCN_HubMenu };

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
}

void MainMenu::Render(SDL_Renderer* rend){
	//renderMenu(rend);
    //renderSelector(rend);
    for (auto const& button : buttons) {
        button->Render(rend);
    }
}

void MainMenu::Update(double dt) {
    // Nothing atm
}

Enums::Scene MainMenu::HandleEvents(SDL_Event event) {
	InputManager* input = InputManager::getInstance();
	std::unordered_set<int> actions = input->getActionsDown();

    /*
	Enums::Scene menuSelectionValue = Enums::SCN_MainMenu;

	if (Globals::Contains(actions, Enums::ACTION_Up)) {
		currSelection--;
        selectorVerticalOffset -= resolutionY / 8;
		currSelection = boundCurrSelection();
	}
	else if (Globals::Contains(actions, Enums::ACTION_Down)) {
		currSelection++;
        selectorVerticalOffset += resolutionY / 8;
		currSelection = boundCurrSelection();
	}
	else if (Globals::Contains(actions, Enums::ACTION_Select)) {
		menuSelectionValue = MapMainMenuSelectionToScene();
	}
    */

    for (auto const& button : buttons) {
        Enums::Scene menuSelection = button->HandleEvents(event);
        if (menuSelection != Enums::SCN_NULL) {
            return menuSelection;
        }
    }

	return Enums::SCN_MainMenu;
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

void MainMenu::renderMenu(SDL_Renderer* rend) {
    SDL_Color white = { 255, 255, 255 };
    const char* fontFile = "fonts/OpenSans-Regular.ttf";
    const char* menuOptions[] = { "GAME START", "OPTIONS", "EXIT" };
    int verticalOffset = 0, x = 0, y = 0, w = 0, h = 0;

    for (int index = 0; index < (sizeof(menuOptions) / sizeof(menuOptions[0])); index++) {
        w = resX / 4;
        h = resY / 8;
        x = screenCenterX - (w / 2);
        y = screenCenterY - (h / 2) + verticalOffset;

        verticalOffset += h;

        textManager->LoadFontAndPrint(fontFile, mainMenuTextSize, menuOptions[index], white, x, y, w, h, rend);
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





