#include "MainMenuState.h"


MainMenuState::MainMenuState(int w, int h, Game* g) : GameState(g, w, h)
{
	mainMenu = new MainMenu(0, 0, g, this);

	mainMenu->setInputConfig(((PGZGame*) game)->controller->mainInputConfig);
	mainMenu->launch();
}


MainMenuState::~MainMenuState()
{
}
