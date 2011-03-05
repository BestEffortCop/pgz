#pragma once
#ifndef __OBJSTAR_H__
#define __OBJSTAR_H__

#include "Entity.h"
#include "Stamp.h"
#include "Level.h"

#include "MaskBox.h"

class objStar : public Entity
{
public:
	objStar(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		graphic = new Stamp("star.png", g->getGfxEngine());
		mask = new MaskBox(x, y, 3, 3, "aloha");
		collidable = false;
	}
	void onStep();
};

#endif