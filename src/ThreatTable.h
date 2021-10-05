#ifndef SRC_THREATTABLE_H_
#define SRC_THREATTABLE_H_

#include "Actor.h"
#include "Utils.h"

#include <unordered_map>
#include <vector>

class ThreatTable {
    public:
        struct ThreatStruct {
            Actor* actor;
            int distance;
            int attackThreat;
            int spellThreat;
        };

        ThreatTable(vector<Actor*> actors, int xPos, int yPos);
        void Update(vector<Actor*> actors, int xPos, int yPos);

        unordered_map<Actor*, ThreatStruct> GetTable() { return threatTable; };

    private:
        unordered_map<Actor*, ThreatStruct> threatTable;
};

#endif /* SRC_THREATTABLE_H_ */