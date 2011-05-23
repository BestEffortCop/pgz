#include "MainMenu.h"

MainMenu::MainMenu(int x, int y, Game* game, GameState* gstate, DataBaseInterface* dbi) : GameMenuController(x, y, game, gstate)
{
	setGraphic(new Stamp(dbi->getMainMenu(), game->getGfxEngine()));
	setCursorImage(new Stamp(dbi->getCursor(), game->getGfxEngine()));

	Color colorEnabled = Color(38,38,38);
	Color colorDisabled = Color(138,138,138);

	menuFont = new TileFont(dbi->getFont(), game->getGfxEngine());

	iNewGame = new GameMenuTextItemS("New Game", menuFont, 85, 75, game, gstate);
	iNewGame->setCursorLocation(LEFT);
	iNewGame->getText()->setColor(colorEnabled);

	iLoadGame = new GameMenuTextItemS("Load Game", menuFont, 85, 95, game, gstate);
	iLoadGame->setCursorLocation(LEFT);


	iOptions = new GameMenuTextItemS("Options", menuFont, 85, 115, game, gstate);
	iOptions->setCursorLocation(LEFT);
	iOptions->getText()->setColor(colorDisabled);

	iQuit = new GameMenuTextItemS("Quit", menuFont, 85, 135, game, gstate);
	iQuit->setCursorLocation(LEFT);
	iQuit->getText()->setColor(colorEnabled);


	FILE * f = NULL;
	noSaveFiles = true;
	int i = 0;
	char str[80];
	char buffer[33];
	while (noSaveFiles && i < 3)
	{
		strcpy(str,"data/save");
		strcat(str,itoa(i,buffer,10));
		f = fopen(str, "rb");
		if (f != NULL)
		{
			fclose(f);
			noSaveFiles = false;
		}
		else
		{
			i++;
		}
	}

	if (!noSaveFiles)
		iLoadGame->getText()->setColor(colorEnabled);
	else
		iLoadGame->getText()->setColor(colorDisabled);
}

MainMenu::~MainMenu()
{
	delete menuFont;
}

void MainMenu::launch()
{
	addMenuItem(iNewGame);
	addMenuItem(iLoadGame);
	addMenuItem(iOptions);
	addMenuItem(iQuit);
	GameMenuController::launch();
}

void MainMenu::onStep()
{
	GameMenuController::onStep();
}

void MainMenu::onChosen(iSelectable* selectable)
{
	if (selectable == iQuit)
	{
		game->setFinished(true);
	}
	if (selectable == iNewGame)
	{
		quit();
		//((PGZGame*) game)->startNewgame();


		((PGZGame*) game)->showPrologue();
	}
	if (selectable == iLoadGame){
		if (!noSaveFiles)
		{
		((PGZGame*) game)->changeMenu();
		}
	}
}