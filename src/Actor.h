#ifndef SRC_ACTOR_H_
#define SRC_ACTOR_H_

#include "SDL2/SDL.h"

class Actor {
    public:
        Actor();
        void Render(SDL_Renderer* rend);

    private:
        int x, y, size;
};

#endif /* SRC_ACTOR_H_ */
