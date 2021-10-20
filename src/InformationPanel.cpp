#include "InformationPanel.h"

InformationPanel::InformationPanel(int resolutionX, int resolutionY, int tileSize) {
    location = Enums::IFP_BOTRIGHT;
    isDisplayed = true;
    size = tileSize;
    resX = resolutionX;
    resY = resolutionY;
    w = size * 3;
    h = size * 2;

    pair<int, int> coords = CalculatePosition();
    x = coords.first;
    y = coords.second;

    message = "";
    messageW = w / 2;
    messageH = h / 2;
    messageX = (x / 2) - (messageW / 2);
    messageY = (y / 2) - (messageH / 2);

    panelImagePath = "./assets/infopanel.png";
    panelTexture = TextureManager::loadTexture(panelImagePath);
}

void InformationPanel::Render(SDL_Renderer* rend) {
    if (isDisplayed) {
        SDL_Rect dst {x, y, w, h};
        SDL_RenderCopy(rend, panelTexture, NULL, &dst);
        RenderMessage(rend);
    }
}

void InformationPanel::RenderMessage(SDL_Renderer* rend) {
    SDL_Color white = { 255, 255, 255 };
    const char* fontFile = "fonts/OpenSans-Regular.ttf";

    TextManager::LoadFontAndPrint(rend, message.c_str(), messageX, messageY);
    //TextManager::LoadFontAndPrint(fontFile, 20, message.c_str(), white, messageX, messageY, messageW, messageH, rend);
}

void InformationPanel::Update(int cursorX, int cursorY, Tile* tileUnderCursor) {
    UpdateInfoPanelPos(cursorX, cursorY);
    UpdateInfoPanelInfo(tileUnderCursor);
}

// Update info panel with game cursor position and tile under cursor
void InformationPanel::UpdateInfoPanelPos(int cursorX, int cursorY) {
    int midX = resX / 2;
    int midY = resY / 2;

    int xPos = cursorX * size;
    int yPos = cursorY * size;

    if (xPos <= midX && yPos <= midY) {
        location = Enums::IFP_BOTRIGHT;
    } else if (xPos <= midX && yPos > midY) {
        location = Enums::IFP_TOPRIGHT;
    } else if (xPos > midX && yPos <= midY) {
        location = Enums::IFP_BOTLEFT;
    } else if (xPos > midX && yPos > midY) {
        location = Enums::IFP_TOPLEFT;
    }

    pair<int, int> coords = CalculatePosition();
    x = coords.first;
    y = coords.second;
}

void InformationPanel::UpdateInfoPanelInfo(Tile* tileUnderCursor) {
    message = tileUnderCursor->GetTileType();
}

pair<int, int> InformationPanel::CalculatePosition() {
    int x, y;

    switch (location) {
        case Enums::IFP_TOPLEFT: 
            x = size / 2;
            y = size / 2;
            break;
        case Enums::IFP_TOPRIGHT: 
            x = resX - (size / 2) - w;
            y = size / 2;
            break;
        case Enums::IFP_BOTLEFT:
            x = size / 2;
            y = resY - (size / 2) - h;
            break;
        case Enums::IFP_BOTRIGHT:
            x = resX - (size / 2) - w;
            y = resY - (size / 2) - h;
            break;
    }

    messageX = x;
    messageY = y;

    return pair<int, int>(x, y);
}