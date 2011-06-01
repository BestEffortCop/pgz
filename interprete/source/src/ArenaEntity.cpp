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

#include "ArenaEntity.h"

ArenaEntity::ArenaEntity(int x, int y, Game* g, GameState* gs) : Entity(x,y,g,gs)
{
	solid = false;
	collidable = false;
	enemies.clear();
}

ArenaEntity::~ArenaEntity()
{
	enemies.clear();
}

void ArenaEntity::addEnemy(Enemy* e)
{
	if (isPuzzleSolved())
		e->setVisible(false);
	enemies.push_back(e);
	e->arena = this;
}

void ArenaEntity::onNotified(Entity* e)
{
//	enemies.remove((Enemy*) e);
}

void ArenaEntity::init(GamePuzzle* puzzle)
{
	/*// Siempre que se crea un arenaEntity, debe
	// desresolverse el puzzle, o eliminar a los malos
	puzzle->unsolve();*/
	GamePuzzleElement::init(puzzle);
}

void ArenaEntity::onStep()
{
	if (!isPuzzleSolved())
	{
		if(enemies.empty())
			puzzle->solve(), instance_destroy();
	}
	else
	{
		// Puzzle Resuelto
		list<Enemy*>::iterator it = enemies.begin();
		while (it != enemies.end())
		{
			if ((*it) != NULL)
				(*it)->instance_destroy();
			it++;
		}
		enemies.clear();
	}
}

void ArenaEntity::onEndStep()
{
	list<Enemy*>::iterator it = enemies.begin();
	while(it != enemies.end())
	{
		if ((*it)->dead)
		{
			it = enemies.erase(it);
		}
		else
		{
			it++;
		}
	}
}