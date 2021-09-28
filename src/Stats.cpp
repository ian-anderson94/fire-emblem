#include "Stats.h"

Stats::Stats() {
    hp = hpMax = str = def = agi = spd = mov = 0;
}

Stats::Stats(int hp, int hpMax, int str, int def, int agi, int spd, int mov) {
    this->hp = hp;
    this->hpMax = hpMax;
    this->str = str;
    this->def = def;
    this->agi = agi;
    this->spd = spd;
    this->mov = mov;
}