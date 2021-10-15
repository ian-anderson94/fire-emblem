#ifndef SRC_CLASSDEFINITIONS_H_
#define SRC_CLASSDEFINITIONS_H_

#include "Actor.h"
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
};

#endif /* SRC_CLASSDEFINITIONS_H_ */