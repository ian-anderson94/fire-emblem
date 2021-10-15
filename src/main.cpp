#include "main.h"

Game* game = nullptr;
ResolutionManager* resolutionManager = nullptr;

int main(int argc, char* argv[]) {
	Uint32 minimum_t = 1000 / 6;
	Uint32 dt = 0;
	Uint32 last_t = 0;
	Uint32 curr_t = 0;

	game = new Game();

	resolutionManager = new ResolutionManager(argc, argv);

	game->init("GAME TITLE", resolutionManager);

	while (InputManager::getInstance()->isRunning()) {
		curr_t = SDL_GetTicks();

		if (last_t < curr_t) {
			dt = curr_t - last_t;

			if (dt > minimum_t)
				dt = minimum_t;

			game->handleEvents();

			game->update(dt / 1000.f);

			game->render(Game::renderer);


			last_t = curr_t;
		} else {
			SDL_Delay(1);
		}
	}

	game->clean();
	return 0;
}
