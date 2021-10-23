#include "Button.h"

Button::Button(const char* text, int x, int y, int w, int h, Enums::Scene currScene, Enums::Scene (*functionality)(Enums::Scene)) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->text = text;
    this->functionality = functionality;
    this->currScene = currScene;
}

void Button::Render(SDL_Renderer* rend) {
    SDL_Rect dst { x, y, w, h };
    SDL_RenderCopy(rend, backgroundTexture, NULL, &dst);

    TextManager::LoadFontAndPrint(rend, text, x, y);
}

Enums::Scene Button::HandleEvents(SDL_Event event) {
    InputManager* input = InputManager::getInstance();
	std::unordered_set<int> actions = input->getActionsDown();

    if (Utils::Contains(actions, Enums::ACTION_Select)) {
        if (IsClicked()) {
            return Execute();
        }
    }

    return Enums::SCN_NULL;
}

bool Button::IsClicked() {
    Mouse::Position mPos = Mouse::GetPosition();

    if (mPos.x > x && mPos.x < x + w) {
        if (mPos.y > y && mPos.y < y + h) {
            return true;
        }
    }

    return false;
}

Enums::Scene Button::Execute() {
    return Enums::SCN_MainMenu;
}