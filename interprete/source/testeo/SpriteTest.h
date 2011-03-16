#pragma once

#include "Entity.h"
#include "Stamp.h"

class SpriteTest : public Entity
{
protected:
public:
	SpriteTest(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		graphic = new Stamp("badguy.png", g->getGfxEngine());
		mask = new MaskBox(0, 0, 14, 14, "anus", 1, 1);
		collidable = true;
	};

	void onStep()
	{
		int mx = (game->getInput()->getMouseX()-game->getGfxEngine()->getGameScreenX())/game->getGfxEngine()->getGameScreenScaleH();
		int my = (game->getInput()->getMouseY()-game->getGfxEngine()->getGameScreenY())/game->getGfxEngine()->getGameScreenScaleV();
		if (mx > x+1 && mx < x+15 && my > y+1 && my < y+15 && game->getInput()->mouseReleased(Input::Left))
			instance_destroy();
	};

	void onCollision(CollisionPair col, Entity* other)
	{
		if (col.b == "anus" && other != NULL)
			instance_destroy();
	};
};