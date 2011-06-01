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

#pragma once
#ifndef __INSTANTIATOR_H__
#define __INSTANTIATOR_H__

#include "GamePlayState.h"
#include "Entity.h"
#include "GamePuzzleListener.h"

class Instantiator : public Entity, public GamePuzzleListener
{
protected:
	std::list<Entity*> toSpawn;
public:
	Instantiator(Game* g, GameState* gs) : Entity(-1, -1, g, gs), GamePuzzleListener()
	{
		toSpawn.clear();
		collidable = false;
	};

	~Instantiator()
	{
		// Se eliminan todas las entidades que no se hayan llegado a spawnear
		std::list<Entity*>::iterator it = toSpawn.begin();
		while (it != toSpawn.end())
			delete (*it), it++;

		toSpawn.clear();
	};

	void addEntity(Entity* e)
	{
		if (isPuzzleSolved())
			((GamePlayState*)world)->add(e);
		else
			toSpawn.push_back(e);
	};

	void removeEntity(Entity* e)
	{
		int oldsize = toSpawn.size();
		toSpawn.remove(e);
		// Si estaba en la lista, la borramos
		if (e != NULL)
			if (oldsize > toSpawn.size())
				delete e;
	};

	void onSolve()
	{
		// Se añaden todas las entidades
		std::list<Entity*>::iterator it = toSpawn.begin();
		while (it != toSpawn.end())
		{
			if ((*it) != NULL)
				((GamePlayState*)world)->add((*it));
			toSpawn.remove((*it));
			it = toSpawn.begin();
		}

		instance_destroy();
	};
};

#endif