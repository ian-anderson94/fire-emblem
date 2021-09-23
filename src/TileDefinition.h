#ifndef SRC_TILEDEFINITION_H_
#define SRC_TILEDEFINITION_H_

#include "SDL2/SDL.h"

#include <string>

using namespace std;

class TileDefinition {
    public:
        TileDefinition(string l, string s, string f, bool p, string a);

        string GetSymbol() { return symbol; };
        string GetImageFile() { return imageFile; };
        bool GetPassable() { return passable; };

    private:
        string symbol;
        string label;
        string imageFile;
        bool passable;
        string attributes;
};

#endif /* SRC_TILEDEFINITION_H_ */