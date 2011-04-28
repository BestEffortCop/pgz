#pragma once
#ifndef __FLOORBUTTON_H__
#define __FLOORBUTTON_H__

#include "Entity.h"
#include "GamePuzzleElement.h"
#include "Stamp.h"

class FloorButton : public Entity, public GamePuzzleElement
{
protected:
	bool onceSolved;
	bool onceUnsolved;
public:
	FloorButton(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs), GamePuzzleElement()
	{
		graphic = new Stamp("data/graphics/coltest.png", g->getGfxEngine());
		mask = new MaskBox(x, y, 16, 16, "puzzle");
		onceSolved = false;
		onceUnsolved = true;
	}
	~FloorButton()
	{
	};

	void onStep()
	{
		if (isPuzzleSolved())
			graphic->setColor(Color::Red);
		else
			graphic->setColor(Color::White);

		if (!place_meeting(x, y, "player") && !place_meeting(x, y, "pushable"))
			if (!onceUnsolved)
			{
				onceUnsolved = true;
				onceSolved = false;
				unsolvePuzzle();
			}
	};

	void onCollision(CollisionPair p, Entity* other)
	{
		if ((p.b == "player" || p.b == "pushable") && !onceSolved)
		{
			solvePuzzle();
			onceSolved = true;
			onceUnsolved = false;
		}
	}
};

#endif