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
		mask = new MaskBox(0, 0, 3, 3, "aloha");
		collidable = false;
	}
	void onStep();

	void onRender()
	{	
		graphic->render(x, y);

		if (mask != NULL)
		{
			game->getGfxEngine()->renderRectangle(mask->x, mask->y, mask->width, mask->height, Color::Yellow);
		}
	}
};

#endif