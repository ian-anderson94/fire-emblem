#include "PathingManager.h"

PathingManager::PathingManager(Map* map, int tileSize) {
    this->map = map;
    this->tileSize = tileSize;

    arrowHeadTexture = TextureManager::loadTexture(arrowHeadImagePath);
    arrowBodyTexture = TextureManager::loadTexture(arrowBodyImagePath);
    arrowTurnTexture = TextureManager::loadTexture(arrowTurnImagePath);
    arrowButtTexture = TextureManager::loadTexture(arrowButtImagePath);
}

void PathingManager::Update(Map* map) {
    this->map = map;
}

void PathingManager::Render(SDL_Renderer* rend, int camX, int camY, int xOffset, int yOffset) {
    SDL_Texture* currTex = nullptr;
    GridLocation nullStruct = GridLocation {-1, -1};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    int angle = 0;

    for (int index = 0; index < currPath.size(); index++) {
        GridLocation prev = nullStruct, curr = nullStruct, next = nullStruct;

        curr = currPath[index];
        if (index > 0) prev = currPath[index - 1];
        if (index < currPath.size() - 1) next = currPath[index + 1];

        angle = 0;
        flip = SDL_FLIP_NONE;

        // First tile in path
        if (prev == nullStruct) {
            currTex = arrowButtTexture;

            if (next.x > curr.x) {
                angle = 0;
            } else if (next.y > curr.y) {
                angle = 90;
            } else if (next.x < curr.x) {
                angle = 180;
            } else if (next.y < curr.y) {
                angle = 270;
            }
        }

        // Last tile in path
        else if (next == nullStruct) {
            currTex = arrowHeadTexture;

            if (curr.x > prev.x) {
                angle = 0;
            } else if (curr.y > prev.y) {
                angle = 90;
            } else if (curr.x < prev.x) {
                angle = 180;
            } else if (curr.y < prev.y) {
                angle = 270;
            }
        }

        // Tiles are in straight line
        else if (prev.x == next.x || prev.y == next.y) {
            currTex = arrowBodyTexture;

            if (prev.y == next.y) {
                angle = 0;
            } else {
                angle = 90;
            }        }

        // Turn
        else {
            currTex = arrowTurnTexture;

            if ((prev.x < curr.x && next.y < curr.y) || (prev.y < curr.y && next.x < curr.x)) {
                flip = SDL_FLIP_NONE;
            } else if ((prev.y < curr.y && next.x > curr.x) || (next.y < curr.y && prev.x > curr.x)) {
                flip = SDL_FLIP_HORIZONTAL;
            } else if ((prev.x > curr.x && next.y > curr.y) || (prev.y > curr.y && next.x > curr.x)) {
                flip = (SDL_RendererFlip) (SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL);
            } else if ((prev.y > curr.y && next.x < curr.x) || (prev.x < curr.x && next.y > curr.y)) {
                angle = SDL_FLIP_VERTICAL;
            }
        }

        SDL_Rect dst {
            ((currPath[index].x - camX) * tileSize) + xOffset,
            ((currPath[index].y - camY) * tileSize) + yOffset,
            tileSize,
            tileSize
        };

        SDL_RenderCopyEx(rend, currTex, NULL, &dst, angle, NULL, flip);
    }
}

// Calculates a path between two specified points (i.e. the selected actor and the cursor)
void PathingManager::CalculatePath(int startX, int startY, int endX, int endY) {
    GridLocation start = GridLocation{startX, startY};
    GridLocation end = GridLocation{endX, endY};

    currPath = AStarSearch(start, end);
}

vector<GridLocation> PathingManager::AStarSearch(GridLocation start, GridLocation end) {
    unordered_map<GridLocation, GridLocation> visitedLocations;
    unordered_map<GridLocation, int> costSoFar;
    PriorityQueue<GridLocation, int> frontier;

    frontier.put(start, 0);

    visitedLocations[start] = start;
    costSoFar[start] = 0;

    while (!frontier.empty()) {
        GridLocation curr = frontier.get();

        if (curr == end) {
            break;
        }

        vector<GridLocation> neighbors = GetNeighbors(curr);

        for (GridLocation next : neighbors) {
            int newCost = costSoFar[curr] + CalculateCost(curr, next);

            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                costSoFar[next] = newCost;

                int priority = newCost + CalculateHeuristic(next, end);
                frontier.put(next, priority);
                visitedLocations[next] = curr;
            }
        }
    }

    return ReconstructPath(start, end, visitedLocations);
}

vector<GridLocation> PathingManager::ReconstructPath(GridLocation start, GridLocation end, unordered_map<GridLocation, GridLocation> visitedLocations) {
    vector<GridLocation> path;
    GridLocation curr = end;

    while (curr != start) {
        path.push_back(curr);
        curr = visitedLocations[curr];
    }

    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}

vector<GridLocation> PathingManager::GetNeighbors(GridLocation curr) {
    vector<GridLocation> neighbors;
    Tile* currTile = nullptr;
    
    if (InBounds(curr.x - 1, curr.y)) {
        currTile = map->GetTile(curr.x - 1, curr.y);

        if (currTile->IsPassable()) {
            GridLocation neighbor = GridLocation{curr.x - 1, curr.y};
            neighbors.push_back(neighbor);
        }
    }

    if (InBounds(curr.x + 1, curr.y)) {
        currTile = map->GetTile(curr.x + 1, curr.y);

        if (currTile->IsPassable()) {
            GridLocation neighbor = GridLocation{curr.x + 1, curr.y};
            neighbors.push_back(neighbor);
        }
    }

    if (InBounds(curr.x, curr.y - 1)) {
        currTile = map->GetTile(curr.x, curr.y - 1);

        if (currTile->IsPassable()) {
            GridLocation neighbor = GridLocation{curr.x, curr.y - 1};
            neighbors.push_back(neighbor);
        }
    }

    if (InBounds(curr.x, curr.y + 1)) {
        currTile = map->GetTile(curr.x, curr.y + 1);

        if (currTile->IsPassable()) {
            GridLocation neighbor = GridLocation{curr.x, curr.y + 1};
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

bool PathingManager::InBounds(int x, int y) {
    Map::Dimensions mapDimensions = map->GetMapSize();

    if (x >= 0 && x < mapDimensions.w) {
        if (y >= 0 && y < mapDimensions.h) {
            return true;
        }
    }

    return false;
}

int PathingManager::CalculateCost(GridLocation left, GridLocation right) {
    return 1;
}

// Manhattan distance = |x1 - x2| + |y1 - y2|
int PathingManager::CalculateHeuristic(GridLocation left, GridLocation right) {
    return abs(left.x - right.x) + abs(left.y - right.y);
}

void PathingManager::TrimPath() {
    currPath.pop_back();
}

void PathingManager::PrintPath(vector<GridLocation> path) {
    string val = "PATH: ";

    for (auto const& coordPair : path) {
        val += "{";
        val += to_string(coordPair.x);
        val += ",";
        val += to_string(coordPair.y);
        val += "}, ";
    }

    cout << val << endl;
}