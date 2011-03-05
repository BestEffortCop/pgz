#pragma once
#ifndef __ONEGAME_H__
#define __ONEGAME_H__

#include "Game.h"
#include "Level.h"

class OneGame : public Game
{
	private:
		bool on;

	public:

		OneGame() : Game(1024, 768, 32, 320, 240, 2, 30)
		{
			on = false;
			gameState = new Level(this);
		}

		void onStep()
		{
			if (getInput()->keyPressed(Input::kESC))
				setFinished(true);
		};
};

#endif
