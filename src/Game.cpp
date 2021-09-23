#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

InGame* Game::inGame;
TextManager* Game::textManager;
MainMenu* Game::mainMenu;
//EntityManager* Game::entityManager;

int Game::currScene = Enums::SCENE_MainMenu;

Game::Game() {
	isRunning = true;
	window = NULL;
}

Game::~Game() {

}

void Game::init(const char* title, ResolutionManager* resolutionManager) {
	int flags = 0;

	// Passing these args instead of SDL_INIT_EVERYTHING to address gdb crashing issue
	// SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_HAPTIC | SDL_INIT_HAPTIC | SDL_INIT_EVENTS
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		TTF_Init();

		// Use SDL_WINDOW_FULLSCREEN_DESKTOP instead of SDL_WINDOW_FULLSCREEN to enable alt-tab and closing window
		if (resolutionManager->GetFlag(Enums::CLF_Fullscreen)) {
			flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
			resolutionManager->SetResolutionToFullscreenValues();
		}

		window = SDL_CreateWindow(
				title,
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				resolutionManager->GetFlag(Enums::CLF_xResolution),
				resolutionManager->GetFlag(Enums::CLF_yResolution),
				flags);

		renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_RenderSetLogicalSize(renderer,
				resolutionManager->GetFlag(Enums::CLF_xResolution),
				resolutionManager->GetFlag(Enums::CLF_yResolution));

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		isRunning = true;
	} else {
		isRunning = false;
	}

    Game::textManager = new TextManager();
	Game::mainMenu = new MainMenu(resolutionManager->GetFlag(Enums::CLF_xResolution), resolutionManager->GetFlag(Enums::CLF_yResolution), textManager);
    Game::inGame = new InGame(resolutionManager->GetFlag(Enums::CLF_xResolution), resolutionManager->GetFlag(Enums::CLF_yResolution), tileSize);
	//Game::entityManager = new EntityManager(tileSize, Globals::RESOLUTION_X, Globals::RESOLUTION_Y);
}

void Game::update(double dt) {
	InputManager* input = InputManager::getInstance();
	input->update(Game::event);

    AnimationManager::GetInstance()->TickAnimationTimer(dt);

	switch(Game::currScene) {
		case Enums::SCENE_MainMenu:
            mainMenu->update(dt);
			break;
		case Enums::SCENE_InGame:
			//Game::entityManager->update(dt);
			break;
		case Enums::SCENE_PauseMenu:
			break;
		default:
			break;
	}
}

void Game::render(SDL_Renderer* rend) {
	SDL_RenderClear(rend);

	switch(Game::currScene) {
		case Enums::SCENE_MainMenu:
			Game::mainMenu->render(rend);
			break;
		case Enums::SCENE_InGame:
            Game::inGame->Render(rend);
			//Game::entityManager->render(rend);
			break;
		case Enums::SCENE_PauseMenu:
			break;
		default:
			break;
	}

	SDL_RenderPresent(rend);
}

void Game::handleEvents() {
	switch(Game::currScene) {
	case Enums::SCENE_MainMenu:
		updateScene(mainMenu->handleEvents(Game::event));
		break;
	case Enums::SCENE_InGame:
		//updateScene(entityManager->handleEvents(Game::event));
        updateScene(inGame->HandleEvents(Game::event));
		break;
	case Enums::SCENE_PauseMenu:
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
	case Enums::MMS_MainMenu:
		Game::currScene = Enums::SCENE_MainMenu;
		break;
	case Enums::MMS_GameStart:
		Game::currScene = Enums::SCENE_InGame;
		break;
	case Enums::MMS_Options:
		Game::currScene = Enums::SCENE_Options;
		break;
	case Enums::MMS_Exit:
		isRunning = false;
		break;
	default:
		break;
	}
}
