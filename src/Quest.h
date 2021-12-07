#ifndef SRC_QUEST_H_
#define SRC_QUEST_H_

#include "Actor.h"
#include "ClassDefinitions.h"
#include "Enums.h"
#include "Item.h"

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Quest {
    public:
        Quest(Enums::QuestType type, Enums::QuestDifficulty difficulty, Enums::Biome biome, int tileSize);
        Enums::QuestDifficulty GetDifficulty() { return difficulty; };
        Enums::QuestType GetType() { return type; };
        Enums::Biome GetBiome() { return biome; };
        string GetTitle() { return title; };
        string GetMapFilePath() { return mapFilePath; };
        vector<pair<Enums::EnemyType, int>> GetEnemyBlueprint() { return enemyBlueprint; };

    private:
        vector<Item*> rewards;
        vector<pair<Enums::EnemyType, int>> enemyBlueprint;
        Enums::QuestDifficulty difficulty;
        Enums::QuestType type;
        Enums::Biome biome;
        string mapFilePath;
        string title;
        int tileSize;

        void GenerateAndScheduleEnemies();
        void GenerateMapFilePath();
        void GenerateTitle();
        void GenerateRewards();
};

#endif /* SRC_QUEST_H_ */