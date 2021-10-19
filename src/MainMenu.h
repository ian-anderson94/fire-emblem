#ifndef SRC_MAINMENU_H_
#define SRC_MAINMENU_H_

#include "AnimationManager.h"
#include "MainMenuButton.h"
#include "Enums.h"
#include "InputManager.h"
#include "Mouse.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "TextManager.h"
#include "TextureManager.h"

#include <unordered_set>
#include <vector>

class MainMenu {

public:
	MainMenu(int resX, int resY, TextManager* textManager);
	virtual ~MainMenu();

	void update(double dt);
	void render(SDL_Renderer* rend);
	Enums::Scene handleEvents(SDL_Event event);

private:
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Texture* selectionsTexture;
    SDL_Texture* selectorTexture;

    TextManager* textManager;
    vector<Button*> buttons;

	int resolutionX;
	int resolutionY;
	int screenCenterX;
	int screenCenterY;
	int currSelection;
    int selectorVerticalOffset;
    int mainMenuTextSize;

	void renderMenu(SDL_Renderer* rend);
    void renderSelector(SDL_Renderer* rend);
    Enums::Scene MapMainMenuSelectionToScene();

	int boundCurrSelection();
};

#endif /* SRC_MAINMENU_H_ */
