#pragma once
#ifndef __OBJLIGHT_H__
#define __OBJLIGHT_H__

#include "Entity.h"
#include "Stamp.h"
#include "MaskBox.h"

class objLight : public Entity
{
	public:


	objLight(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		graphic = new Stamp("light.png", g->getGfxEngine());
		mask = new MaskBox(x, y, 4, 4, "aloha ranurado");
		visible = false;
	}

	void onStep()
	{
		setVisible(false);
	}
};
#endif
