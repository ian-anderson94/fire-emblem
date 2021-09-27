#ifndef SRC_ACTOR_H_
#define SRC_ACTOR_H_

#include "SDL2/SDL.h"
#include "TextureManager.h"

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
        void RenderRelativeToViewport(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY);
        Position GetPosition() { return Position{x, y, size}; };
        Stats GetStats() { return stats; };
        SDL_Texture* GetIcon() { return iconTexture; };
        bool IsSelected() { return selected; };
        void SetSelected(bool val) { selected = val; };
        bool GetPlayerControlled() { return playerControlled; };
        void Move(int newX, int newY);

    private:
        int x, y, size;
        bool playerControlled, selected;
        Stats stats;

        const char* iconPath;
        const char* imagePath;
        const char* moveTilePath;
        SDL_Texture* moveTileTexture;
        SDL_Texture* iconTexture;
        SDL_Texture* actorTexture;

        void RenderPossibleMoves(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY);
};

#endif /* SRC_ACTOR_H_ */
