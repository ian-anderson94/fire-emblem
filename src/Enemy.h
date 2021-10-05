#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include "Actor.h"
#include "AIParadigm.h"
#include "Map.h"
#include "PathingManager.h"

#include <iostream>

class Enemy : public Actor {
    public:
        Enemy(const char* image, const char* icon, int xPos, int yPos, int ts, Stats actorStats, Map* map, AIParadigm* paradigm, vector<Actor*> actors);
        void DoTurn();

        void Update(double dt, Map* map, vector<Actor*> actors);

    private:
        AIParadigm* paradigm;
        Map* map;
        PathingManager* pathingManager;
        ThreatTable* threatTable;

        vector<Actor*> actors;
};

#endif /* SRC_ENEMY_H_ */