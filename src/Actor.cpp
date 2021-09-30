#include "Actor.h"

Actor::Actor(const char* image, const char* icon, int xPos, int yPos, int ts, Stats actorStats) {
    x = xDouble = xPos;
    y = yDouble = yPos;
    size = ts;
    stats = actorStats;

    moving = false;
    selected = false;
    playerControlled = true;

    imagePath = image;
    iconPath = icon;
    passableTilePath = "./assets/moveTile.png";
    impassableTilePath = "./assets/impassable_tile.png";
    passableTileTexture = TextureManager::loadTexture(passableTilePath);
    impassableTileTexture = TextureManager::loadTexture(impassableTilePath);
    actorTexture = TextureManager::loadTexture(imagePath);
    iconTexture = TextureManager::loadTexture(iconPath);

    SDL_SetTextureBlendMode(passableTileTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(impassableTileTexture, SDL_BLENDMODE_BLEND);

    SDL_SetTextureAlphaMod(passableTileTexture, 160);
    SDL_SetTextureAlphaMod(impassableTileTexture, 160);
}

void Actor::RenderRelativeToViewport(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY, int wTiles, int hTiles) {
    if (selected) {
        RenderPossibleMoves(rend, xOffset, yOffset, camX, camY, wTiles, hTiles);
    }

    SDL_Rect dst {
        (int)((xDouble - camX) * size) + xOffset, 
        (int)((yDouble - camY) * size) + yOffset, 
        size, 
        size
    };

    SDL_RenderCopy(rend, actorTexture, NULL, &dst);
}

void Actor::RenderPossibleMoves(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY, int wTiles, int hTiles) {
    list<pair<pair<int, int>, bool>> coords;
    int currX, currY;

    // Add possible moves to vector
    for (int i = (stats.mov * -1); i <= stats.mov; i++) {
        for (int j = (stats.mov * -1); j <= stats.mov; j++) {
            if (abs(i) + abs(j) <= stats.mov) {
                if ((x+i-camX) >= 0 && (x+i-camX) < wTiles && (y+j-camY) >= 0 && (y+j-camY) < hTiles) {
                    Tile* currTile = map->GetTile(x+i, y+j);
                    currX = ((x + i - camX) * size) + xOffset;
                    currY = ((y + j - camY) * size) + yOffset;
                    coords.push_back(pair<pair<int, int>, bool>(pair<int, int>(currX, currY), currTile->IsPassable()));
                }
            }
        }
    }

    // Only render those that are on screen
    for (auto const& kvp : coords) {
        if (kvp.first.first >= camX * size && kvp.first.second >= camY * size) {
            if (kvp.first.first <= (camX + wTiles) * size + xOffset && kvp.first.second <= (camY + hTiles) * size + yOffset) {
               SDL_Rect dst {kvp.first.first, kvp.first.second, size, size};
               kvp.second ? SDL_RenderCopy(rend, passableTileTexture, NULL, &dst) : SDL_RenderCopy(rend, impassableTileTexture, NULL, &dst);
            }
        }
    }
}

void Actor::Update(double dt, Map* map) {
    this->map = map;

    if (!path.empty()) {
        MoveToWaypoint(dt);
    } else {
        moving = false;
        x = (int) xDouble;
        y = (int) yDouble;
    }
}

void Actor::MoveToWaypoint(double dt) {
    if (waypoint.x > xDouble) {
        xDouble += size * dt;
        xDouble = xDouble >= waypoint.x ? waypoint.x : xDouble;
    } else {
        xDouble -= size * dt;
        xDouble = xDouble <= waypoint.x ? waypoint.x : xDouble;
    }

    if (waypoint.y > y) {
        yDouble += size * dt;
        yDouble = yDouble >= waypoint.y ? waypoint.y : yDouble;
    } else {
        yDouble -= size * dt;
        yDouble = yDouble <= waypoint.y ? waypoint.y : yDouble;
    }

    if (xDouble == waypoint.x && yDouble == waypoint.y) {
        path.erase(path.begin());
        if (!path.empty()) {
            waypoint = path[0];
        }
    }
}

void Actor::Move(GridLocation dst, vector<GridLocation> path) {
    this->path = path;
    waypoint = path[0];
    moving = true;
    /*
    x = dst.x;
    y = dst.y;
    */
}
