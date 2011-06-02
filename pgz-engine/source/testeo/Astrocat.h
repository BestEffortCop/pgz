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
#include "Stamp.h"
#include "Sfx.h"

class AstroCat : public Entity
{
protected:
	float vsp;
	float hsp;
	int yoffset;
	Color* myColor;
	bool hit;

	Sfx* hitS;

public:
	AstroCat(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		yoffset = y;
		mask = new MaskBox(0, 0, 23, 21, "enemy", 4, 6);
		collidable = true;
		hit = false;

		hitS = new Sfx("ball.wav", g->getSoundEngine());
	};

	void onInit()
	{
		graphic = new Stamp("gfx/astrocat.png", game->getGfxEngine());
		hsp = -4+rand()%5;
		vsp = -1+2*rand()%1;
		myColor = new Color(rand()%255, rand()%255, rand()%255);
		graphic->setColor(*myColor);
	};

	void onStep()
	{
		x += hsp;
		y = yoffset+vsp*sin(x*3.1415/180)*64;

		if (x < -32)
			instance_destroy();

		if (getTimer(0) > 0)
			graphic->setColor(Color(rand()%255, rand()%100, rand()%100));
	};

	void onTimer(int n)
	{
		if (n == 0)
			instance_destroy();
	};

	void onCollision(CollisionPair pair, Entity* other)
	{
		if (pair.b == "pbullet" && other != NULL && getTimer(0) < 0)
			other->instance_destroy(), hit = true, hitS->play(),setTimer(0, 5);
	};
	
	void onDestroy();
};