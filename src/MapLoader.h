#ifndef SRC_MAPLOADER_H_
#define SRC_MAPLOADER_H_

#include "Map.h"
#include "MapLoader.h"
#include "TileDefinition.h"
#include "Utils.h"
#include "Stats.h"

#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <regex>
#include <tuple>
#include <utility>

using namespace std;

class MapLoader {
    public:
        MapLoader(int size);
        Map* Load(const char* file);

    private:
        unordered_map<string, vector<string>> LoadAndParseFileIntoGroups(const char* file);
        TileDefinition* CreateTileDefinitionFromGroup(string label, vector<string> definition);
        vector<vector<string>> ParseLayout(vector<string> layout);
        vector<pair<int, int>> ParsePlayerSpawns(vector<string> playerSpawns);
        Stats ParseStats(string attributes);

        vector<string> reservedLabels;
        string baseAssetPath;
        int tileSize;
};

#endif /* SRC_MAPLOADER_H_ */