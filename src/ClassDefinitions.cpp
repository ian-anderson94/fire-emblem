#include "ClassDefinitions.h"

/********************
    -- Stats --
    health
    healthMax
    strength
    defense
    agility
    intelligence
    speed
    move
********************/

Actor* ClassDefinitions::CreateWarrior(int tileSize) {
    return new Actor(
        "./assets/PH_warrior.png",
        "./assets/PH_warrior.png",
        0,
        0,
        tileSize,
        Actor::Stats {
            10, 10, 8, 8, 2, 1, 2, 3
        }
    );
}

Actor* ClassDefinitions::CreatePaladin(int tileSize) {
    return new Actor(
        "./assets/PH_paladin.png",
        "./assets/PH_paladin.png",
        0,
        0,
        tileSize,
        Actor::Stats {
            12, 12, 7, 9, 2, 1, 3, 2
        }
    );
}

Actor* ClassDefinitions::CreateHunter(int tileSize) {
    return new Actor(
        "./assets/PH_hunter.png",
        "./assets/PH_hunter.png",
        0,
        0,
        tileSize,
        Actor::Stats {
            9, 9, 4, 5, 7, 2, 4, 3
        }
    );
}

Actor* ClassDefinitions::CreateRogue(int tileSize) {
    return new Actor(
        "./assets/PH_rogue.png",
        "./assets/PH_rogue.png",
        0,
        0,
        tileSize,
        Actor::Stats {
            6, 6, 4, 4, 9, 4, 4, 4
        }
    );    
}

Actor* ClassDefinitions::CreateMage(int tileSize) {
    return new Actor(
        "./assets/PH_mage.png",
        "./assets/PH_mage.png",
        0,
        0,
        tileSize,
        Actor::Stats {
            6, 6, 2, 5, 2, 9, 4, 3
        }
    );    
}

Actor* ClassDefinitions::CreatePriest(int tileSize) {
    return new Actor(
        "./assets/PH_priest.png",
        "./assets/PH_priest.png",
        0,
        0,
        tileSize,
        Actor::Stats {
            7, 7, 1, 5, 2, 7, 4, 2
        }
    );    
}

Enemy* ClassDefinitions::CreateEnemyFromEnum(Enums::EnemyType type, int tileSize, int spawnTurn, Map* map, vector<Actor*> actors, GridLocation coords) {
    Enemy* enemy = nullptr;
    
    switch (type) {
        case Enums::ENM_Skeleton: enemy = ClassDefinitions::CreateSkeleton(tileSize, spawnTurn, map, actors, coords); break;
        case Enums::ENM_Zombie: enemy = ClassDefinitions::CreateZombie(tileSize, spawnTurn, map, actors, coords); break;
    }

    return enemy;
}

Enemy* ClassDefinitions::CreateSkeleton(int tileSize, int spawnTurn, Map* map, vector<Actor*> actors, GridLocation coords) {
    return new Enemy(
      "./assets/PH_rogue.png",
      "./assets/PH_rogue.png",
      coords.x,
      coords.y,
      tileSize,
      Actor::Stats {
          2, 2, 2, 2, 2, 2, 2, 2
      },
      map,
      new BasicAI(),
      actors,
      spawnTurn  
    );
}

Enemy* ClassDefinitions::CreateZombie(int tileSize, int spawnTurn, Map* map, vector<Actor*> actors, GridLocation coords) {
    return new Enemy(
      "./assets/PH_warrior.png",
      "./assets/PH_warrior.png",
      coords.x,
      coords.y,
      tileSize,
      Actor::Stats {
          3, 3, 3, 3, 3, 3, 2, 2
      },
      map,
      new BasicAI(),
      actors,
      spawnTurn  
    );
}