/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "FloorButton.h"

FloorButton::FloorButton(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs), GamePuzzleElement()
{
	onceSolved = false;
	onceUnsolved = true;
}
FloorButton::~FloorButton()
{
};


void FloorButton::initGraphic(std::string gfxpath)
{
	graphic = new SpriteMap(gfxpath, 2, 1, game->getGfxEngine());
	mask = new MaskBox(x, y, 16, 16, "puzzle");

	vector<int>* vsolved = new vector<int>();
	vsolved->push_back(1);
	((SpriteMap*) graphic)->addAnim("solved", vsolved, 1, false);

	vector<int>* vunsolved = new vector<int>();
	vunsolved->push_back(0);
	((SpriteMap*) graphic)->addAnim("unsolved", vunsolved, 1, false);

	((SpriteMap*) graphic)->playAnim("unsolved");
}


void FloorButton::init(GamePuzzle* puzzle)
{
	GamePuzzleElement::init(puzzle);
}

void FloorButton::onStep()
{
	if (isPuzzleSolved())
		((SpriteMap*) graphic)->playAnim("solved");
	else
		((SpriteMap*) graphic)->playAnim("unsolved");

	if (!place_meeting(x, y, "player") && !place_meeting(x, y, "pushable"))
		if (!onceUnsolved)
		{
			onceUnsolved = true;
			onceSolved = false;
			unsolvePuzzle();
		}
};

void FloorButton::onCollision(CollisionPair p, Entity* other)
{
	if ((p.b == "player" || p.b == "pushable") && !onceSolved)
	{
		solvePuzzle();
		onceSolved = true;
		onceUnsolved = false;
	}
}

void FloorButton::onRender()
{/*
	if (visible && enabled)
		game->getGfxEngine()->renderRectangle(x, y, 16, 16, Color::Red, false);*/
	Entity::onRender();
};