#ifndef SRC_MAINMENU_H_
#define SRC_MAINMENU_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "TextManager.h"
#include "AnimationManager.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Enums.h"

#include <unordered_set>

class MainMenu {

public:
	MainMenu(int resX, int resY, TextManager* textManager);
	virtual ~MainMenu();

	void update(double dt);
	void render(SDL_Renderer* rend);
	int handleEvents(SDL_Event event);

private:
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Texture* backgroundTexture;
	SDL_Texture* selectionsTexture;
    SDL_Texture* selectorTexture;

    TextManager* textManager;

	int resolutionX;
	int resolutionY;
	int screenCenterX;
	int screenCenterY;
	int currSelection;
    int selectorVerticalOffset;
    int mainMenuTextSize;

	void renderBackground(SDL_Renderer* rend);
	void renderMenu(SDL_Renderer* rend);
    void renderSelector(SDL_Renderer* rend);

	int boundCurrSelection();
};

#endif /* SRC_MAINMENU_H_ */
