#pragma once
#ifndef __PGZGAME_H__
#define __PGZGAME_H__

#include "Game.h"
#include "GamePlayState.h"
#include "MainMenuState.h"
#include "controller.h"

#include "DataBaseInterface.h"
#include "Player.h"


class Controller;

class PGZGame : public Game
{
	private:
		bool reset;
	public:

		Controller* controller;

		//PGZGame() : Game(224*3, 192*3, 32, 224, 192, 3, 30)
		PGZGame();
		~PGZGame();
		void onStep();

		void startNewgame();
		void showPrologue();
		void loadGame(int i);
		void resetGame();
		void changeMenu();
};

#endif
