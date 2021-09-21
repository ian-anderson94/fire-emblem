#ifndef RESOLUTIONMANAGER_H_
#define RESOLUTIONMANAGER_H_

#include "Enums.h"
#include "SDL2/SDL.h"

#include <unordered_map>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

class ResolutionManager {
public:
	ResolutionManager(int argc, char* argv[]);
	virtual ~ResolutionManager();

	int GetFlag(Enums::CommandLineFlag flag);
	void SetResolutionToFullscreenValues();

private:
	unordered_map<Enums::CommandLineFlag, string> ParseCommandLineArgs(int argc, char* argv[]);
	unordered_map<Enums::CommandLineFlag, string> InitializeFlagsFromSettingsOrDefault();
	unordered_map<Enums::CommandLineFlag, string> flags;

	const string defaultFullscreen = "false";
	const string defaultXResolution = "1280";
	const string defaultYResolution = "720";
};


#endif /* RESOLUTIONMANAGER_H_ */
