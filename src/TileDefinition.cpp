#include "TileDefinition.h"
#include <iostream>

TileDefinition::TileDefinition(string l, string s, string f, bool p, Stats stats) {
    symbol = s;
    label = l;
    imageFile = f;
    passable = p;
    this->stats = stats;
}