#ifndef SRC_WEAPON_H_
#define SRC_WEAPON_H_

#include "Item.h"

class Weapon : public Item {
    public:
        Weapon(int range);

        int GetRange() { return range; };

    private:
        int range;
};

#endif /* SRC_WEAPON_H_ */