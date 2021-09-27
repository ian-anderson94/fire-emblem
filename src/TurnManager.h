#ifndef SRC_TURNMANAGER_H_
#define SRC_TURNMANAGER_H_

#include "Actor.h"
#include "TurnOrder.h"

#include <unordered_set>

using namespace std;

class TurnManager {
    public:
        TurnManager(int resX, int resY, int tileSize);

        bool IsCurrentTurnOver() { return isCurrentTurnOver; };
        void EndTurn() { isCurrentTurnOver = true; };

        Actor* GetNextTurn(unordered_set<Actor*> actors);
        void Render(SDL_Renderer* rend);

    private:
        int resX, resY, tileSize;
        bool isCurrentTurnOver;

        TurnOrder* turnOrder;
};

#endif /* SRC_TURNMANAGER_H_ */