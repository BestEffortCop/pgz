#pragma once
#ifndef __TOOLMENU_H__
#define __TOOLMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"
#include "GameMenuItemS.h"

#include "Stamp.h"
#include "PGZGame.h"

#include <vector>

//Centro real 112,96
//Centro para que se dibuje bien 112 - 16/2 , 96 -16/2
//Radio 60

#define Pi 3.1415f

class ToolMenu : public GameMenuController
{

protected:
	vector<GameMenuItemS*>* iTools;
	GameMenuTextItem * iText;
	vector<int> idTools;
	TileFont* menuFont;

	int centroX;
	int centroY;
	int radio;


public:
	ToolMenu(int x, int y, Game* game, GameState* gstate,int centroX = 104, int centroY = 88, int radio = 60);
	~ToolMenu();

	void launch();

	void onStep();
	void onRender();
	void onChosen(iSelectable* selectable);
	void onCancelled(iSelectable* selectable);
	void onStartPressed(iSelectable* selectable);

	iSelectable* getMandatorySelectable(iSelectable* slc, Direction dir);
	iSelectable* getAlternativeSelectable(iSelectable* slc, Direction dir);
};

#endif __TOOLMENU_H__