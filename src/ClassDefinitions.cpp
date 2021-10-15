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
        "./assets/knight.png",
        "./assets/knight.png",
        0,
        0,
        tileSize,
        Actor::Stats {
            10, 10, 8, 8, 2, 1, 2, 3
        }
    );
}

Actor* ClassDefinitions::CreatePaladin(int tileSize) {

}

Actor* ClassDefinitions::CreateHunter(int tileSize) {
    
}

Actor* ClassDefinitions::CreateRogue(int tileSize) {
    
}

Actor* ClassDefinitions::CreateMage(int tileSize) {
    
}

Actor* ClassDefinitions::CreatePriest(int tileSize) {
    
}