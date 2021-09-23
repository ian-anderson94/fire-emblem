#include "Map.h"

Map::Map(vector<vector<string>> layout, unordered_map<string, TileDefinition*> tileDefs, int size) {
    tileLayout = layout;
    tileDefinitions = tileDefs;
    tileSize = size;

    tiles = ParseTilesFromLayout();
}

vector<Tile*> Map::GetTilesInViewport(int xOffset, int yOffset, int wTiles, int hTiles, int camX, int camY) {
    vector<Tile*> tilesInRange;

    for (auto const& tile : tiles) {
        Tile::Position tilePos = tile->GetPosition();

        if (tilePos.x >= camX && tilePos.x < camX + wTiles) {
            if (tilePos.y >= camY && tilePos.y < camY + hTiles) {
                tilesInRange.push_back(tile);
            }
        }

        // Account for ViewPort's offset
        /*
        int currX = currTilePos.x + x;
        int currY = currTilePos.y + y;

        if (currX >= x && currX + currTilePos.size <= x + w) {
            if (currY >= y && currY + currTilePos.size <= y + h) {
                tilesInRange.push_back(tile);
            }
        }
        */
    }

    return tilesInRange;
}

vector<Tile*> Map::ParseTilesFromLayout() {
    vector<Tile*> tiles;

    for (int col = 0; col < tileLayout.size(); col++) {
        for (int row = 0; row < tileLayout[col].size(); row++) {
            string currSymbol = tileLayout[col][row];
            //tiles.push_back(new Tile(tileDefinitions[currSymbol], row * tileSize, col * tileSize, tileSize));
            tiles.push_back(new Tile(tileDefinitions[currSymbol], row, col, tileSize));
        }
    }

    return tiles;
}

void Map::PrintLayout() {
    for (auto const& row : tileLayout) {
        for (auto const& c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
}