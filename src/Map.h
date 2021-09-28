#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "Tile.h"
#include "TileDefinition.h"

#include <string>
#include <exception>
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
        struct Dimensions {
            int w, h;
        };

        Map(vector<vector<string>> layout, unordered_map<string, TileDefinition*> tileDefinitions, int size);
        vector<Tile*> GetTilesInViewport(int xOffset, int yOffset, int wTiles, int hTiles, int camX, int camY);
        Tile* GetTile(int xPos, int yPos);
        vector<vector<string>> GetLayout() { return tileLayout; };
        Dimensions GetMapSize() { return Dimensions{ (int)tileLayout[1].size(), (int)tileLayout.size()}; };

    private:
        int tileSize;
        vector<vector<string>> tileLayout;
        unordered_map<string, TileDefinition*> tileDefinitions;

        vector<vector<Tile*>> tiles;
        vector<vector<Tile*>> ParseTilesFromLayout();

        void PrintLayout();
};

#endif /* SRC_MAP_H_ */