#pragma once
#ifndef __FLOORBUTTON_H__
#define __FLOORBUTTON_H__

#include "Entity.h"
#include "GamePuzzleElement.h"
#include "Stamp.h"

class FloorButton : public Entity, public GamePuzzleElement
{
protected:
	bool once;
public:
	FloorButton(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs), GamePuzzleElement()
	{
		graphic = new Stamp("data/graphics/coltest.png", g->getGfxEngine());
		mask = new MaskBox(x, y, 16, 16, "puzzle");
		once = false;
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

		if (!place_meeting(x, y, "player") || "pushable")
			once = false, unsolvePuzzle();
	};

	void onCollision(CollisionPair p, Entity* other)
	{
		if ((p.b == "player" || p.b == "pushable") && !once)
		{
			solvePuzzle();
			once = true;
		}
	}
};

#endif