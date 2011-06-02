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

class JetParticle : public Entity
{
public:
	JetParticle(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		mask = NULL;
		collidable = false;

		depth = 10;

		graphic = new SpriteMap("gfx/jetfire-part.png", 4, 1, g->getGfxEngine());
		int a[] = {0, 1, 2, 3};
		((SpriteMap*) graphic)->addAnim("a", a, 4, 2, false);
		((SpriteMap*) graphic)->playAnim("a");
	};

	void onStep()
	{
		x -= 1+rand()%3;
		if (((SpriteMap*) graphic)->animFinished())
			instance_destroy();
	};
};