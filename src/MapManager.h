#ifndef SRC_MAPMANAGER_H_
#define SRC_MAPMANAGER_H_

#include "Actor.h"
#include "Map.h"
#include "MapLoader.h"

#include <unordered_set>
#include <utility>

class MapManager {
    public:
        MapManager(int size);
        void LoadMapFromFile(const char* file);
        void Render(SDL_Renderer* rend, int xOffset, int yOffset, int vpWidth, int vpHeight, int camX, int camY);
        void SetTilesOccupied(unordered_set<Actor*> actors);
        void SetTilesOccupied(Actor* actor);
        Map::Dimensions GetMapSize() { return map->GetMapSize(); };
        vector<pair<int, int>> GetPlayerSpawns() { return map->GetPlayerSpawns(); };

        Tile* GetTile(int xPos, int yPos) { return map->GetTile(xPos, yPos); };
        Map* GetMap() { return map; };

    private:
        Map* map;
        MapLoader* mapLoader;
        int tileSize;
};

#endif /* SRC_MAPMANAGER_H_ */