#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() {
	locked = false;
	running = true;
}

InputManager::~InputManager() {

}

InputManager* InputManager::getInstance() {
	if (!instance)
		instance = new InputManager();

	return instance;
}

void InputManager::update(SDL_Event event) {
	std::unordered_set<SDL_Keycode> tempDown;
	std::unordered_set<SDL_Keycode> tempUp;
    std::unordered_set<Uint8> tempButtonDown;
    std::unordered_set<Uint8> tempButtonUp;
	keysDown = tempDown;
	keysUp = tempUp;
    buttonsDown = tempButtonDown;
    buttonsUp = tempButtonUp;

	while(SDL_PollEvent(&event) != 0) {
		switch(event.type) {
            case SDL_KEYDOWN: setKeyDown(event.key.keysym.sym); break;
            case SDL_KEYUP: setKeyUp(event.key.keysym.sym); break;
            case SDL_MOUSEBUTTONDOWN: setMouseDown(event.button.button); break;
            case SDL_MOUSEBUTTONUP: setMouseUp(event.button.button); break;
            case SDL_QUIT: running = false; break;
		}
	}

	for (auto& key : keysDown) {
		keysPressed[key] = true;
	}

	for (auto& key : keysUp) {
		keysPressed[key] = false;
    }
}

std::unordered_set<int> InputManager::getPressedKeys() {
	std::unordered_set<int> keys;

	for (auto& kvp : keysPressed) {
		if (kvp.second) {
			keys.insert(kvp.first);
		}
	}

	return keys;
}

std::unordered_set<int> InputManager::getActionsDown() {
	ControlMapper* controls = ControlMapper::getInstance();
	return controls->getActionsFromInput(keysDown, buttonsDown);
}

std::unordered_set<int> InputManager::getActionsUp() {
	ControlMapper* controls = ControlMapper::getInstance();
	return controls->getActionsFromInput(keysUp, buttonsUp);
}

std::unordered_set<int> InputManager::getActionsPressed() {
	ControlMapper* controls = ControlMapper::getInstance();
	return controls->getActionsFromInput(getPressedKeys(), buttonsDown);
}

