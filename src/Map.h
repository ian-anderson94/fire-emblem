#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "Tile.h"
#include "TileDefinition.h"

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <regex>
#include <tuple>

using namespace std;

class Map {
    public:
        Map(vector<vector<string>> layout, unordered_map<string, TileDefinition*> tileDefinitions, int size);
        vector<Tile*> GetTilesInViewport(int xOffset, int yOffset, int wTiles, int hTiles, int camX, int camY);
        vector<vector<string>> GetLayout() { return tileLayout; };

    private:
        int tileSize;
        vector<Tile*> tiles;
        vector<vector<string>> tileLayout;
        unordered_map<string, TileDefinition*> tileDefinitions;

        vector<Tile*> ParseTilesFromLayout();

        void PrintLayout();
};

#endif /* SRC_MAP_H_ */