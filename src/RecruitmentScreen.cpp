#include "RecruitmentScreen.h"

RecruitmentScreen::RecruitmentScreen(int resX, int resY, int tileSize) {
    this->resX = resX;
    this->resY = resY;
    this->tileSize = tileSize;
    
    currSelection = 0;

    recruitGenerator = new RecruitGenerator(tileSize);
    recruitsAvailable = 4;
    maxRecruits = 4;

    RefreshRecruits(recruitsAvailable);
    CreateFrames();
}

void RecruitmentScreen::Render(SDL_Renderer* rend) {
    for (int i = 0; i < maxRecruits; i++) {
        float scale = 1;

        if (currSelection == i) {
            scale = 1.1;
        } else {
            scale = 1;
        }

        frames[i]->Render(rend, scale);

        // If not nullptr, render recruit in frame. Otherwise render locked frame
        if (recruits[i]) {
            Position fPos = frames[i]->GetPosition();
            string recruitName = recruits[i]->GetName();
            string recruitLevel = "Lvl " + to_string(recruits[i]->GetLevel());

            float renderScale = 2 * scale;

            recruits[i]->SetPosition(fPos.x, fPos.y);
            recruits[i]->Render(rend, renderScale);

            Actor::Position rPos = recruits[i]->GetPosition();
            TextManager::LoadFontAndPrint(rend, recruitName.c_str(), rPos.x + (tileSize * renderScale), rPos.y);
            TextManager::LoadFontAndPrint(rend, recruitLevel.c_str(), rPos.x + (tileSize * renderScale), rPos.y + (tileSize / 2));
        } else {
            // TODO: Render locked frame
        }
    }
}

Enums::Scene RecruitmentScreen::HandleEvents(SDL_Event event) {
    InputManager* input = InputManager::getInstance();
	unordered_map<int, bool> actions = input->GetActionMap();

    if (actions[Enums::ACTION_Left]) {
        SetAndBoundCurrSelection(-1);
    }

    if (actions[Enums::ACTION_Right]) {
        SetAndBoundCurrSelection(1);
    }

    if (actions[Enums::ACTION_Up]) {
        SetAndBoundCurrSelection(-2);
    }

    if (actions[Enums::ACTION_Down]) {
        SetAndBoundCurrSelection(2);
    }

    if (actions[Enums::ACTION_Select]) {

    }

    if (actions[Enums::ACTION_Cancel]) {

    }

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

    int frameWidth = halfResX - (tileSize * 2);
    int frameHeight = halfResY - (tileSize * 2);

    Position pos1 { halfTs , halfTs, frameWidth, frameHeight };
    Position pos2 { halfTs + halfResX , halfTs, frameWidth, frameHeight };
    Position pos3 { halfTs , halfTs + halfResY, frameWidth, frameHeight };
    Position pos4 { halfTs + halfResX , halfTs + halfResY, frameWidth, frameHeight };

    frames.push_back(new Frame(pos1));
    frames.push_back(new Frame(pos2));
    frames.push_back(new Frame(pos3));
    frames.push_back(new Frame(pos4));
}

void RecruitmentScreen::SetAndBoundCurrSelection(int delta) {
    currSelection += delta;

    if (currSelection < 0) {
        currSelection = maxRecruits - abs(currSelection);
    } else if (currSelection >= maxRecruits) {
        currSelection = 0 + (currSelection - maxRecruits);
    }
}