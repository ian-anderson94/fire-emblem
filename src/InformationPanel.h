#ifndef SRC_INFORMATIONPANEL_H_
#define SRC_INFORMATIONPANEL_H_

#include "Enums.h"
#include "TextManager.h"
#include "TextureManager.h"
#include "Tile.h"

#include <iostream>
#include <string>
#include <utility>

using namespace std;

class InformationPanel {
    public:
        InformationPanel(int resolutionX, int resolutionY, int tileSize);
        void Update(int cursorX, int cursorY, Tile* tileUnderCursor);
        void Render(SDL_Renderer* rend);

    private:
        int x, y, w, h, size, resX, resY, messageX, messageY, messageW, messageH;
        bool isDisplayed;
        string message;
        Enums::InfoPanelLocation location;

        const char* panelImagePath;
        SDL_Texture* panelTexture;

        pair<int, int> CalculatePosition();
        void UpdateInfoPanelPos(int cursorX, int cursorY);
        void UpdateInfoPanelInfo(Tile* tileUnderCursor);

        void RenderMessage(SDL_Renderer* rend);
};

#endif /* SRC_INFORMATIONPANEL_H_ */
