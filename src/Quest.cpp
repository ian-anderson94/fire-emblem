#include "Quest.h"

Quest::Quest(Enums::QuestType type, Enums::QuestDifficulty difficulty, Enums::Biome biome) {
    this->difficulty = difficulty;
    this->type = type;
    this->biome = biome;

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

void Quest::GenerateRewards() {

}