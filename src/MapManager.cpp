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

void MapManager::SetTilesOccupied(unordered_set<Actor*> actors) {
    map->SetTilesUnoccupied();

    for (auto const& actor : actors) {
        SetTilesOccupied(actor);
    }
}

void MapManager::SetTilesOccupied(Actor* actor) {
    Actor::Position actorPos = actor->GetPosition();
    GetTile(actorPos.x, actorPos.y)->SetOccupied(true);
}
