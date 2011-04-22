#pragma once

#include "GameMenuController.h"
#include "GameMenuStampItemS.h"
#include "Stamp.h"

class MenuTest : public GameMenuController
{

private:

	GameMenuItemS* i1;
	GameMenuItemS* i2;

	GameMenuItemS* i4;
	GameMenuItemS* i5;
	GameMenuItemS* i8;

	GameMenuItemS* i3;
	GameMenuItemS* i6;
	GameMenuItemS* i7;

public:
	MenuTest(int x, int y, Game* game, GameState* gstate);
	~MenuTest();

	void launch();
	void onChosen(iSelectable* selectable);
};

