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

#ifndef __I_PUSHABLE_H__
#define __I_PUSHABLE_H__

#include "HelperTypes.h"
#include "Entity.h"
#include "Controller.h"
#include <set>

using namespace std;

class iPushable
{
	private:
		bool locked;
		bool useConstraints;
		set<Direction> pushConstraints;
		std::pair<int, int> move(Entity *ent, Direction dir);
		
	public:
		// Distancia empujable en cada step
		int stepPushDist;
		
		// Por defecto será empujable
		iPushable();
		iPushable(int stepPushDist, bool useConstraints = false);
		virtual ~iPushable();

		void init(int stepPushDist, bool useConstraints = false);
		void lockPush();
		void unlockPush();
		bool isLockedPush();

		// Empuja y devuelve si ha sido empujado con éxito un par con la posicion a la que moverse.
		// Param ent: nosotros (lo que va a ser empujado)
		// Param dir: dirección en la que nos empujan.
		virtual std::pair<int, int> onPush(Entity *ent, Direction dir);

		// Indicamos en qué direcciones puede empujarse (Activa los constraints)
		void setConstraints(set<Direction> pushConstrains);
};

#endif
