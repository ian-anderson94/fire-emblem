#ifndef SRC_MOUSE_H_
#define SRC_MOUSE_H_

#include "SDL2/SDL.h"

class Mouse {
    public:
        struct Position {
            int x, y;
        };

        static Position GetPosition();
};

#endif /* SRC_MOUSE_H_ */