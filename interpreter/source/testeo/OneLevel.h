#pragma once

#ifndef __ONELEVEL_H__
#define __ONELEVEL_H__

#include "GameState.h"
#include "Stamp.h"
#include "Canvas.h"
#include "SpaceDude.h"
#include "Astrocat.h"

class OneLevel : public GameState
{
    protected:
        Stamp* bg0a, *bg0b, *bg1a, *bg1b;
		int bgx0, bgx1, bgsp0, bgsp1, bgw;
		int bgy0, bgy1;

		Image* point;
		Canvas* scoreDisplay;

		SpaceDude* player;

		int score;

    public:
        OneLevel(Game* g) : GameState(g, 320, 144)
        {
            g->getGfxEngine()->setScreenBackgroundColor(Color(30, 30, 30));
            bg0a = new Stamp("gfx/pharalaxbg0.png", g->getGfxEngine());
			bg0b = new Stamp("gfx/pharalaxbg0.png", g->getGfxEngine());
			bg1a = new Stamp("gfx/pharalaxbg1.png", g->getGfxEngine());
			bg1b = new Stamp("gfx/pharalaxbg1.png", g->getGfxEngine());

			bgx0 = 0;
			bgx1 = 0;
			bgy0 = 96;
			bgy1 = -32;
			bgw = 320;
			bgsp0 = 4;
			bgsp1 = 2;

			player = new SpaceDude(16, 48, game, this);
			_add(player);

			//point = new Image("gfx/point.png", g->getGfxEngine(), true, false);

			scoreDisplay = new Canvas(32, 8, 256, 16, g->getGfxEngine());
			scoreDisplay->clear(Color(5, 10, 30));
			scoreDisplay->refresh();
			scoreDisplay->setAlpha(0.6);

			score = 0;
        }

        void onStep()
        {
			bgx0 -= bgsp0;
			if (bgx0 < -bgw)
				bgx0 += bgw;

			bgx1 -= bgsp1;
			if (bgx1 < -bgw)
				bgx1 += bgw;

			if (rand()%25 < 1)
				add(new AstroCat(320, 24+rand()%144-24-32, game, this));

			bgy0 = roomh-32+(32-player->y)/2,
			bgy1 = -32+32-player->y/4;

			if (game->getInput()->key(Input::kO))
				oneDown(Color::Magenta);

			game->getGfxEngine()->setScreenBackgroundColor(Color(rand()%255, rand()%255, rand()%255));
        }

        void renderBG()
        {   
			bg1a->render(bgx1, bgy1);
			bg1b->render(bgx1+bgw, bgy1);

			scoreDisplay->render(32, 8);

			bg0a->render(bgx0, bgy0);
			bg0b->render(bgx0+bgw, bgy0);
        }

		void oneDown(Color c)
		{
			if (score < 64)
			{
				int px = score % 32;
				int py = score / 32;

				Stamp* tmp = new Stamp("gfx/point.png", game->getGfxEngine());
				tmp->setColor(c);
				
				scoreDisplay->draw(tmp, px*8, py*8);
				scoreDisplay->refresh();

				delete tmp;

				score++;
			}
			else score = 0, scoreDisplay->clear(Color::Black), scoreDisplay->refresh();
		};
};

#endif // __ONELEVEL_H__
