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

class SpaceBullet : public Entity
{
protected:
	float sp;
	float acc;

public:
	SpaceBullet(int x, int y, int sp, Game* g, GameState* gs) : Entity(x, y, g, gs)
	{
		this->sp = (float) sp;
		mask = new MaskBox(0, 0, 12, 4, "pbullet", 1, 1);
		collidable = true;
		acc = 0.6;
	};

	void onInit()
	{
		graphic = new Stamp("gfx/gunfire-bullet.png", game->getGfxEngine());
	};

	void onStep()
	{
		sp += acc;
		x += (int) sp;
		if (x > 320 || x < 0)
			instance_destroy();
	};
};