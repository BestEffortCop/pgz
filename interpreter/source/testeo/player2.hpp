#pragma once
#ifndef _P2_H_
#define _P2_H_

#include "Entity.h"
#include "Spritemap.h"
#include "MaskBox.h"

class Player2 : public Entity
{
private:
	int sp;

public:
	Player2(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		sp = 2;
		graphic = new SpriteMap("spaceman.png", 3, 2, g->getGfxEngine());
		SpriteMap* gfx = (SpriteMap*) graphic;

		mask = new MaskBox(7, 8, 50, 56, "ranurado");
		collidable = true;

		int a[4] = {0, 1, 0, 2};
		int b[4] = {3, 4, 3, 5};
		gfx->addAnim("WalkR", a, 4, 4, true);
		gfx->addAnim("WalkL", b, 4, 4, true);
		gfx->setColor(Color(rand()%255, rand()%255, rand()%255));

		gfx->playAnim("WalkR", 0.f, false);
		gfx->stopAnim();

		game->getInput()->joySet("p2b1", 1, 0);
		game->getInput()->joySet("p2b2", 1, 2);
	}

	void onStep()
	{
		int ox = x;
		int oy = y;
		float jX = game->getInput()->joyAxis(1, 0);
		float jY = game->getInput()->joyAxis(1, 1);
		SpriteMap* gfx = (SpriteMap*) graphic;

		if (abs(jX) > 0.3)
			x += (int) (sp*jX);
		if (abs(jY) > 0.3)
			y += (int) (sp*jY);

		if (ox != x || oy != y)
		{
			if (jX < 0)
				gfx->playAnim("WalkL", abs(jX), true);
			else if (jX > 0)
				gfx->playAnim("WalkR", abs(jX), true);
			else if (jY != 0)
				gfx->playAnim(gfx->getCurrentAnim(), abs(jY), true);
		}

		if (game->getInput()->joyPressed("p2b1"))
			gfx->setColor(Color(rand()%255, rand()%255, rand()%255));
		if (game->getInput()->joyReleased("p2b2"))
			game->setFinished(true);
	}

	void onRender()
	{
		graphic->render(x, y);

		if (mask != NULL)
		{
			//game->getGfxEngine()->renderRectangle(mask->x, mask->y, mask->width, mask->height, Color::Red);
		}
	}
};

#endif