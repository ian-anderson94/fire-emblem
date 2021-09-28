#include "Map.h"

Map::Map(vector<vector<string>> layout, unordered_map<string, TileDefinition*> tileDefs, int size) {
    tileLayout = layout;
    tileDefinitions = tileDefs;
    tileSize = size;

    tiles = ParseTilesFromLayout();
}

Tile* Map::GetTile(int row, int col) {
   if (col >= tiles.size() || row >= tiles[0].size()) {
       cout << printf("x: %d y: %d\n", row, col);
       throw invalid_argument("Tile not found\n");
   }

   return tiles[col][row];
}

vector<Tile*> Map::GetTilesInViewport(int xOffset, int yOffset, int wTiles, int hTiles, int camX, int camY) {
    vector<Tile*> tilesInRange;

   for (auto const& col : tiles) {
       for (auto const& tile : col) {
            Tile::Position tilePos = tile->GetPosition();

            if (tilePos.x >= camX && tilePos.x < camX + wTiles) {
                if (tilePos.y >= camY && tilePos.y < camY + hTiles) {
                    tilesInRange.push_back(tile);
                }
            }
        }
   }

    return tilesInRange;
}

vector<vector<Tile*>> Map::ParseTilesFromLayout() {
    vector<vector<Tile*>> tiles;

    for (int col = 0; col < tileLayout.size(); col++) {
        vector<Tile*> tileCol;

        for (int row = 0; row < tileLayout[col].size(); row++) {
            string currSymbol = tileLayout[col][row];
            tileCol.push_back(new Tile(tileDefinitions[currSymbol], row, col, tileSize));
        }

        tiles.push_back(tileCol);
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