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

#ifndef _ARENAENTITY_H_
#define _ARENAENTITY_H_

#include "iNotificable.h"
#include "GamePuzzleElement.h"
#include "Entity.h"
#include "Enemy.h"

class ArenaEntity : public Entity, public GamePuzzleElement, public iNotificable
{
	private:
		std::list<Enemy*> enemies;

	public:
		ArenaEntity(int x, int y, Game* g, GameState* gs);
		~ArenaEntity();

		void addEnemy(Enemy* e);
		void onNotified(Entity* e);

		void init(GamePuzzle* puzzle);
		void onStep();
		void onEndStep();
};

#endif