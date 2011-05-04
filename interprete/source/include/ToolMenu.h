#pragma once
#ifndef __TOOLMENU_H__
#define __TOOLMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"

#include "Stamp.h"
#include "PGZGame.h"

#include <vector>

//Centro real 112,96
//Centro para que se dibuje bien 

#define CentroX 110
#define CentroY 93
#define Radio 92
#define Pi 3.1415



class ToolMenu : public GameMenuController
{

protected:
	vector<GameMenuItemS*>* iTools;
	vector<int> idTools;
	TileFont* menuFont;

public:
	ToolMenu(int x, int y, Game* game, GameState* gstate);
	~ToolMenu();

	void launch();

	void onStep();
	void onRender();
	void onChosen(iSelectable* selectable);
	void onCancelled(iSelectable* selectable);

	iSelectable* getMandatorySelectable(iSelectable* slc, Direction dir);
	iSelectable* getAlternativeSelectable(iSelectable* slc, Direction dir);
};

#endif