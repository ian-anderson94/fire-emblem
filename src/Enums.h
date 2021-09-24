#ifndef ENUMS_H_
#define ENUMS_H_

class Enums {
public:
	enum Action {
		ACTION_Jump,
		ACTION_Left,
		ACTION_Right,
		ACTION_Up,
		ACTION_Down,
		ACTION_Select,
		ACTION_Quit,
		ACTION_End
	};

	enum CommandLineFlag {
		CLF_Fullscreen,
		CLF_xResolution,
		CLF_yResolution,
	};

    enum Direction {
        DIR_Up,
        DIR_Down,
        DIR_Left,
        DIR_Right
    };

    enum InfoPanelLocation {
        IFP_TOPLEFT,
        IFP_TOPRIGHT,
        IFP_BOTLEFT,
        IFP_BOTRIGHT
    };

	enum MainMenuSelection {
		MMS_Start,
		MMS_MainMenu,
		MMS_GameStart,
		MMS_Options,
		MMS_Exit,
		MMS_End
	};

	enum Scene {
		SCENE_MainMenu,
		SCENE_InGame,
		SCENE_Options,
		SCENE_PauseMenu
	};
};

#endif /* ENUMS_H_ */
