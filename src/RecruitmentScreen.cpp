#include "RecruitmentScreen.h"

RecruitmentScreen::RecruitmentScreen(int resX, int resY, int tileSize) {
    this->resX = resX;
    this->resY = resY;
    this->tileSize = tileSize;

    recruitGenerator = new RecruitGenerator(tileSize);
    recruitsAvailable = 4;
    maxRecruits = 4;

    RefreshRecruits(recruitsAvailable);
    CreateFrames();
}

void RecruitmentScreen::Render(SDL_Renderer* rend) {
    for (int i = 0; i < maxRecruits; i++) {
        frames[i]->Render(rend);

        // If not nullptr, render recruit in frame. Otherwise render locked frame
        if (recruits[i]) {
            Position fPos = frames[i]->GetPosition();
            string recruitName = recruits[i]->GetName();
            string recruitLevel = "Lvl " + to_string(recruits[i]->GetLevel());

            recruits[i]->SetPosition(fPos.x, fPos.y);
            recruits[i]->Render(rend, 1);

            TextManager::LoadFontAndPrint(rend, recruitName.c_str(), fPos.x + tileSize, fPos.y);
            TextManager::LoadFontAndPrint(rend, recruitLevel.c_str(), fPos.x + tileSize, fPos.y + (tileSize / 2));
        } else {
            // TODO: Render locked frame
        }
    }
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

void RecruitmentScreen::CreateFrames() {
    int halfTs = tileSize;
    int halfResX = resX / 2;
    int halfResY = resY / 2;

    int frameWidth = halfResX - tileSize;
    int frameHeight = halfResY - tileSize;

    Position pos1 { halfTs , halfTs, frameWidth, frameHeight };
    Position pos2 { halfTs + halfResX , halfTs, frameWidth, frameHeight };
    Position pos3 { halfTs , halfTs + halfResY, frameWidth, frameHeight };
    Position pos4 { halfTs + halfResX , halfTs + halfResY, frameWidth, frameHeight };

    frames.push_back(new Frame(pos1));
    frames.push_back(new Frame(pos2));
    frames.push_back(new Frame(pos3));
    frames.push_back(new Frame(pos4));
}