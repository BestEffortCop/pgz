#pragma once
#ifndef __MAINMENUTEST_H__
#define __MAINMENUTEST_H__

#include "GameMenuController.h"
#include "GameMenuItemTextS.h"
#include "Stamp.h"
/*#include "PGZGame.h"
#include "GamePlayState.h"

class GamePlayState;
class PGZGame;*/

class MainMenuTest : public GameMenuController
{

private:
	GameMenuItemTextS* i_newGame;
	GameMenuItemTextS* i_loadGame;
	GameMenuItemTextS* i_options;
	GameMenuItemTextS* i_quit;

public:
	MainMenuTest(int x, int y, Game* game, GameState* gstate);
	~MainMenuTest();

	void launch();
	void onChosen(iSelectable* selectable);
};

#endif