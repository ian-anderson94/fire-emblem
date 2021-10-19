#include "ControlMapper.h"

ControlMapper* ControlMapper::instance = nullptr;

ControlMapper::ControlMapper() {
	defaultControlMap = {
			{ SDLK_a, Enums::Action::ACTION_Left },
			{ SDLK_d, Enums::Action::ACTION_Right },
			{ SDLK_w, Enums::Action::ACTION_Up },
			{ SDLK_s, Enums::Action::ACTION_Down },
			{ SDLK_SPACE, Enums::Action::ACTION_Jump },
			{ SDLK_RETURN, Enums::Action::ACTION_Select },
			{ SDLK_ESCAPE, Enums::Action::ACTION_Quit },
            { SDLK_BACKSPACE, Enums::ACTION_Cancel }
	};

    buttonControlMap = {
        { SDL_BUTTON_LEFT, Enums::ACTION_Select },
        { SDL_BUTTON_RIGHT, Enums::ACTION_Cancel }
    };

	controlMap = defaultControlMap;
}

ControlMapper::~ControlMapper() {
	// TODO Auto-generated destructor stub
}

ControlMapper* ControlMapper::getInstance() {
	if (!instance)
		instance = new ControlMapper();

	return instance;
}

std::unordered_set<int> ControlMapper::getActionsFromInput(std::unordered_set<SDL_Keycode> input, std::unordered_set<Uint8> buttonInput) {
	std::unordered_set<int> actions;

	for (auto& in : input) {
		actions.insert(controlMap[in]);
	}

    for (auto& in : buttonInput) {
        actions.insert(buttonControlMap[in]);
    }

	return actions;
}

