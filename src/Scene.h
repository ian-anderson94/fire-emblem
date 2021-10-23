#ifndef SRC_SCENE_H_
#define SRC_SCENE_H_

#include "Enums.h"
#include "SDL2/SDL.h"

class Scene {
    public:
        Scene(int resX, int resY, int tileSize);
        virtual void Update(double dt) = 0;
        virtual void Render(SDL_Renderer* rend) = 0;
        virtual Enums::Scene HandleEvents(SDL_Event event) = 0;

    protected:
        Enums::Scene sceneType;
        int resX, resY, tileSize;
};

#endif /* SRC_SCENE_H_ */