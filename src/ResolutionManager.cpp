#include "ResolutionManager.h"

ResolutionManager::ResolutionManager(int argc, char* argv[]) {
	flags = ParseCommandLineArgs(argc, argv);
}

ResolutionManager::~ResolutionManager() {

}

// Returns a map of various settings sourced from the arguments passed to the command line, the settings files, or the defaults
unordered_map<Enums::CommandLineFlag, string> ResolutionManager::ParseCommandLineArgs(int argc,char* argv[]) {
	unordered_map<Enums::CommandLineFlag, string> flags;

	flags = InitializeFlagsFromSettingsOrDefault();

	for (int i = 0; i < argc; i++) {
		string curr = argv[i];

		if (curr.compare("-fs") == 0) {
			flags[Enums::CommandLineFlag::CLF_Fullscreen] = argv[i + 1];
		} else if (curr.compare("-x") == 0) {
			flags[Enums::CommandLineFlag::CLF_xResolution] = argv[i + 1];
		} else if (curr.compare("-y") == 0) {
			flags[Enums::CommandLineFlag::CLF_yResolution] = argv[i + 1];
		}
	}

	return flags;
}


// Initializes the map using the values in the settings file or default values.
unordered_map<Enums::CommandLineFlag, string> ResolutionManager::InitializeFlagsFromSettingsOrDefault() {
	unordered_map<Enums::CommandLineFlag, std::string> flags;

	flags[Enums::CommandLineFlag::CLF_Fullscreen] = defaultFullscreen;
	flags[Enums::CommandLineFlag::CLF_xResolution] = defaultXResolution;
	flags[Enums::CommandLineFlag::CLF_yResolution] = defaultYResolution;

	//TODO: Read in flag values from some settings files, other wise use default value from Enums

	return flags;
}

int ResolutionManager::GetFlag(Enums::CommandLineFlag flag) {
	int flagValue = 0;

	switch (flag) {
		case Enums::CommandLineFlag::CLF_Fullscreen:
			flagValue = flags[Enums::CommandLineFlag::CLF_Fullscreen].compare("true") == 0 ? 1 : 0;
			break;
		case Enums::CommandLineFlag::CLF_xResolution:
			flagValue = stoi(flags[Enums::CommandLineFlag::CLF_xResolution]);
			break;
		case Enums::CommandLineFlag::CLF_yResolution:
			flagValue = stoi(flags[Enums::CommandLineFlag::CLF_yResolution]);
			break;
	}

	return flagValue;
}

void ResolutionManager::SetResolutionToFullscreenValues() {
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);

	flags[Enums::CommandLineFlag::CLF_xResolution] = to_string(mode.w);
	flags[Enums::CommandLineFlag::CLF_yResolution] = to_string(mode.h);

}



