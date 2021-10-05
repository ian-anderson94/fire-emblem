#ifndef SRC_ACTORMANAGER_H_
#define SRC_ACTORMANAGER_H_

#include "Actor.h"
#include "Map.h"
#include "SDL2/SDL.h"

#include <unordered_set>
#include <vector>

using namespace std;

class ActorManager {
    public:
        ActorManager(int resolutionX, int resolutionY, int tileSize);
        void Render(SDL_Renderer* rend, int xOffset, int yOffset, int wTiles, int hTiles, int camX, int camY);
        void Update(double dt, Map* map);

        bool AnyActorsMoving();

        void Add(Actor* actor) { actors.insert(actor); };
        Actor* GetActor(int xPos, int yPos);
        unordered_set<Actor*> GetAllActors() { return actors; };
        vector<Actor*> GetPlayerControlled();

    private:
        unordered_set<Actor*> actors;
        int resX, resY, tileSize;

        vector<Actor*> GetActorsInViewport(int xOffset, int yOffset, int wTiles, int hTiles, int camX, int camY);
};

#endif /* SRC_ACTORMANAGER_H_ */
