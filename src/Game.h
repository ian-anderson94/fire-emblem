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
#include "QuestBoard.h"
#include "RecruitmentScreen.h"
#include "ResolutionManager.h"
#include "Scene.h"
#include "TextManager.h"

#include <iostream>
#include <unordered_map>

using namespace std;

class Game {
public:
	Game();

	void init(const char* title, ResolutionManager* resolutionManager);
	void update(double dt);
	void render(SDL_Renderer* rend);
	void handleEvents();
	void clean();

	bool getIsRunning() { return isRunning; };

    static Background* background;
    static SDL_Renderer* renderer;
	static SDL_Event event;
    static TextManager* textManager;

	static const int tileSize = 64;

private:
	bool isRunning;
	SDL_Window* window;
    Enums::Scene currScene;
    unordered_map<Enums::Scene, Scene*> scenes;
};

#endif /* SRC_GAME_H_ */
