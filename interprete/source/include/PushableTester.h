#pragma once
#ifndef _PUSHTESTER_H_
#define _PUSHTESTER_H_

#include "Entity.h"
#include "Stamp.h"
#include "Player.h"
#include "iPushable.h"
#include "HelperTypes.h"
#include <set>

class PushableTester : public iPushable, public Entity
{
private:
public:

	PushableTester(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		mask = new MaskBox(0, 0, 16, 16, "pushtest");
		graphic = new Stamp("data/graphics/coltest.png", g->getGfxEngine());
		iPushable::init(1);
		collidable = true;
		mask->type = "pushable";
		type = "pushable";
		solid = true;

		depth = y;
	};

	~PushableTester()
	{
	};

	void onStep()
	{
		depth = y;
	};
};

#endif