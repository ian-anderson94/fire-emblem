#include "RecruitGenerator.h"

RecruitGenerator::RecruitGenerator(int tileSize) {
    this->tileSize = tileSize;
}

vector<Actor*> RecruitGenerator::Generate(int count) {
    vector<Actor*> recruits;

    for (int i = 0; i < count; i++) {
        int classTypeId = rand() % Enums::CLS_LAST;

        switch (classTypeId) {
            case Enums::CLS_Warrior: recruits.push_back(ClassDefinitions::CreateWarrior(tileSize)); break;
            case Enums::CLS_Paladin: recruits.push_back(ClassDefinitions::CreatePaladin(tileSize)); break;
            case Enums::CLS_Hunter: recruits.push_back(ClassDefinitions::CreateHunter(tileSize)); break;
            case Enums::CLS_Rogue: recruits.push_back(ClassDefinitions::CreateRogue(tileSize)); break;
            case Enums::CLS_Mage: recruits.push_back(ClassDefinitions::CreateMage(tileSize)); break;
            case Enums::CLS_Priest: recruits.push_back(ClassDefinitions::CreatePriest(tileSize)); break;
            default: throw invalid_argument("Class not supported\n");
        }
    }

    return recruits;
}