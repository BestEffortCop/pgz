/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//	  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef __ONELEVEL_H__
#define __ONELEVEL_H__

#include "GameState.h"
#include "Stamp.h"
#include "Canvas.h"
#include "SpaceDude.h"
#include "Astrocat.h"

#include "BGM.h"

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

		Bgm* b, *b2;

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

			point = new Image("gfx/point.png", g->getGfxEngine(), true, false);

			scoreDisplay = new Canvas(32, 8, 256, 16, g->getGfxEngine());
			scoreDisplay->clear(Color(5, 10, 30));
			scoreDisplay->refresh();
			scoreDisplay->setAlpha(0.6);

			score = 0;

			b2 = new Bgm("mus2.ogg", g->getSoundEngine());
			b = new Bgm("mus.ogg", g->getSoundEngine());
			b->play();
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

			//game->getGfxEngine()->setScreenBackgroundColor(Color(rand()%255, rand()%255, rand()%255));

			if (game->getInput()->keyPressed(Input::kK))
			{
				if (game->getTargetFPS() == 30) game->setFPS(60);
				else game->setFPS(30);
			}

			if (game->getInput()->keyPressed(Input::kL))
			{
				if (b->isPlaying()) /*b->stop(),*/ b2->play();
				else /*b2->stop(),*/ b->play();
			}
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
