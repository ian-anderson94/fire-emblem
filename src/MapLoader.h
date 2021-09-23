#ifndef SRC_MAPLOADER_H_
#define SRC_MAPLOADER_H_

#include "Map.h"
#include "MapLoader.h"
#include "TileDefinition.h"
#include "Utils.h"

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <regex>
#include <tuple>

using namespace std;

class MapLoader {
    public:
        MapLoader(int size);
        Map* Load(const char* file);

    private:
        unordered_map<string, vector<string>> LoadAndParseFileIntoGroups(const char* file);
        TileDefinition* CreateTileDefinitionFromGroup(string label, vector<string> definition);
        vector<vector<string>> ParseLayout(vector<string> layout);

        vector<string> reservedLabels;
        string baseAssetPath;
        int tileSize;
};

#endif /* SRC_MAPLOADER_H_ */