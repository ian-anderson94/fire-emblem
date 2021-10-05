#ifndef SRC_PATHINGMANAGER_H_
#define SRC_PATHINGMANAGER_H_

#include "GridLocation.h"
#include "Map.h"
#include "PriorityQueue.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "Tile.h"

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class PathingManager {
    public:
        PathingManager(Map* map, int tileSize);

        void CalculatePath(int actorX, int actorY, int cursorX, int cursorY);
        void Update(Map* map);
        void Render(SDL_Renderer* rend, int camX, int camY, int xOffset, int yOffset);
        void TrimPath();

        vector<GridLocation> GetPath() { return currPath; };

    private:
        int tileSize;
        Map* map;
        vector<GridLocation> currPath;

        const char* arrowHeadImagePath = "./assets/arrow_head.png";
        const char* arrowBodyImagePath = "./assets/arrow_body.png";
        const char* arrowTurnImagePath = "./assets/arrow_left_up_turn.png";
        const char* arrowButtImagePath = "./assets/arrow_end.png";

        SDL_Texture* arrowHeadTexture;
        SDL_Texture* arrowBodyTexture;
        SDL_Texture* arrowTurnTexture;
        SDL_Texture* arrowButtTexture;

        vector<GridLocation> AStarSearch(GridLocation start, GridLocation end);
        vector<GridLocation> GetNeighbors(GridLocation curr);
        vector<GridLocation> ReconstructPath(GridLocation start, GridLocation end, unordered_map<GridLocation, GridLocation> visitedLocations);
        int CalculateHeuristic(GridLocation left, GridLocation right);
        int CalculateCost(GridLocation left, GridLocation right);
        bool InBounds(int x, int y);

        void PrintPath(vector<GridLocation> path);
};

#endif /* SRC_PATHINGMANAGER_H_ */