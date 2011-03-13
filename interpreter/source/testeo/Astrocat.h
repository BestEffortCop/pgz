#pragma once

#include "Entity.h"
#include "Stamp.h"

class AstroCat : public Entity
{
protected:
	float vsp;
	float hsp;
	int yoffset;
	Color* myColor;
	bool hit;

public:
	AstroCat(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		yoffset = y;
		mask = new MaskBox(0, 0, 23, 21, "enemy", 4, 6);
		collidable = true;
		hit = false;
	};

	void onInit()
	{
		graphic = new Stamp("gfx/astrocat.png", game->getGfxEngine());
		hsp = -4+rand()%5;
		vsp = -1+2*rand()%1;
		myColor = new Color(rand()%255, rand()%255, rand()%255);
		graphic->setColor(*myColor);
	};

	void onStep()
	{
		x += hsp;
		y = yoffset+vsp*sin(x*3.1415/180)*64;

		if (x < -32)
			instance_destroy();

		if (getTimer(0) > 0)
			graphic->setColor(Color(rand()%255, rand()%100, rand()%100));
	};

	void onTimer(int n)
	{
		if (n == 0)
			instance_destroy();
	};

	void onCollision(CollisionPair pair, Entity* other)
	{
		if (pair.b == "pbullet" && other != NULL && getTimer(0) < 0)
			other->instance_destroy(), hit = true, setTimer(0, 5);
	};
	
	void onDestroy();
};