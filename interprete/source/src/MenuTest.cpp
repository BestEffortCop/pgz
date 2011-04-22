#include "MenuTest.h"


MenuTest::MenuTest(int x, int y, Game* game, GameState* gstate) : GameMenuController(x, y, game, gstate)
{
	setGraphic(new Stamp("data/graphics/stampcontroller.png", game->getGfxEngine()));
	setCursorImage(new Stamp("data/graphics/cursor.png", game->getGfxEngine()));
	
	i1 = new GameMenuItemS(95, 75, 32, 8, game, gstate);
	i1->setGraphic(new Stamp("data/graphics/item1.png", game->getGfxEngine()));
	i1->setCursorLocation(UP);

	i2 = new GameMenuItemS(115, 95, 32, 8, game, gstate);
	i2->setGraphic(new Stamp("data/graphics/item1.png", game->getGfxEngine()));
	i2->setCursorLocation(RIGHT);

	i3 = new GameMenuItemS(125, 115, 32, 8, game, gstate);
	i3->setGraphic(new Stamp("data/graphics/item1.png", game->getGfxEngine()));
	i3->setCursorLocation(RIGHT);

	i4 = new GameMenuItemS(115, 135, 32, 8, game, gstate);
	i4->setGraphic(new Stamp("data/graphics/item1.png", game->getGfxEngine()));
	i4->setCursorLocation(RIGHT);

	i5 = new GameMenuItemS(95, 155, 32, 8, game, gstate);
	i5->setGraphic(new Stamp("data/graphics/item1.png", game->getGfxEngine()));
	i5->setCursorLocation(DOWN);

	i6 = new GameMenuItemS(75, 135, 32, 8, game, gstate);
	i6->setGraphic(new Stamp("data/graphics/item1.png", game->getGfxEngine()));
	i6->setCursorLocation(LEFT);

	i7 = new GameMenuItemS(65, 115, 32, 8, game, gstate);
	i7->setGraphic(new Stamp("data/graphics/item1.png", game->getGfxEngine()));
	i7->setCursorLocation(LEFT);

	i8 = new GameMenuItemS(75, 95, 19, 10, game, gstate);
	i8->setGraphic(new Stamp("data/graphics/item2.png", game->getGfxEngine()));
	i8->setCursorLocation(LEFT);
}

MenuTest::~MenuTest()
{
}

void MenuTest::launch()
{
	addMenuItem(i1);
	addMenuItem(i2);
	addMenuItem(i3);
	addMenuItem(i4);
	addMenuItem(i5);
	addMenuItem(i6);
	addMenuItem(i7);
	addMenuItem(i8);
	GameMenuController::launch();
}

void MenuTest::onChosen(iSelectable* selectable)
{
	if (selectable == i8)
		quit();
}