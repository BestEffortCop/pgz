#pragma once
#ifndef __GAMEOVERMENU_H__
#define __GAMEOVERMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"
#include "DataBaseInterface.h"

#include "Stamp.h"
#include "PGZGame.h"

class GameOverMenu : public GameMenuController
{

protected:
	GameMenuTextItemS* iLoad;
	GameMenuTextItemS* iQuit;

	TileFont* menuFont;

public:

	GameOverMenu(int x, int y, Game* game, GameState* gstate, DataBaseInterface* dbi);
	~GameOverMenu();

	void launch();

	void onRender();
	void onChosen(iSelectable* selectable);
};

#endif __GAMEOVER_H__