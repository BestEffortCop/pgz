#pragma once

#include "GameMenuController.h"
#include "GameMenuStampItemS.h"
#include "Stamp.h"

class MenuTest : public GameMenuController
{

private:

	GameMenuItemS* i1;
	GameMenuItemS* i2;

public:
	MenuTest(int x, int y, Game* game, GameState* gstate);
	~MenuTest();


	void launch();
};

