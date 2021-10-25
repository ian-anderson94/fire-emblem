#ifndef SRC_QUESTBOARD_H_
#define SRC_QUESTBOARD_H_

#include "InputManager.h"
#include "PlayerAccount.h"
#include "Position.h"
#include "Scene.h"
#include "Selector.h"
#include "TextManager.h"
#include "Quest.h"

#include <vector>
#include <unordered_map>

using namespace std;

class QuestBoard : public Scene {
    public:
        QuestBoard(int resX, int resY, int tileSize);
        void Update(double dt);
        void Render(SDL_Renderer* rend);
        Enums::Scene HandleEvents(SDL_Event event);

    private:
        void GenerateQuests(int numQuests);
        void RenderActiveQuest(SDL_Renderer* rend);
        Position RenderAvailableQuests(SDL_Renderer* rend);

        int xAnchor, yAnchor, maxQuestsAvailable;
        vector<Quest*> questsAvailable;
        vector<string> questTitles;
        Quest* activeQuest;
        Selector<Quest*>* selector;
};

#endif /* SRC_QUESTBOARD_H_ */