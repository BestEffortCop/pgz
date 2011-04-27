#pragma once
#ifndef __MAINMENUTEST_H__
#define __MAINMENUTEST_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"

#include "Stamp.h"
#include "PGZGame.h"
#include "GamePlayState.h"

class MainMenu : public GameMenuController
{

protected:
	GameMenuTextItemS* iNewGame;
	GameMenuTextItemS* iLoadGame;
	GameMenuTextItemS* iOptions;
	GameMenuTextItemS* iQuit;

	TileFont* menuFont;

	bool sleep;

public:
	MainMenu(int x, int y, Game* game, GameState* gstate);
	~MainMenu();

	void launch();

	void onStep();
	void onTimer(int n);

	void onChosen(iSelectable* selectable);
};

#endif