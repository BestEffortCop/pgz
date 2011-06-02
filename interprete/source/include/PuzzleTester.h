/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
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
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once
#ifndef __PTESTER_J__
#define __PTESTER_J__

#include "Entity.h"
#include "GamePuzzleElement.h"
#include "Stamp.h"

class PuzzleTester : public Entity, public GamePuzzleElement
{
protected:
	bool once;
public:
	PuzzleTester(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs), GamePuzzleElement()
	{
		graphic = new Stamp("data/graphics/coltest.png", g->getGfxEngine());
		mask = new MaskBox(x, y, 16, 16, "puzzle");
		once = false;
	}
	~PuzzleTester()
	{
	};

	void onStep()
	{
		if (isPuzzleSolved())
			graphic->setColor(Color::Red);
		else
			graphic->setColor(Color::White);

		if (!place_meeting(x, y, "player"))
			once = false;
	};

	void onCollision(CollisionPair p, Entity* other)
	{
		if (p.b == "player" && !once)
		{
			switchPuzzle();
			once = true;
		}
	}
};

#endif