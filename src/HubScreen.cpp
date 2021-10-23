#include "HubScreen.h"

HubScreen::HubScreen(int resX, int resY, int tileSize) {
    this->resX = resX;
    this->resY = resY,
    this->tileSize = tileSize;

    currSelection = Enums::HUB_Embark;
    recruitmentImagePath = "./assets/PH_house.png";
    embarkImagePath = "./assets/embark.png";

    selectionTextures.insert(pair<Enums::HubSelection, SDL_Texture*>(Enums::HUB_Recruitment, TextureManager::loadTexture(recruitmentImagePath)));
    selectionTextures.insert(pair<Enums::HubSelection, SDL_Texture*>(Enums::HUB_Embark, TextureManager::loadTexture(embarkImagePath)));

}

void HubScreen::Render(SDL_Renderer* rend) {
    int xOffset = 0;
    int sizeFactor = 2;

    for (auto const& kvp : selectionTextures) {
        xOffset += tileSize * 4;
        sizeFactor = 2;

        if (currSelection == kvp.first) {
            sizeFactor = 3;
        }

        SDL_Rect dst {xOffset, resY / 2, tileSize * sizeFactor, tileSize * sizeFactor};

        SDL_RenderCopy(rend, kvp.second, NULL, &dst);
    }
}

Enums::Scene HubScreen::HandleEvents(SDL_Event event) {
    Enums::Scene sceneSelection = Enums::SCN_HubMenu;
    InputManager* input = InputManager::getInstance();
	unordered_set<int> actions = input->getActionsDown();

    if (Utils::Contains(actions, Enums::ACTION_Right)) {
        IncrementSelection();
    }

    if (Utils::Contains(actions, Enums::ACTION_Left)) {
        DecrementSelection();
    }

    if (Utils::Contains(actions, Enums::ACTION_Select)) {
        PlayerAccount* account = PlayerAccount::GetInstance();

        switch (currSelection) {
            case Enums::HUB_Embark:
                if ((int) account->GetParty().size() == 0) {
                    /* Error message about party with 0 size */
                } else {
                    sceneSelection = Enums::SCENE_InGame;
                }

                break;
            case Enums::HUB_Recruitment:
                sceneSelection = Enums::SCN_HubRecruitment;
                break;
        }

        //sceneSelection = MapHubSelectionToScene();
    }

    return sceneSelection;
}

Enums::Scene HubScreen::MapHubSelectionToScene() {
    Enums::Scene scene;

    switch (currSelection) {
        case Enums::HUB_Recruitment: scene = Enums::SCN_HubRecruitment; break;
        case Enums::HUB_Embark: scene = Enums::SCENE_InGame; break;
    }

    return scene;
}

void HubScreen::IncrementSelection() {
    currSelection++;

    if (currSelection > Enums::HUB_Embark) {
        currSelection = Enums::HUB_Recruitment;
    }
}

void HubScreen::DecrementSelection() {
    currSelection--;

    if (currSelection < Enums::HUB_Recruitment) {
        currSelection = Enums::HUB_Embark;
    }
}