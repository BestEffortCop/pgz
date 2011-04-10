#pragma once
#ifndef _COLTESTER_H_
#define _COLTESTER_H_

#include "Entity.h"
#include "Stamp.h"
#include "Player.h"

class CollisionTester : public Entity
{
public:
	CollisionTester(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		mask = new MaskBox(0, 0, 16, 16, "coltest");
		graphic = new Stamp("data/graphics/coltest.png", g->getGfxEngine());

		depth = y;
	};

	void onCollision(CollisionPair pair, Entity* other)
	{
		if (pair.b == "player")
			((Player*) other)->onDamage(1, 0x1);
	};
};

#endif