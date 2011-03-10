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

		OneGame() : Game(320*2 + 2, 240*2 + 2, 32, 320, 240, 2, 30)
		{
			on = false;
			gameState = new Level(this);
			gfxEngine->setScreenBackgroundColor(Color::Blue);
		}

		void onStep()
		{
			if (getInput()->keyPressed(Input::kESC))
				setFinished(true);
		};
};

#endif
