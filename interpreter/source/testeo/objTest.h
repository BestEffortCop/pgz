#pragma once
#ifndef __OBJTEST_H__
#define __OBJTEST_H__

#include "Entity.h"
#include "SpriteMap.h"
#include "MaskBox.h"

class objTest : public Entity
{
	public:

	int sp;
	bool facingR;

	objTest(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		srand((unsigned int) time(NULL));

		graphic = new SpriteMap("player-sheet.png", 3, 4, g->getGfxEngine());
		sp = 4;
		facingR = true;
		type = "player";

		mask = new MaskBox(x, y, 29, 50, "aloha");

		vector<int>* a = new vector<int>();
		a->push_back(9);
		a->push_back(10);
		a->push_back(9);
		a->push_back(11);

		((SpriteMap*) graphic)->addAnim("WalkR", a, 4, true);

		a = new vector<int>();
		a->push_back(6);
		a->push_back(7);
		a->push_back(6);
		a->push_back(8);

		((SpriteMap*) graphic)->addAnim("WalkL", a, 4, true);

		a = new vector<int>();
		a->push_back(3);
		a->push_back(4);
		a->push_back(3);
		a->push_back(5);

		((SpriteMap*) graphic)->addAnim("StandR", a, 4, true);

		a = new vector<int>();
		a->push_back(0);
		a->push_back(1);
        a->push_back(0);
		a->push_back(2);

		((SpriteMap*) graphic)->addAnim("StandL", a, 4, true);

		((SpriteMap*) graphic)->playAnim("StandR");

		graphic->setOriginX(15);
		graphic->setOriginY(25);

		game->getInput()->joySet("Jumpo1", 0, 0);
		game->getInput()->joySet("Jumpo2", 0, 1);
	}

	void onStep()
	{
		int ox = x;
		int oy = y;
		float jX = game->getInput()->joyAxis(0, 0);
		float jY = game->getInput()->joyAxis(0, 1);

		float j2X = game->getInput()->joyAxis(0, 2);
		float j2Y = game->getInput()->joyAxis(0, 3);

		if (jX < -0.3)
		{
			if (place_free((int) (x + sp*jX),y))
			{
				((SpriteMap*) graphic)->playAnim("WalkL", abs(jX), true);
				x += (int) (sp*jX);
				facingR = false;
			}
			else
				moveToContact((int) (x + sp*jX), y);
		}
		else if (jX > 0.3)
		{
			if (place_free((int) (x + sp*jX),y))
			{
				((SpriteMap*) graphic)->playAnim("WalkR", jX, true);
				x += (int) (sp*jX);
				facingR = true;
			}
			else
				moveToContact((int) (x + sp*jX), y);
		}
		if (jY < -0.3)
		{
			if (place_free(x, (int) (y + sp*jY)))
			{
				if (facingR)
					((SpriteMap*) graphic)->playAnim("WalkR", abs(jY), true);
				else
					((SpriteMap*) graphic)->playAnim("WalkL", abs(jY), true);
				y += (int) (sp*jY);
			}
			else
				moveToContact(x, (int) (y + sp*jY));
		}
		else if (jY > 0.3)
		{
			if (place_free(x,(int) (y + sp*jY)))
			{
				if (facingR)
					((SpriteMap*) graphic)->playAnim("WalkR", abs(jY), true);
				else
					((SpriteMap*) graphic)->playAnim("WalkL", abs(jY), true);
				y += (int) (sp*jY);
			}
			else
				moveToContact(x, (int) (y + sp*jY));
		}

		if ((ox == x) && (oy == y))
            if (facingR)
                ((SpriteMap*) graphic)->playAnim("StandR");
            else
                ((SpriteMap*) graphic)->playAnim("StandL");

		if (game->getInput()->joyButton("Jumpo1"))
			graphic->setColor(Color(rand()%255, rand()%255, rand()%255));
		if (game->getInput()->joyReleased("Jumpo2"))
			graphic->setAlpha((rand()%1000)/1000.f);
		
		if (abs(jY) > 0.1 && abs(jX) > 0.1)
			graphic->setRotation(float(atan2(jY, jX))*180 / 3.14f + 90);
	}

	void onRender()
	{
		graphic->render(x, y);
		if (mask != NULL)
		{
			game->getGfxEngine()->renderRectangle(mask->x, mask->y, mask->width, mask->height, Color::Blue);
		}
	}
};

#endif
