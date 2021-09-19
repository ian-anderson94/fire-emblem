#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

MainMenu* Game::mainMenu;
//EntityManager* Game::entityManager;

int Game::currScene = Enums::Scene::SCENE_MainMenu;

Game::Game() {
	isRunning = true;
	window = NULL;
}

Game::~Game() {

}

void Game::init(const char* title, int windowXPos, int windowYPos, int windowWidth, int windowHeight, bool isFullscreen) {
	int flags = 0;

	// Use SDL_WINDOW_FULLSCREEN_DESKTOP instead of SDL_WINDOW_FULLSCREEN to enable alt-tab and closing window
	if (isFullscreen)
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;

	// Passing these args instead of SDL_INIT_EVERYTHING to address gdb crashing issue
	// SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_HAPTIC | SDL_INIT_HAPTIC | SDL_INIT_EVENTS
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, windowXPos, windowYPos, windowWidth, windowHeight, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		isRunning = true;
	} else {
		isRunning = false;
	}

	Game::mainMenu = new MainMenu(windowWidth, windowHeight);
	//Game::entityManager = new EntityManager(tileSize, Globals::RESOLUTION_X, Globals::RESOLUTION_Y);
}

void Game::update(double dt) {
	InputManager* input = InputManager::getInstance();
	input->update(Game::event);

	switch(Game::currScene) {
		case Enums::Scene::SCENE_MainMenu:
			break;
		case Enums::Scene::SCENE_InGame:
			//Game::entityManager->update(dt);
			break;
		case Enums::Scene::SCENE_PauseMenu:
			break;
		default:
			break;
	}
}

void Game::render(SDL_Renderer* rend) {
	SDL_RenderClear(rend);

	switch(Game::currScene) {
		case Enums::Scene::SCENE_MainMenu:
			Game::mainMenu->render(rend);
			break;
		case Enums::Scene::SCENE_InGame:
			//Game::entityManager->render(rend);
			break;
		case Enums::Scene::SCENE_PauseMenu:
			break;
		default:
			break;
	}

	SDL_RenderPresent(rend);
}

void Game::handleEvents() {
	switch(Game::currScene) {
	case Enums::Scene::SCENE_MainMenu:
		updateScene(mainMenu->handleEvents(Game::event));
		break;
	case Enums::Scene::SCENE_InGame:
		//updateScene(entityManager->handleEvents(Game::event));
		break;
	case Enums::Scene::SCENE_PauseMenu:
		break;
	default:
		break;
	}
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::updateScene(int menuSelection) {
	switch (menuSelection) {
	case Enums::MainMenuSelection::MMS_MainMenu:
		Game::currScene = Enums::Scene::SCENE_MainMenu;
		break;
	case Enums::MainMenuSelection::MMS_GameStart:
		Game::currScene = Enums::Scene::SCENE_InGame;
		break;
	case Enums::MainMenuSelection::MMS_Options:
		Game::currScene = Enums::Scene::SCENE_Options;
		break;
	case Enums::MainMenuSelection::MMS_Exit:
		isRunning = false;
		break;
	default:
		break;
	}
}
