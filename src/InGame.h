#ifndef SRC_INGAME_H_
#define SRC_INGAME_H_

#include "ActionMenu.h"
#include "Actor.h"
#include "ActorManager.h"
#include "BasicAI.h"
#include "Enemy.h"
#include "GameCursor.h"
#include "GridLocation.h"
#include "InformationPanel.h"
#include "InputManager.h"
#include "MapManager.h"
#include "PathingManager.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "TurnManager.h"
#include "ViewPort.h"

class InGame {
    public:
        InGame(int resX, int resY, int ts);
        void Update(double dt);
        void Render(SDL_Renderer* rend);
        int HandleEvents(SDL_Event event);

        void PrintPositions();

    private:
        int resolutionX;
        int resolutionY;
        int tileSize;

        Actor* activeActor;
        Actor* selectedActor;
        Actor* actorUnderCursor;

        ActionMenu* actionMenu;
        ActorManager* actorManager;
        InformationPanel* infoPanel;
        GameCursor* cursor;
        PathingManager* pathingManager;
        ViewPort* viewPort;
        const char* backgroundTextureFile;
        SDL_Texture* backgroundTexture;
        MapManager* mapManager;
        TurnManager* turnManager;

        void RenderBackground(SDL_Renderer* rend);
        void HandlePlayerTurn(SDL_Event event);
        void HandleEnemyTurn(SDL_Event event);

        void MoveCursorUp();
        void MoveCursorDown();
        void MoveCursorLeft();
        void MoveCursorRight();
};

#endif /* SRC_INGAME_H_ */
