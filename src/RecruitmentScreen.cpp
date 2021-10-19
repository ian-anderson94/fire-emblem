#include "RecruitmentScreen.h"

RecruitmentScreen::RecruitmentScreen(int resX, int resY, int tileSize) {
    this->resX = resX;
    this->resY = resY;
    this->tileSize = tileSize;

    recruitGenerator = new RecruitGenerator(tileSize);
    recruitsAvailable = 2;
    maxRecruits = 4;

    RefreshRecruits(recruitsAvailable);
}

void RecruitmentScreen::Render(SDL_Renderer* rend) {
    int xOffset = resX / 4;
    int yOffset = resY / 4;

    CreateAndRenderRecruitFrame(rend, recruits[0], xOffset, yOffset);
    CreateAndRenderRecruitFrame(rend, recruits[1], xOffset * 3, yOffset);
    CreateAndRenderRecruitFrame(rend, recruits[2], xOffset, yOffset * 3);
    CreateAndRenderRecruitFrame(rend, recruits[3], xOffset * 3, yOffset * 3);
}

Enums::Scene RecruitmentScreen::HandleEvents(SDL_Event event) {
    return Enums::SCN_HubRecruitment;
}

void RecruitmentScreen::RefreshRecruits(int count) {
    recruits = recruitGenerator->Generate(recruitsAvailable);

    // Add nullptr to recruits vector to indicate that slot hasn't been unlocked
    for (int i = recruitsAvailable; i < maxRecruits; i++) {
        recruits[i] = nullptr;
    }
}

void RecruitmentScreen::CreateAndRenderRecruitFrame(SDL_Renderer* rend, Actor* recruit, int frameX, int frameY) {
    // Render recruit if not nullptr, locked slot otherwise
    if (recruit) {
        int sizeFactor = 4;
        std::string recruitName = recruit->GetName();
        std::string recruitLevel = std::to_string(recruit->GetLevel());

        recruit->SetPosition(frameX, frameY);
        recruit->Render(rend, sizeFactor);

        TextManager::LoadFontAndPrint(rend, recruitName.c_str(), frameX, frameY + (tileSize * sizeFactor), tileSize * sizeFactor, tileSize);
        TextManager::LoadFontAndPrint(rend, recruitLevel.c_str(), frameX, frameY + (tileSize * sizeFactor) + tileSize, tileSize * sizeFactor, tileSize);
    }
}