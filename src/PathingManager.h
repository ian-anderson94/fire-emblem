#ifndef SRC_PATHINGMANAGER_H_
#define SRC_PATHINGMANAGER_H_

#include "Map.h"

class PathingManager {
    public:
        PathingManager(Map* map);
        
        void Update(Map* map);

    private:
        Map* map;

        void CalculatePath(int actorX, int actorY, int cursorX, int cursorY);
};

#endif /* SRC_PATHINGMANAGER_H_ */