#ifndef SRC_CLASSDEFINITIONS_H_
#define SRC_CLASSDEFINITIONS_H_

#include "Actor.h"
#include "BasicAI.h"
#include "Enemy.h"
#include "Enums.h"

#include <unordered_map>

class ClassDefinitions {
    public:
        static Actor* CreateWarrior(int tileSize);
        static Actor* CreatePaladin(int tileSize);
        static Actor* CreateHunter(int tileSize);
        static Actor* CreateRogue(int tileSize);
        static Actor* CreateMage(int tileSize);
        static Actor* CreatePriest(int tileSize);

        static Enemy* CreateEnemyFromEnum(Enums::EnemyType type, int tileSize, int spawnTurn, Map* map, vector<Actor*> actors, GridLocation coords);
        static Enemy* CreateSkeleton(int tileSize, int spawnTurn, Map* map, vector<Actor*> actors, GridLocation coords);
        static Enemy* CreateZombie(int tileSize, int spawnTurn, Map* map, vector<Actor*> actors, GridLocation coords);
};

#endif /* SRC_CLASSDEFINITIONS_H_ */