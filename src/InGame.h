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
#include "PlayerAccount.h"
#include "Scene.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "TurnManager.h"
#include "ViewPort.h"

class InGame : public Scene {
    public:
        InGame(int resX, int resY, int tileSize);
        void Update(double dt);
        void Render(SDL_Renderer* rend);
        Enums::Scene HandleEvents(SDL_Event event);

        void PrintPositions();

    private:
        bool matchStarted;

        Actor* activeActor;
        Actor* selectedActor;
        Actor* actorUnderCursor;

        ActionMenu* actionMenu;
        ActorManager* actorManager;
        InformationPanel* infoPanel;
        GameCursor* cursor;
        PathingManager* pathingManager;
        ViewPort* viewPort;
        MapManager* mapManager;
        TurnManager* turnManager;

        void HandlePlayerTurn(SDL_Event event);
        void HandleEnemyTurn(SDL_Event event);

        void EndMatch() { matchStarted = false; };
        void StartMatch();
        void EndTurn();
        void MoveCursor(int dx, int dy);
};

#endif /* SRC_INGAME_H_ */
