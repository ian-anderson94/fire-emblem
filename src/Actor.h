#ifndef SRC_ACTOR_H_
#define SRC_ACTOR_H_

#include "AnimationManager.h"
#include "Enums.h"
#include "GridLocation.h"
#include "Item.h"
#include "Map.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "Weapon.h"

#include <list>
#include <unordered_map>

using namespace std;

class Actor {
    public:
        struct Stats {
            int health, healthMax;
            int str, def, agi, intel, spd, mov;
        };

        struct Position {
            int x, y, size;
        };

        Actor(const char* image, const char* icon, int xPos, int yPos, int ts, Stats actorStats, Enums::ClassType classType = Enums::CLS_Warrior);
        void Render(SDL_Renderer* rend, float scale = 0);
        void RenderRelativeToViewport(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY, int wTiles, int hTiles);
        virtual void Update(double dt, Map* map, vector<Actor*> actor);

        Position GetPosition() { return Position{x, y, size}; };
        Stats GetStats() { return stats; };
        SDL_Texture* GetIcon() { return iconTexture; };
        //bool IsSelected() { return selected; };
        bool IsDead() { return dead; };
        bool IsMoving() { return moving; };
        bool IsPlanningMove() { return planningMove; };
        bool IsPlanningAttack() { return planningAttack; };
        bool IsPlayerControlled() { return playerControlled; };
        bool ActionsAvailable();
        string GetName() { return name; };
        int GetLevel() { return level; };
        void ResetAvailableActions();
        void UseAction(Enums::TurnAction action) { actionsAvailable[action] = false; };
        void SetSelected(bool val) { selected = val; };
        void SetPlanningMove(bool val) { planningMove = val; };
        void SetPlanningAttack(bool val) { planningAttack = val; };
        void SetPosition(int x, int y) { this->x = x; this->y = y; };
        void Move(vector<GridLocation> path);
        void Attack(Actor* target);
        void ChangeHealth(int delta) { stats.health += delta; };
        void Kill() { dead = true; };

        virtual void DoTurn();

    protected:
        int x, y, size, movespeed, level;
        double xDouble, yDouble;
        bool playerControlled, dead, selected, moving, planningMove, planningAttack;
        Stats stats;
        Enums::ClassType classType;
        string name;

        unordered_map<Enums::TurnAction, bool> actionsAvailable;
        vector<GridLocation> path;
        GridLocation waypoint;

        Weapon* equippedWeapon;

        const int spriteFrameDimensions = 32;
        const char* spriteSheetFilePath;
        const char* iconPath;
        const char* imagePath;
        const char* passableTilePath;
        const char* impassableTilePath;
        SDL_Texture* impassableTileTexture;
        SDL_Texture* passableTileTexture;
        SDL_Texture* iconTexture;
        SDL_Texture* actorTexture;
        SDL_Texture* spriteSheetTexture;

        vector<SDL_Rect> idleRects;
        vector<SDL_Rect> walkLeftRects;
        vector<SDL_Rect> walkRightRects;
        vector<SDL_Rect> walkUpRects;
        vector<SDL_Rect> walkDownRects;
        vector<SDL_Rect> selectedRects;
        Map* map;

        void RenderPossibleTiles(SDL_Renderer* rend, int xOffset, int yOffset, int camX, int camY, int wTiles, int hTiles, int range);
        void MoveToWaypoint(double dt);
        SDL_Rect GetSrcRect();
        string GetRandomName();
};

#endif /* SRC_ACTOR_H_ */
