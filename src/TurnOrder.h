#ifndef SRC_TURNORDER_H_
#define SRC_TURNORDER_H_

#include "Actor.h"
#include "SDL2/SDL.h"
#include "TextureManager.h"

#include <list>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class TurnOrder {
    public:
        TurnOrder(int resX, int resY, int tileSize);
        void GenerateTurnOrder(unordered_set<Actor*> actors);
        void Render(SDL_Renderer* rend);
        bool Empty();
        Actor* GetNext();

    private:
        void RenderBar(SDL_Renderer* rend);
        void RenderIcons(SDL_Renderer* rend);

        class Comparator {
            public:
                bool operator() (pair<int, Actor*> left, pair<int, Actor*> right) {
                    if (left.first >= right.first) {
                        return true;
                    }
                    
                    return false;
                };
        };

        priority_queue<pair<int, Actor*>, vector<pair<int, Actor*>>, Comparator> turnOrder;
        const char* imagePath;
        SDL_Texture* turnOrderTexture;
        int x, y, w, h, resX, resY, tileSize;
};

#endif /* SRC_TURNORDER_H_ */