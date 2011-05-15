#pragma once
#ifndef __MAINMENUSTATE_H__
#define __MAINMENUSTATE_H__


#include "Gamestate.h"
#include "MainMenu.h"
#include "LoadMenu.h"

class MainMenu;
class LoadMenu;

class MainMenuState : public GameState
{
protected:
	MainMenu* mainMenu;
	LoadMenu* loadMenu;

public:

	// Constructora
	MainMenuState(int w, int h, Game* g);

	// Destructora
	~MainMenuState();

	void changeMenu();
};

#endif