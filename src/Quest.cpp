#include "Quest.h"

Quest::Quest(Enums::QuestType type, Enums::QuestDifficulty difficulty, Enums::Biome biome, int tileSize) {
    this->difficulty = difficulty;
    this->type = type;
    this->biome = biome;
    this->tileSize = tileSize;

    GenerateAndScheduleEnemies();
    GenerateMapFilePath();
    GenerateTitle();
    GenerateRewards();
}

void Quest::GenerateTitle() {
    switch(biome) {
        case Enums::BIO_Graveyard: title = "Elimation: Zombies!"; break;
        case Enums::BIO_Forest: title = "Eliminaton: Wildlife!"; break;
        case Enums::BIO_Tomb: title = "Elimination: The Undead!"; break;
    }
}

void Quest::GenerateMapFilePath() {
    switch (biome) {
        case Enums::BIO_Graveyard: mapFilePath = "./maps/graveyard.txt"; break;
        case Enums::BIO_Forest: mapFilePath = "./maps/forest.txt"; break;
        case Enums::BIO_Tomb: mapFilePath = "./maps/tomb.txt"; break;
    }
}

void Quest::GenerateAndScheduleEnemies() {
    // Place starting enemies into vector
    switch (difficulty) {
        case Enums::QDF_Easy:
            // Push pair containing enemy type and the turn that enemy should spawn.
            cout << "adding enemies to blueprint" << endl;
            enemyBlueprint.push_back(pair<Enums::EnemyType, int>(Enums::ENM_Skeleton, 0));
            enemyBlueprint.push_back(pair<Enums::EnemyType, int>(Enums::ENM_Skeleton, 0));
            enemyBlueprint.push_back(pair<Enums::EnemyType, int>(Enums::ENM_Zombie, 0));
            enemyBlueprint.push_back(pair<Enums::EnemyType, int>(Enums::ENM_Zombie, 0));
            break;
        case Enums::QDF_Medium:
            break;
        case Enums::QDF_Hard:
            break;
    }

    // Add additional spawns with later turn value
}

void Quest::GenerateRewards() {

}