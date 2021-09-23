#include "TileDefinition.h"

TileDefinition::TileDefinition(string l, string s, string f, bool p, string a) {
    symbol = s;
    label = l;
    imageFile = f;
    passable = p;
    attributes = a;
}