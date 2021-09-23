#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(int resX, int resY, TextManager* textManager) {
	resolutionX = resX;
	resolutionY = resY;
	screenCenterX = resX / 2;
	screenCenterY = resY / 2;
	currSelection = Enums::MMS_GameStart;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 0;
	srcRect.h = 0;

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = 0;
	destRect.h = 0;

    mainMenuTextSize = 60;

    selectorVerticalOffset = 0;

    MainMenu::textManager = textManager;

	backgroundTexture = TextureManager::loadTexture("./assets/mainmenu_background.png");
    selectorTexture = TextureManager::loadTexture("./assets/selector_arrow.png");
	//selectionsTexture = TextureManager::loadTexture("assets/mainmenu_selections.png");
	selectionsTexture = nullptr;
}

MainMenu::~MainMenu() {

}

void MainMenu::render(SDL_Renderer* rend){
	renderBackground(rend);
	renderMenu(rend);
    renderSelector(rend);
}

void MainMenu::update(double dt) {
    // Nothing atm
}

int MainMenu::handleEvents(SDL_Event event) {
	InputManager* input = InputManager::getInstance();
	std::unordered_set<int> actions = input->getActionsDown();

	int menuSelectionValue = Enums::MMS_MainMenu;

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
		menuSelectionValue = currSelection;
	}

	return menuSelectionValue;
}

void MainMenu::renderBackground(SDL_Renderer* rend) {
	srcRect.w = destRect.w = resolutionX;
	srcRect.h = destRect.h = resolutionY;

	srcRect.x = srcRect.y = 0;
	destRect.x = destRect.y = 0;

	SDL_RenderCopy(rend, backgroundTexture, &srcRect, &destRect);
}

void MainMenu::renderMenu(SDL_Renderer* rend) {
    SDL_Color white = { 255, 255, 255 };
    const char* fontFile = "fonts/OpenSans-Regular.ttf";
    const char* menuOptions[] = { "GAME START", "OPTIONS", "EXIT" };
    int verticalOffset = 0, x = 0, y = 0, w = 0, h = 0;

    for (int index = 0; index < (sizeof(menuOptions) / sizeof(menuOptions[0])); index++) {
        w = resolutionX / 4;
        h = resolutionY / 8;
        x = screenCenterX - (w / 2);
        y = screenCenterY - (h / 2) + verticalOffset;

        verticalOffset += h;

        textManager->LoadFontAndPrint(fontFile, mainMenuTextSize, menuOptions[index], white, x, y, w, h, rend);
    }
}

void MainMenu::renderSelector(SDL_Renderer* rend) {
    int frame = AnimationManager::GetInstance()->GetFrameIndex(6);
    int selectorSize = resolutionY / 8;
    SDL_Rect src {0, 0, 0, 0};
    SDL_Rect dest {0, 0, 0, 0};

    src.x = frame * 64;
    src.y = 0;
    src.w = 64;
    src.h = 64;

    dest.w = dest.h = selectorSize;
    dest.x = screenCenterX - (resolutionX / 8) - (selectorSize * 2);
    dest.y = screenCenterY - (resolutionY / 16) + selectorVerticalOffset;

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





