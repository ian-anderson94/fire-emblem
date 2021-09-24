#ifndef SRC_ACTORMANAGER_H_
#define SRC_ACTORMANAGER_H_

#include "Actor.h"
#include "SDL2/SDL.h"

#include <unordered_set>

using namespace std;

class EntityManager {
    public:
        EntityManager();
        void Render(SDL_Renderer* rend);

    private:
        unordered_set<Actor*> actors;
};

#endif /* SRC_ACTORMANAGER_H_ */
