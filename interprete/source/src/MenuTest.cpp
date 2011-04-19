#include "MenuTest.h"


MenuTest::MenuTest(int x, int y, Game* game, GameState* gstate) : GameMenuController(x, y, game, gstate)
{
	setGraphic(new Stamp("data/graphics/stampcontroller.png", game->getGfxEngine()));
	setCursorImage(new Stamp("data/graphics/cursor.png", game->getGfxEngine()));

	i1 = new GameMenuItemS(95,75,game, gstate);
	i1->setGraphic(new Stamp("data/graphics/item1.png", game->getGfxEngine()));

	i2 = new GameMenuItemS(95,95,game, gstate);
	i2->setGraphic(new Stamp("data/graphics/item2.png", game->getGfxEngine()));
}


MenuTest::~MenuTest()
{
}


void MenuTest::launch()
{
	addMenuItem(i1);
	addMenuItem(i2);
	GameMenuController::launch();
}