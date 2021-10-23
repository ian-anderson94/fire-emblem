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
        ACTION_Cancel,
		ACTION_End
	};

    enum ActionMenu {
        ACTM_Move,
        ACTM_Attack,
        ACTM_Inspect,
        ACTM_End,
    };

    enum ActionMenuRecruitment {
        AMR_Recruit,
        AMR_Cancel,
    };

    enum ClassType {
        CLS_Warrior,
        CLS_Paladin,
        CLS_Hunter,
        CLS_Rogue,
        CLS_Mage,
        CLS_Priest,
        CLS_LAST
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

    enum HubSelection {
        HUB_Recruitment,
        /*
        HUB_Blacksmith,
        HUB_Shop,
        HUB_Graveyard,
        */
        HUB_Embark
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
		SCN_MainMenu,
		SCN_InGame,
		SCN_Options,
		SCN_PauseMenu,
        SCN_HubMenu,
        SCN_HubRecruitment,
        SCN_NULL
	};

    enum SpriteSheetFrames {
        SSF_Icon,
        SSF_Idle1,
        SSF_Idle2,
        SSF_Idle3,
        SSF_WalkLeft1,
        SSF_WalkLeft2,
        SSF_WalkLeft3,
        SSF_WalkLeft4,
        SSF_WalkRight1,
        SSF_WalkRight2,
        SSF_WalkRight3,
        SSF_WalkRight4,
        SSF_WalkUp1,
        SSF_WalkUp2,
        SSF_WalkUp3,
        SSF_WalkUp4,
        SSF_WalkDown1,
        SSF_WalkDown2,
        SSF_WalkDown3,
        SSF_WalkDown4,
        SSF_Selected1,
        SSF_Selected2,
        SSF_Selected3
    };

    enum TurnAction {
        TRN_Move,
        TRN_Attack
    };
};

#endif /* ENUMS_H_ */
