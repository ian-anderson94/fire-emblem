#include "MapManager.h"

MapManager::MapManager(int size) {
    tileSize = size;
    mapLoader = new MapLoader(tileSize);
}

void MapManager::LoadMapFromFile(const char* file) {
    map = mapLoader->Load(file);
}

void MapManager::Render(SDL_Renderer* rend, int xOffset, int yOffset, int wTiles, int hTiles, int camX, int camY) {
    vector<Tile*> tiles = map->GetTilesInViewport(xOffset, yOffset, wTiles, hTiles, camX, camY);

    for (auto const& tile : tiles) {
        tile->RenderRelativeToViewPort(rend, xOffset, yOffset, camX, camY);
    }
}
