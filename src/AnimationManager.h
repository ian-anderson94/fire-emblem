#ifndef SRC_ANIMATIONMANAGER_H_
#define SRC_ANIMATIONMANAGER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <math.h>

class AnimationManager {
    public:
        void TickAnimationTimer(double dt);
        int GetFrameIndex(int framesInTexture);

        static AnimationManager* GetInstance();

    private:
        double animationTimer = 0;
        double animationTimerMax = 1.0;

        static AnimationManager* instance;
};

#endif /* SRC_ANIMATIONMANAGER_H_ */
