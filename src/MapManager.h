#ifndef SRC_MAPMANAGER_H_
#define SRC_MAPMANAGER_H_

#include "Map.h"

class MapManager {
    public:
        Map* LoadMapFromFile(const char* file);

    private:
        Map* map;
};

#endif /* SRC_MAPMANAGER_H_ */