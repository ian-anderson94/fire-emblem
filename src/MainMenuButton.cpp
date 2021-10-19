#include "MainMenuButton.h"

MainMenuButton::MainMenuButton(const char* text, int x, int y, int w, int h, Enums::Scene currScene, Enums::Scene destScene, Enums::Scene (*functionality)(Enums::Scene)) : Button(text, x, y, w, h, currScene, functionality) {
    backgroundImagePath = "./assets/infopanel.png";
    backgroundTexture = TextureManager::loadTexture(backgroundImagePath);

    this->destScene = destScene;
}

Enums::Scene MainMenuButton::Execute() {
    return functionality(destScene);
}