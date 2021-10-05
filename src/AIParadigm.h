#ifndef SRC_AIPARADIGM_H_
#define SRC_AIPARADIGM_H_

#include "Actor.h"
#include "ThreatTable.h"

class AIParadigm {
    public:
        virtual Actor* IdentifyMostThreateningEnemy(unordered_map<Actor*, ThreatTable::ThreatStruct> threatTable);

    private:
};

#endif /* SRC_AIPARADIGM_H_ */