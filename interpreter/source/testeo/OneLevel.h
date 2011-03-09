#pragma once
#ifndef _ONELEVEL_H_
#define _ONELEVEL_H_

#include "GameState.h"
#include "SpriteTest.h"

class OneLevel : public GameState
{
protected:
	Stamp* bg1;
	Stamp* bg2;

	int posx;
	int w;

public:
	OneLevel(Game* g) : GameState(g, 240, 144)
	{
		posx = 0;
		w = 240;

		bg1 = new Stamp("thebg.png", g->getGfxEngine());
		bg2 = new Stamp("thebg.png", g->getGfxEngine());

		_add(new SpriteTest(50, 50, g, this));
	};

	void onStep()
	{
		int mx = (game->getInput()->getMouseX()-game->getGfxEngine()->getGameScreenX())/game->getGfxEngine()->getGameScreenScaleH();
		int my = (game->getInput()->getMouseY()-game->getGfxEngine()->getGameScreenY())/game->getGfxEngine()->getGameScreenScaleV();
		// The Background
		posx -= 1;
		if (posx < -w)
			posx = 0;

		// Instantiate!
		if (game->getInput()->mousePressed(Input::Right))
			add(new SpriteTest(mx, my, game, this));

		if (game->getInput()->mouseButton(Input::Middle))
			game->getGfxEngine()->setScreenBackgroundColor(Color(rand()%255, rand()%255, rand()%255));
	};

	void renderBG()
	{
		bg1->render(posx, 0);
		bg2->render(posx+w, 0);
	};
};

#endif