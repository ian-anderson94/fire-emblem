#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "MainMenu.h"
#include "Enums.h"
//#include "EntityManager.h"

#include "InputManager.h"
#include <iostream>

class Game {
public:
	Game();
	virtual ~Game();

	void init(const char* title, int windowXPos, int windowYPos, int windowWidth, int windowHeight, bool isFullscreen);
	void update(double dt);
	void render(SDL_Renderer* rend);
	void handleEvents();
	void clean();

	bool getIsRunning() { return isRunning; };

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static MainMenu* mainMenu;
	//static EntityManager* entityManager;

	static int currScene;

	static const int tileSize = 32;

private:
	bool isRunning;
	SDL_Window* window;

	void updateScene(int menuSelection);

};

#endif /* SRC_GAME_H_ */
