#include "RecruitmentScreen.h"

RecruitmentScreen::RecruitmentScreen(int resX, int resY, int tileSize) : Scene(resX, resY, tileSize) {    
    currSelection = 0;

    actionMenu = new ActionMenu(menuOptions, tileSize);

    recruitGenerator = new RecruitGenerator(tileSize);
    recruitsAvailable = 4;
    maxRecruits = 4;

    RefreshRecruits(recruitsAvailable);
    CreateFrames();
}

void RecruitmentScreen::Update(double dt) {
    actionMenu->Update(frames[currSelection]->GetPosition());
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

        Position fPos = frames[i]->GetPosition();

        // If not nullptr, render recruit in frame. Otherwise render locked frame
        if (recruits[i]) {
            string recruitName = recruits[i]->GetName();
            string recruitLevel = "Lvl " + to_string(recruits[i]->GetLevel());

            float renderScale = 2 * scale;

            recruits[i]->SetPosition(fPos.x, fPos.y);
            recruits[i]->Render(rend, renderScale);

            Actor::Position rPos = recruits[i]->GetPosition();
            TextManager::LoadFontAndPrint(rend, recruitName.c_str(), rPos.x + (tileSize * renderScale), rPos.y);
            TextManager::LoadFontAndPrint(rend, recruitLevel.c_str(), rPos.x + (tileSize * renderScale), rPos.y + (tileSize / 2));
        } else {
            string unavailableString = "Unavailable";
            TextManager::LoadFontAndPrint(rend, unavailableString.c_str(), fPos.x, fPos.y);
        }
    }

    actionMenu->Render(rend);
}

Enums::Scene RecruitmentScreen::HandleEvents(SDL_Event event) {
    Enums::Scene currScene = Enums::SCN_HubRecruitment;

    InputManager* input = InputManager::getInstance();
	unordered_map<int, bool> actions = input->GetActionMap();

    if (actions[Enums::ACTION_Left]) {
        if (!actionMenu->IsActive()) {
            SetAndBoundCurrSelection(-1);
        }
    }

    if (actions[Enums::ACTION_Right]) {
        if (!actionMenu->IsActive()) {
            SetAndBoundCurrSelection(1);
        }
    }

    if (actions[Enums::ACTION_Up]) {
        if (!actionMenu->IsActive()) {
            SetAndBoundCurrSelection(-2);
        } else {
            actionMenu->DecrementSelection();
        }
    }

    if (actions[Enums::ACTION_Down]) {
        if (!actionMenu->IsActive()) {
            SetAndBoundCurrSelection(2);
        } else {
            actionMenu->IncrementSelection();
        }
    }

    if (actions[Enums::ACTION_Select]) {
        if (actionMenu->IsActive()) {
            int selection = actionMenu->GetSelection();

            switch (selection) {
                case Enums::AMR_Recruit: Recruit(); break;
                case Enums::AMR_Cancel: actionMenu->SetActive(false); break;
            }
        } else {
            if (recruits[currSelection]) {
                actionMenu->SetActive(true);
            }
        }
    }

    if (actions[Enums::ACTION_Cancel]) {
        if (actionMenu->IsActive()) {
            actionMenu->SetActive(false);
        } else {
            currScene = Enums::SCN_HubMenu;
        }
    }

    return currScene;
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

void RecruitmentScreen::Recruit() {
    PlayerAccount* account = PlayerAccount::GetInstance();
    account->AddToRoster(recruits[currSelection]);

    if ((int) account->GetParty().size() < account->GetMaxPartySize()) {
        account->AddToParty(recruits[currSelection]);
    }

    actionMenu->SetActive(false);
    recruits[currSelection] = nullptr;
}