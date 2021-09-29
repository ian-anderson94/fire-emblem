#include "PathingManager.h"

PathingManager::PathingManager(Map* map) {
    this->map = map;
}

void PathingManager::Update(Map* map) {
    this->map = map;
}

// Calculates a path between two specified points (i.e. the selected actor and the cursor)
void PathingManager::CalculatePath(int startX, int startY, int endX, int endY) {
    GridLocation start = GridLocation{startX, startY};
    GridLocation end = GridLocation{endX, endY};

    vector<GridLocation> path = AStarSearch(start, end);

    PrintPath(path);
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