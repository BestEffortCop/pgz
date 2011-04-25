#pragma once
#ifndef __MAINMENUSTATE_H__
#define __MAINMENUSTATE_H__


#include "Gamestate.h"
#include "MainMenu.h"

class MainMenu;

class MainMenuState : public GameState
{
protected:
	MainMenu* mainMenu;

public:

	// Constructora
	MainMenuState(int w, int h, Game* g);

	// Destructora
	~MainMenuState();
};

#endif