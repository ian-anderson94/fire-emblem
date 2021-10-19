#ifndef SRC_MAINMENUBUTTON_H_
#define SRC_MAINMENUBUTTON_H_

#include "Button.h"

class MainMenuButton : public Button {
    public:
        MainMenuButton(const char* text, int x, int y, int w, int h, Enums::Scene currScene, Enums::Scene destScene, Enums::Scene (*functionality)(Enums::Scene));
        Enums::Scene Execute();

    private:
        Enums::Scene destScene;

};

#endif /* SRC_MAINMENUBUTTON_H_ */