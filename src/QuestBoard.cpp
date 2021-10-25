#include "QuestBoard.h"

QuestBoard::QuestBoard(int resX, int resY, int tileSize) : Scene(resX, resY, tileSize) {
    xAnchor = tileSize;
    yAnchor = 2 * tileSize;
    activeQuest = nullptr;
    maxQuestsAvailable = 4;
    GenerateQuests(maxQuestsAvailable);
    selector = new Selector<Quest*>(questsAvailable);
}

void QuestBoard::Update(double dt) {

}

void QuestBoard::Render(SDL_Renderer* rend) {
    RenderActiveQuest(rend);
    Position sPos = RenderAvailableQuests(rend);
    selector->RenderRelativeToSelection(rend, sPos);
}

Position QuestBoard::RenderAvailableQuests(SDL_Renderer* rend) {
    Position sPos;
    int yOffset = 0;
    int mx = xAnchor + (tileSize / 2);

    for (int i = 0; i < (int) questTitles.size(); i++) {
        Position tPos = TextManager::LoadFontAndPrint(rend, questTitles[i].c_str(), mx, yAnchor + yOffset);

        if (selector->GetSelectionIndex() == i) {
            sPos.x = xAnchor - (tileSize / 2);
            sPos.y = yAnchor + yOffset;
            sPos.w = tPos.h;
            sPos.h = tPos.h;
        }

        yOffset += tileSize / 2;
    }

    return sPos;
}

void QuestBoard::RenderActiveQuest(SDL_Renderer* rend) {
    PlayerAccount* account = PlayerAccount::GetInstance();
    Quest* activeQuest = account->GetActiveQuest(); 
    string activeQuestString = "Current Quest: ";

    if (activeQuest) {
        activeQuestString += activeQuest->GetTitle();
    }

    TextManager::LoadFontAndPrint(rend, activeQuestString.c_str(), tileSize, tileSize);
}

Enums::Scene QuestBoard::HandleEvents(SDL_Event event) {
    Enums::Scene currScene = Enums::SCN_HubQuestBoard;

    InputManager* input = InputManager::getInstance();
	unordered_map<int, bool> actions = input->GetActionMap();

    if (actions[Enums::ACTION_Up]) {
        selector->SetAndBoundCurrSelection(-1);
    }

    if (actions[Enums::ACTION_Down]) {
        selector->SetAndBoundCurrSelection(1);
    }

    if (actions[Enums::ACTION_Select]) {
        PlayerAccount* account = PlayerAccount::GetInstance();
        account->SetActiveQuest(selector->GetSelection());
    }

    if (actions[Enums::ACTION_Cancel]) {
        currScene = Enums::SCN_HubMenu;
    }

    return currScene;
}

void QuestBoard::GenerateQuests(int numQuests) {
    questsAvailable.push_back(new Quest(Enums::QST_Elimination, Enums::QDF_Easy, Enums::BIO_Graveyard));
    questsAvailable.push_back(new Quest(Enums::QST_Elimination, Enums::QDF_Easy, Enums::BIO_Graveyard));
    questsAvailable.push_back(new Quest(Enums::QST_Elimination, Enums::QDF_Easy, Enums::BIO_Graveyard));
    questsAvailable.push_back(new Quest(Enums::QST_Elimination, Enums::QDF_Easy, Enums::BIO_Graveyard));

    for (int i = 0; i < questsAvailable.size(); i++) {
        questTitles.push_back(questsAvailable[i]->GetTitle());
    }
}