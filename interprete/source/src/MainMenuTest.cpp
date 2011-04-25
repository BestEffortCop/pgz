#include "MainMenuTest.h"

#include "GamePlayState.h"

MainMenuTest::MainMenuTest(int x, int y, Game* game, GameState* gstate) : GameMenuController(x, y, game, gstate)
{
	setGraphic(new Stamp("data/graphics/game_menu.png", game->getGfxEngine()));
	setCursorImage(new Stamp("data/graphics/cursor.png", game->getGfxEngine()));

	i_newGame = new GameMenuItemTextS(85, 75, "New Game", 32, 8, game, gstate);
	i_newGame->setCursorLocation(LEFT);

	i_loadGame = new GameMenuItemTextS(85, 95, "Load Game", 32, 8, game, gstate);
	i_loadGame->setCursorLocation(LEFT);

	i_options = new GameMenuItemTextS(85, 115, "Options", 32, 8, game, gstate);
	i_options->setCursorLocation(LEFT);

	i_quit = new GameMenuItemTextS(85, 135, "Quit", 32, 8, game, gstate);
	i_quit->setCursorLocation(LEFT);
}

MainMenuTest::~MainMenuTest()
{
}

void MainMenuTest::launch()
{
	addMenuItem(i_newGame);
	addMenuItem(i_loadGame);
	addMenuItem(i_options);
	addMenuItem(i_quit);
	GameMenuController::launch();
	((GamePlayState*) world)->pauseGameEntities();
}

void MainMenuTest::onChosen(iSelectable* selectable)
{
	if (selectable == i_quit)
	{
		quit();
		((GamePlayState*) world)->unpauseGameEntities();
	}
	/*if (selectable == i_newGame)
	{
			(PGZGame*) game->controller = new Controller(game);


			(PGZGame*) game->controller->initData("");
			
			GamePlayState gameState = new GamePlayState(224, 224, game);

			(PGZGame*) game->changeGameState(gameState);
			(PGZGame*) game->controller->initGamePlayState((GamePlayState*) gameState);
	}*/
}