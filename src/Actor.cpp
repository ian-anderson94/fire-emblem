#include "Actor.h"

Actor::Actor(const char* image, const char* icon, int xPos, int yPos, int ts, Stats actorStats, Enums::ClassType classType) {
    x = xDouble = xPos;
    y = yDouble = yPos;
    size = ts;
    stats = actorStats;

    level = 1;
    movespeed = 10;
    moving = false;
    selected = false;
    dead = false;
    planningMove = false;
    planningAttack = false;
    playerControlled = true;

    name = GetRandomName();

    equippedWeapon = new Weapon(1);

    actionsAvailable = {{Enums::TRN_Move, true}, {Enums::TRN_Attack, true}};

    imagePath = image;
    iconPath = icon;
    passableTilePath = "./assets/moveTile.png";
    impassableTilePath = "./assets/impassable_tile.png";
    passableTileTexture = TextureManager::loadTexture(passableTilePath);
    impassableTileTexture = TextureManager::loadTexture(impassableTilePath);
    actorTexture = TextureManager::loadTexture(imagePath);
    iconTexture = TextureManager::loadTexture(iconPath);

    spriteSheetFilePath = image;
    spriteSheetTexture = TextureManager::loadTexture(spriteSheetFilePath);

    idleRects = {
        SDL_Rect { 0, spriteFrameDimensions * 1, spriteFrameDimensions, spriteFrameDimensions},
        SDL_Rect { 0, spriteFrameDimensions * 2, spriteFrameDimensions, spriteFrameDimensions},
        SDL_Rect { 0, spriteFrameDimensions * 3, spriteFrameDimensions, spriteFrameDimensions}
    };

    walkLeftRects = {
        SDL_Rect { spriteFrameDimensions * 1, spriteFrameDimensions * 0, spriteFrameDimensions, spriteFrameDimensions },
        SDL_Rect { spriteFrameDimensions * 1, spriteFrameDimensions * 1, spriteFrameDimensions, spriteFrameDimensions },
        SDL_Rect { spriteFrameDimensions * 1, spriteFrameDimensions * 2, spriteFrameDimensions, spriteFrameDimensions },
        SDL_Rect { spriteFrameDimensions * 1, spriteFrameDimensions * 3, spriteFrameDimensions, spriteFrameDimensions }
    };

    walkDownRects = {
        SDL_Rect { spriteFrameDimensions * 2, spriteFrameDimensions * 0, spriteFrameDimensions, spriteFrameDimensions },
        SDL_Rect { spriteFrameDimensions * 2, spriteFrameDimensions * 1, spriteFrameDimensions, spriteFrameDimensions },
        SDL_Rect { spriteFrameDimensions * 2, spriteFrameDimensions * 2, spriteFrameDimensions, spriteFrameDimensions },
        SDL_Rect { spriteFrameDimensions * 2, spriteFrameDimensions * 3, spriteFrameDimensions, spriteFrameDimensions }
    };

    walkUpRects = {
        SDL_Rect { spriteFrameDimensions * 3, spriteFrameDimensions * 0, spriteFrameDimensions, spriteFrameDimensions },
        SDL_Rect { spriteFrameDimensions * 3, spriteFrameDimensions * 1, spriteFrameDimensions, spriteFrameDimensions },
        SDL_Rect { spriteFrameDimensions * 3, spriteFrameDimensions * 2, spriteFrameDimensions, spriteFrameDimensions },
        SDL_Rect { spriteFrameDimensions * 3, spriteFrameDimensions * 3, spriteFrameDimensions, spriteFrameDimensions }
    };

    selectedRects = {
        SDL_Rect { spriteFrameDimensions * 4, spriteFrameDimensions * 1, spriteFrameDimensions, spriteFrameDimensions},
        SDL_Rect { spriteFrameDimensions * 4, spriteFrameDimensions * 2, spriteFrameDimensions, spriteFrameDimensions},
        SDL_Rect { spriteFrameDimensions * 4, spriteFrameDimensions * 3, spriteFrameDimensions, spriteFrameDimensions}
    };

    SDL_SetTextureBlendMode(passableTileTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(impassableTileTexture, SDL_BLENDMODE_BLEND);

    SDL_SetTextureAlphaMod(passableTileTexture, 160);
    SDL_SetTextureAlphaMod(impassableTileTexture, 160);
}

void Actor::Render(SDL_Renderer* rend, float scale) {
    SDL_Rect src = GetSrcRect();

    SDL_Rect dst = (scale == 0) 
        ? SDL_Rect { x, y, size, size}
        : SDL_Rect { x, y, (int) (size * scale), (int) (size * scale)};

    SDL_RenderCopy(rend, actorTexture, &src, &dst);
}

void Actor::RenderRelativeToViewport(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY, int wTiles, int hTiles) {
    if (!dead) {
        if (planningMove) {
            RenderPossibleTiles(rend, xOffset, yOffset, camX, camY, wTiles, hTiles, stats.mov);
        }

        if (planningAttack) {
            RenderPossibleTiles(rend, xOffset, yOffset, camX, camY, wTiles, hTiles, equippedWeapon->GetRange());
        }

        SDL_Rect src = GetSrcRect();

        SDL_Rect dst {
            (int)((xDouble - camX) * size) + xOffset, 
            (int)((yDouble - camY) * size) + yOffset, 
            size, 
            size
        };

        SDL_RenderCopy(rend, actorTexture, &src, &dst);
    }
}

void Actor::RenderPossibleTiles(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY, int wTiles, int hTiles, int range) {
    list<pair<pair<int, int>, bool>> coords;
    int currX, currY;

    // Add possible moves to vector
    for (int i = (range * -1); i <= range; i++) {
        for (int j = (range * -1); j <= range; j++) {
            if (abs(i) + abs(j) <= range) {
                if ((x+i-camX) >= 0 && (x+i-camX) < wTiles && (y+j-camY) >= 0 && (y+j-camY) < hTiles) {
                    Tile* currTile = map->GetTile(x+i, y+j);
                    currX = ((x + i - camX) * size) + xOffset;
                    currY = ((y + j - camY) * size) + yOffset;
                    coords.push_back(
                        pair<pair<int, int>, bool>(
                            pair<int, int>(currX, currY), 
                            currTile->IsPassable() && !currTile->IsOccupied()
                        )
                    );
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

void Actor::Update(double dt, Map* map, vector<Actor*> actors) {
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
        xDouble += (size * dt) / movespeed;
        xDouble = xDouble >= waypoint.x ? waypoint.x : xDouble;
    } else {
        xDouble -= (size * dt) / movespeed;
        xDouble = xDouble <= waypoint.x ? waypoint.x : xDouble;
    }

    if (waypoint.y > y) {
        yDouble += (size * dt) / movespeed;
        yDouble = yDouble >= waypoint.y ? waypoint.y : yDouble;
    } else {
        yDouble -= (size * dt) / movespeed;
        yDouble = yDouble <= waypoint.y ? waypoint.y : yDouble;
    }

    if (xDouble == waypoint.x && yDouble == waypoint.y) {
        path.erase(path.begin());
        if (!path.empty()) {
            waypoint = path[0];
        }
    }
}

void Actor::Move(vector<GridLocation> path) {
    this->path = path;
    waypoint = path[0];
    moving = true;
}

void Actor::DoTurn() {

}

void Actor::ResetAvailableActions() {
    actionsAvailable[Enums::TRN_Move] = true;
    actionsAvailable[Enums::TRN_Attack] = true;
}

bool Actor::ActionsAvailable() {
    bool available = false;

    for (auto const& action : actionsAvailable) {
        if (action.second) {
            available = true;
        }
    }

    return available;
}

void Actor::Attack(Actor* target) {
    int damage = -1;

    target->ChangeHealth(damage);

    if (target->GetStats().health <= 0) {
        target->Kill();
    }
}

SDL_Rect Actor::GetSrcRect() {
    int frame = 0;
    SDL_Rect rect;

    if (moving) {
        // Walking
        frame = AnimationManager::GetInstance()->GetFrameIndex(walkLeftRects.size());
        rect = walkLeftRects[frame];
    } else if (planningAttack || planningMove) {
        // Selected
        frame = AnimationManager::GetInstance()->GetFrameIndex(selectedRects.size());
        rect = selectedRects[frame];
    } else {
        // Idle
        frame = AnimationManager::GetInstance()->GetFrameIndex(idleRects.size());
        rect = idleRects[frame];
    }

    return rect;
}

string Actor::GetRandomName() {
    return "Timmy";
}