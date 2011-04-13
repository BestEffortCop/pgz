#pragma once
#ifndef _PUSHTESTER_H_
#define _PUSHTESTER_H_

#include "Entity.h"
#include "Stamp.h"
#include "Player.h"
#include "iPushable.h"

class PushableTester : public Entity, public iPushable
{
private:

public:

	PushableTester(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		mask = new MaskBox(0, 0, 16, 16, "pushtest");
		graphic = new Stamp("data/graphics/coltest.png", g->getGfxEngine());
		iPushable::init(3);
		collidable = true;
		//solid = true;

		depth = y;
	};

	void onStep()
	{ 
	};

	void onCollision(CollisionPair pair, Entity* other)
	{
		if (pair.b == "player")
		{
			iPushable::onPush(this, ((Player*) other)->dir);
		}
	};

};

#endif