#include "MainMenuState.h"


MainMenuState::MainMenuState(int w, int h, Game* g) : GameState(g, w, h)
{
	mainMenu = new MainMenu(0, 0, g, this);

	mainMenu->launch();
}


MainMenuState::~MainMenuState()
{
}
