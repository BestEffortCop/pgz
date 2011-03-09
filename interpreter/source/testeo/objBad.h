#pragma once
#ifndef __OBJBAD_H__
#define __OBJBAD_H__

#include "Entity.h"
#include "Stamp.h"
#include "MaskCircle.h"
#include "MaskList.h"
#include "MaskBox.h"
#include "Level.h"
#include <vector>

class objBad : public Entity
{
	public:
	bool stepped;
	int counter;

	objBad(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		graphic = new Stamp("cguy.png", g->getGfxEngine());
		/*graphic->setOriginX(8);
		graphic->setOriginY(8);*/
		Mask* m1 = new MaskCircle(x, y, 25.f, "body", 8, 8);
		Mask* m2 = new MaskBox(x, y, 24, 30, "head");
		vector<Mask*>* a = new vector<Mask*>();
		a->push_back(m1);
		a->push_back(m2);
		solid = true;

		mask = new MaskList(x, y, 64, 64, "dude", a);
		stepped = false;
		counter = 0;
		type = "c";
	}

	void onCollision(CollisionPair other);
	void onRender()
	{
		if (mask != NULL)
		{
			game->getGfxEngine()->renderRectangle(mask->posX(), mask->posY(), mask->width, mask->height, Color::Red);
		}
		graphic->render(x, y);
	}
	void onStep()
	{
		counter++;
		//graphic->setRotation((float) sin(counter*3.14/180)*25);
	}
};

#endif
