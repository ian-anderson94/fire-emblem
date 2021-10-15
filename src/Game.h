#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "AnimationManager.h"
#include "Background.h"
#include "Enums.h"
#include "HubScreen.h"
#include "InGame.h"
#include "InputManager.h"
#include "MainMenu.h"
#include "ResolutionManager.h"
#include "TextManager.h"

#include <iostream>

class Game {
public:
	Game();
	virtual ~Game();

	void init(const char* title, ResolutionManager* resolutionManager);
	void update(double dt);
	void render(SDL_Renderer* rend);
	void handleEvents();
	void clean();

	bool getIsRunning() { return isRunning; };

    static Background* background;
    static HubScreen* hubScreen;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static MainMenu* mainMenu;
    static TextManager* textManager;
    static InGame* inGame;

	//static int currScene;

	static const int tileSize = 64;

private:
	bool isRunning;
	SDL_Window* window;

    Enums::Scene currScene;

	void updateScene(int menuSelection);

};

#endif /* SRC_GAME_H_ */
