#include "RecruitmentScreen.h"

RecruitmentScreen::RecruitmentScreen(int resX, int resY, int tileSize) {
    this->resX = resX;
    this->resY = resY;
    this->tileSize = tileSize;

    recruitGenerator = new RecruitGenerator(tileSize);
    recruitsAvailable = 2;

    RefreshRecruits(recruitsAvailable);
}

void RecruitmentScreen::Render(SDL_Renderer* rend) {
    
}

void RecruitmentScreen::RefreshRecruits(int count) {
    recruits = recruitGenerator->Generate(2);
}