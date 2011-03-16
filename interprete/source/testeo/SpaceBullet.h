#pragma once

#include "Entity.h"
#include "Stamp.h"

class SpaceBullet : public Entity
{
protected:
	float sp;
	float acc;

public:
	SpaceBullet(int x, int y, int sp, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		this->sp = (float) sp;
		mask = new MaskBox(0, 0, 12, 4, "pbullet", 1, 1);
		collidable = true;
		acc = 0.6;
	};

	void onInit()
	{
		graphic = new Stamp("gfx/gunfire-bullet.png", game->getGfxEngine());
	};

	void onStep()
	{
		sp += acc;
		x += (int) sp;
		if (x > 320 || x < 0)
			instance_destroy();
	};
};