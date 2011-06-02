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

#include "Entity.h"
#include "SpriteMap.h"
#include "particle.h"
#include "SpaceBullet.h"

#include "Sfx.h"

class SpaceDude : public Entity
{
protected:
	SpriteMap* gfx;
	Input* input;

	int sp;
	int bulletsp;
	int nbul;

	bool joyMode;

public:
	SpaceDude(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
	};

	void onInit()
	{
		/****************************************************************\
		*			PONME A FALSE PARA UTILIZAR EL TECLADO				 *
		\****************************************************************/
		joyMode = true;

		graphic = new SpriteMap("gfx/shoot-dude.png", 1, 8, game->getGfxEngine());
		gfx =  (SpriteMap*) graphic;

		int a[] = {0};
		gfx->addAnim("Idle", a, 1, 1, true);

		int b[] = {1, 2, 3, 4, 5, 6, 7};
		gfx->addAnim("Shoot", b, 7, 1, false);

		gfx->playAnim("Idle");

		depth = 0;

		input = game->getInput();

		sp = 4;
		bulletsp = 5;
		nbul = 3;

		mask = new MaskBox(0, 0, 20, 20, "player", 12, 2);

		Sfx* s = new Sfx("a.wav", game->getSoundEngine());
	}

	void onStep()
	{
		float jX = 0, jY = 0;

		if (joyMode)
		{
			if (input->key(Input::kENTER)) joyMode = false;
			jX = input->joyAxis(0, 0), jY = input->joyAxis(0, 1);
		}
		else
		{
			if (input->joyButton(0, 0)) joyMode = true;

			if (input->key(Input::kLEFT)) jX = -0.9;
			else if (input->key(Input::kRIGHT)) jX = 0.9;

			if (input->key(Input::kUP)) jY = -0.9;
			else if (input->key(Input::kDOWN)) jY = 0.9;
		}
		
		if (abs(jX) > 0.2 && (int) (x+jX*sp) > 0 && (int) (x+jX*sp) < 320-48)
			x += (int) (jX*sp);

		if (abs(jY) > 0.2 && (int) (y+jY*sp) > 0 && (int) (y+jY*sp) < 144-48)
			y += (int) (jY*sp);

		if (((joyMode && input->joyButton(0, 0)) || (!joyMode && input->key(Input::kA))) && nbul > 0)
			if (gfx->animFinished() || gfx->getCurrentAnim() == "Idle")
				gfx->playAnim("Shoot");

		if (gfx->getCurrentAnim() == "Shoot" && gfx->animFinished())
			world->add(new SpaceBullet(x+46, y+12, bulletsp, game, world)), gfx->playAnim("Idle");

		world->add(new JetParticle(x+12, y+27, game, world));
	};
};