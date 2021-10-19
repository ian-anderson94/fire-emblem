#ifndef SRC_RECRUITMENTSCREEN_H_
#define SRC_RECRUITMENTSCREEN_H_

#include "RecruitGenerator.h"
#include "TextManager.h"

#include <string>
#include <vector>

class RecruitmentScreen {
    public:
        RecruitmentScreen(int resX, int resY, int tileSize);
        void Render(SDL_Renderer* rend);
        Enums::Scene HandleEvents(SDL_Event event);

    private:
        int resX, resY, tileSize, recruitsAvailable, maxRecruits;
        vector<Actor*> recruits;
        RecruitGenerator* recruitGenerator;

        void RefreshRecruits(int count);
        void CreateAndRenderRecruitFrame(SDL_Renderer* rend, Actor* recruit, int frameX, int frameY);
};

#endif /* SRC_RECRUITMENTSCREEN_H_ */