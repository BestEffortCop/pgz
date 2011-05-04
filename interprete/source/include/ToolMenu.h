#pragma once
#ifndef __TOOLMENU_H__
#define __TOOLMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"

#include "Stamp.h"
#include "PGZGame.h"

#include <vector>

#define CentroX 112
#define CentroY 96
#define Radio 92
#define Pi 3.1415



class ToolMenu : public GameMenuController
{

protected:
	vector<GameMenuTextItemS*>* iTools;
	vector<int> idTools;
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