#ifndef SRC_BASICAI_H_
#define SRC_BASICAI_H_

#include "Actor.h"
#include "AIParadigm.h"

class BasicAI : public AIParadigm {
    public:
        Actor* IdentifyMostThreateningEnemy(unordered_map<Actor*, ThreatTable::ThreatStruct> threatTable);

    private:
};

#endif /* SRC_BASICAI_H_ */