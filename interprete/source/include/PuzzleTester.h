#pragma once
#ifndef __PTESTER_J__
#define __PTESTER_J__

#include "Entity.h"
#include "GamePuzzleElement.h"
#include "Stamp.h"

class PuzzleTester : public Entity, public GamePuzzleElement
{
protected:
	bool once;
public:
	PuzzleTester(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs), GamePuzzleElement()
	{
		graphic = new Stamp("data/graphics/coltest.png", g->getGfxEngine());
		mask = new MaskBox(x, y, 16, 16, "puzzle");
		once = false;
	}
	~PuzzleTester()
	{
	};

	void onStep()
	{
		if (isPuzzleSolved())
			graphic->setColor(Color::Red);
		else
			graphic->setColor(Color::White);

		if (!place_meeting(x, y, "player"))
			once = false;
	};

	void onCollision(CollisionPair p, Entity* other)
	{
		if (p.b == "player" && !once)
		{
			switchPuzzle();
			once = true;
		}
	}
};

#endif