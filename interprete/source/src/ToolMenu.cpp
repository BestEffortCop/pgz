#include "ToolMenu.h"


ToolMenu::ToolMenu(int x, int y, Game* game, GameState* gstate) : GameMenuController(x, y, game, gstate)
{
	setGraphic(new Stamp("data/graphics/game_menu.png", game->getGfxEngine()));
	setCursorImage(new Stamp("data/graphics/cursor.png", game->getGfxEngine()));

	Color colorEnabled = Color(38,38,38);
	Color colorDisabled = Color(138,138,138);

	menuFont = new TileFont("data/graphics/sprFont_strip94.png", game->getGfxEngine());

	GameMenuTextItemS* iTool = NULL;
	iTools = new vector<GameMenuTextItemS*>;
	std::vector<GameMenuTextItemS*>::iterator it = iTools->begin();

	iTool = new GameMenuTextItemS("New Game", menuFont, 85, 75, game, gstate);
	iTool->setCursorLocation(LEFT);
	iTool->getText()->setColor(colorEnabled);
	iTools->insert(it,iTool);
	it = iTools->end();

	iTool = new GameMenuTextItemS("Load Game", menuFont, 85, 95, game, gstate);
	iTool->setCursorLocation(LEFT);
	iTool->getText()->setColor(colorDisabled);
	iTools->insert(it,iTool);
	it = iTools->end();

	iTool = new GameMenuTextItemS("Options", menuFont, 85, 115, game, gstate);
	iTool->setCursorLocation(LEFT);
	iTool->getText()->setColor(colorDisabled);
	iTools->insert(it,iTool);
	it = iTools->end();

	iTool = new GameMenuTextItemS("Quit", menuFont, 85, 135, game, gstate);
	iTool->setCursorLocation(LEFT);
	iTool->getText()->setColor(colorDisabled);
	iTools->insert(it,iTool);
	it = iTools->end();

	iTool = NULL;
}

ToolMenu::~ToolMenu()
{
	delete menuFont;
}

void ToolMenu::launch()
{
	addMenuItem(iTools->at(0));
	addMenuItem(iTools->at(1));
	addMenuItem(iTools->at(2));
	addMenuItem(iTools->at(3));
	GameMenuController::launch();
}

void ToolMenu::onStep()
{
	GameMenuController::onStep();
}

void ToolMenu::onChosen(iSelectable* selectable)
{
	if (selectable == iTools->at(3))
	{
		quit();
	}
	/*if (selectable == iNewGame)
	{
		quit();
		((PGZGame*) game)->startNewgame();
	}*/
}