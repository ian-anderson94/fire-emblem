#ifndef SRC_RECRUITMENTSCREEN_H_
#define SRC_RECRUITMENTSCREEN_H_

#include "RecruitGenerator.h"

#include <vector>

class RecruitmentScreen {
    public:
        RecruitmentScreen(int resX, int resY, int tileSize);
        void Render(SDL_Renderer* rend);

    private:
        int resX, resY, tileSize, recruitsAvailable;
        vector<Actor*> recruits;
        RecruitGenerator* recruitGenerator;

        void RefreshRecruits(int count);
};

#endif /* SRC_RECRUITMENTSCREEN_H_ */