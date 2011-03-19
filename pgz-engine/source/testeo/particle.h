#pragma once

#include "Entity.h"
#include "SpriteMap.h"

class JetParticle : public Entity
{
public:
	JetParticle(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		mask = NULL;
		collidable = false;

		depth = 10;

		graphic = new SpriteMap("gfx/jetfire-part.png", 4, 1, g->getGfxEngine());
		int a[] = {0, 1, 2, 3};
		((SpriteMap*) graphic)->addAnim("a", a, 4, 2, false);
		((SpriteMap*) graphic)->playAnim("a");
	};

	void onStep()
	{
		x -= 1+rand()%3;
		if (((SpriteMap*) graphic)->animFinished())
			instance_destroy();
	};
};