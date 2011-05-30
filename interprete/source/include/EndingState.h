#pragma once
#ifndef _ENDING_H_
#define _ENDING_H_

#include "Entity.h"
#include "Stamp.h"
#include "PGZGame.h"

class EndingEntity : public Entity
{
private:
	Stamp* scroller;
	int ox, oy, tx, ty, sp;
	int counter;
	bool counting;
public:
	EndingEntity(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		collidable = false;
		scroller = new Stamp("./data/basic-gfx/end.xyz", game->getGfxEngine());
		ox = x;
		oy = y+16;
		tx = x;
		ty = oy-scroller->getHeight()+224;
		sp = 1;
		counter = 0;
		counting = false;
		depth = 10000;
	};

	~EndingEntity()
	{
		delete scroller;
	};

	void onStep()
	{
		int steps = 2;

		char buf[256];
		if (!counting)
		{
			counter++;
			if (counter < 30)
				return;
			if (counter % steps == 0)
			{
				if (oy > ty)
					oy -= sp;
				else if (oy <= ty)
				{
					oy = ty;
					sp = 0;
					counter = 60;
					counting = true;
				}
			}
		}
		else
		{
			counter--;
			if (counter <= 0)
				counter = 0, counting = false, setTimer(0, 10);
		}
	};

	void onTimer(int n)
	{
		if (n == 0)
			((PGZGame*)game)->controller->changeGameStateTo(Controller::TITLE);
	}

	void onRender()
	{
		scroller->render(ox, oy);
	};
};

#endif