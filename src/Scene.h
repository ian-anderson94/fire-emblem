#ifndef SRC_SCENE_H_
#define SRC_SCENE_H_

#include "Enums.h"
#include "SDL2/SDL.h"

class Scene {
    public:
        Scene();
        virtual void Update();
        virtual void Render(SDL_Renderer* rend);
        virtual Enums::Scene HandleEvents(SDL_Event event);

    private:
        Enums::Scene sceneType;
};

#endif /* SRC_SCENE_H_ */