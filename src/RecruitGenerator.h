#ifndef SRC_RECRUITGENERATOR_H_
#define SRC_RECRUITGENERATOR_H_

#include "Actor.h"
#include "ClassDefinitions.h"

#include <unordered_map>
#include <vector>

class RecruitGenerator {
    public:
        RecruitGenerator(int tileSize);
        vector<Actor*> Generate(int count);

    private:
        int tileSize;
};

#endif /* SRC_RECRUITGENERATOR_H_ */