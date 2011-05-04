#pragma once
#ifndef __TOOLMENU_H__
#define __TOOLMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"

#include "Stamp.h"
#include "PGZGame.h"

#include <vector>

class ToolMenu : public GameMenuController
{

protected:
	vector<GameMenuTextItemS*>* iTools;
	TileFont* menuFont;

public:
	ToolMenu(int x, int y, Game* game, GameState* gstate);
	~ToolMenu();

	void launch();

	void onStep();
	void onRender();
	void onChosen(iSelectable* selectable);

	iSelectable* getMandatorySelectable(iSelectable* slc, Direction dir);
	iSelectable* getAlternativeSelectable(iSelectable* slc, Direction dir);
};

#endif