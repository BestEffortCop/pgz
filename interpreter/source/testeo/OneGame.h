#pragma once
#ifndef __ONEGAME_H__
#define __ONEGAME_H__

#include "Game.h"
#include "Level.h"

class OneGame : public Game
{
	public:

		OneGame() : Game(1024, 768, 32, 320, 240, 2, 30)
		{
			gameState = new Level(this);
		}

		void onUpdate()
		{
			if (getInput()->keyPressed(Input::kESC))
				setFinished(true);
		};

};

#endif
