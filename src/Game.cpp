#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
Background* Game::background = nullptr;
TextManager* Game::textManager = nullptr;
SDL_Event Game::event;

Game::Game() {
	isRunning = true;
	window = NULL;

    currScene = Enums::SCN_MainMenu;
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

    int xResolution = resolutionManager->GetFlag(Enums::CLF_xResolution);
    int yResolution = resolutionManager->GetFlag(Enums::CLF_yResolution);

    scenes.insert(pair<Enums::Scene, Scene*>(Enums::SCN_MainMenu, new MainMenu(xResolution, yResolution, tileSize)));
    scenes.insert(pair<Enums::Scene, Scene*>(Enums::SCN_HubMenu, new HubScreen(xResolution, yResolution, tileSize)));
    scenes.insert(pair<Enums::Scene, Scene*>(Enums::SCN_HubRecruitment, new RecruitmentScreen(xResolution, yResolution, tileSize)));
    scenes.insert(pair<Enums::Scene, Scene*>(Enums::SCN_InGame, new InGame(xResolution, yResolution, tileSize)));

    Game::background = new Background(xResolution, yResolution);
    Game::textManager = new TextManager();
}

void Game::update(double dt) {
	InputManager* input = InputManager::getInstance();
	input->update(Game::event);

    AnimationManager::GetInstance()->TickAnimationTimer(dt);

    scenes[currScene]->Update(dt);
}

void Game::render(SDL_Renderer* rend) {
	SDL_RenderClear(rend);
    background->Render(rend);
    scenes[currScene]->Render(rend);
	SDL_RenderPresent(rend);
}

void Game::handleEvents() {
    currScene = scenes[currScene]->HandleEvents(Game::event);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
