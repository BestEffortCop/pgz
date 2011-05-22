#pragma once
#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"
#include "DataBaseInterface.h"

#include "Stamp.h"
#include "PGZGame.h"
#include "IntroState.h"

class MainMenu : public GameMenuController
{

protected:
	GameMenuTextItemS* iNewGame;
	GameMenuTextItemS* iLoadGame;
	GameMenuTextItemS* iOptions;
	GameMenuTextItemS* iQuit;

	TileFont* menuFont;

	bool noSaveFiles;

public:
	MainMenu(int x, int y, Game* game, GameState* gstate, DataBaseInterface* dbi);
	~MainMenu();

	void launch();

	void onStep();
	void onChosen(iSelectable* selectable);
};

#endif __MAINMENU_H__