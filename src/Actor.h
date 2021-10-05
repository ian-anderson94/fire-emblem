#ifndef SRC_ACTOR_H_
#define SRC_ACTOR_H_

#include "GridLocation.h"
#include "Map.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"

#include <list>

using namespace std;

class Actor {
    public:
        struct Stats {
            int health, healthMax;
            int str, def, agi, spd, mov;
        };

        struct Position {
            int x, y, size;
        };

        Actor(const char* image, const char* icon, int xPos, int yPos, int ts, Stats actorStats);
        void RenderRelativeToViewport(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY, int wTiles, int hTiles);
        virtual void Update(double dt, Map* map, vector<Actor*> actor);

        Position GetPosition() { return Position{x, y, size}; };
        Stats GetStats() { return stats; };
        SDL_Texture* GetIcon() { return iconTexture; };
        bool IsSelected() { return selected; };
        bool IsMoving() { return moving; };
        bool IsPlayerControlled() { return playerControlled; };
        void SetSelected(bool val) { selected = val; };
        void Move(vector<GridLocation> path);

        virtual void DoTurn();

    protected:
        int x, y, size, movespeed;
        double xDouble, yDouble;
        bool playerControlled, selected, moving;
        Stats stats;

        vector<GridLocation> path;
        GridLocation waypoint;

        const char* iconPath;
        const char* imagePath;
        const char* passableTilePath;
        const char* impassableTilePath;
        SDL_Texture* impassableTileTexture;
        SDL_Texture* passableTileTexture;
        SDL_Texture* iconTexture;
        SDL_Texture* actorTexture;
        Map* map;

        void RenderPossibleMoves(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY, int wTiles, int hTiles);
        void MoveToWaypoint(double dt);
};

#endif /* SRC_ACTOR_H_ */
