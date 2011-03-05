#pragma once
#ifndef __OBJBAD_H__
#define __OBJBAD_H__

#include "Entity.h"
#include "Stamp.h"
#include "MaskBox.h"
#include "Level.h"

class objBad : public Entity
{
	public:
	bool stepped;
	int counter;

	objBad(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		graphic = new Stamp("badguy.png", g->getGfxEngine());
		graphic->setOriginX(8);
		graphic->setOriginY(8);
		mask = new MaskBox(x, y, 16, 16, "aloha");
		stepped = false;
		counter = 0;
	}

	void onCollision(CollisionPair other);

	void onStep()
	{
		counter++;
		graphic->setRotation((float) sin(counter*3.14/180)*25);
	}
};

#endif
