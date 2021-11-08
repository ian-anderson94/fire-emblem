#include "Quest.h"

Quest::Quest(Enums::QuestType type, Enums::QuestDifficulty difficulty, Enums::Biome biome) {
    this->difficulty = difficulty;
    this->type = type;
    this->biome = biome;

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

void Quest::GenerateRewards() {

}