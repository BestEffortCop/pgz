#pragma once
#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"

#include "Stamp.h"
#include "PGZGame.h"


class MainMenu : public GameMenuController
{

protected:
	GameMenuTextItemS* iNewGame;
	GameMenuTextItemS* iLoadGame;
	GameMenuTextItemS* iOptions;
	GameMenuTextItemS* iQuit;

	TileFont* menuFont;

public:
	MainMenu(int x, int y, Game* game, GameState* gstate);
	~MainMenu();

	void launch();

	void onStep();
	void onChosen(iSelectable* selectable);
};

#endif __MAINMENU_H__