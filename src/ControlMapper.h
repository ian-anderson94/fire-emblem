#ifndef SRC_CONTROLMAPPER_H_
#define SRC_CONTROLMAPPER_H_

#include <unordered_map>
#include <unordered_set>

#include "Globals.h"
#include "Enums.h"

class ControlMapper {

public:
	ControlMapper();
	virtual ~ControlMapper();

	static ControlMapper* getInstance();

	void resetControlsToDefault() { controlMap = defaultControlMap; };

	std::unordered_set<int> getActionsFromInput(std::unordered_set<SDL_Keycode> input, std::unordered_set<Uint8> buttonInput);

private:
	static ControlMapper* instance;

	std::unordered_map<SDL_Keycode, int> controlMap;
    std::unordered_map<Uint8, int> buttonControlMap;
	std::unordered_map<SDL_Keycode, int> defaultControlMap;
};

#endif /* SRC_CONTROLMAPPER_H_ */
