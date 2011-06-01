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

/*#pragma once

#ifndef __I_PULLABLE_H__
#define __I_PULLABLE_H__

#include "HelperTypes.h"
#include "Entity.h"
#include "Controller.h"
#include <set>

using namespace std;

class iPullable
{
	private:
		bool locked;
		bool useConstraints;
		set<Direction> pullConstraints;
		std::pair<int, int> move(Entity *ent, Direction dir);
		
	public:
		// Distancia pullable en cada step
		int stepPullDist;
		
		// Por defecto será pullable
		iPullable();
		iPullable(int stepPullDist, bool useConstraints = false);
		virtual ~iPullable();

		void init(int stepPullDist, bool useConstraints = false);
		void lockPull();
		void unlockPull();
		bool isLockedPull();

		// Pullea y devuelve si ha sido pulled con éxito.
		// Param ent: nosotros (lo que va a ser pulled)
		// Param dir: dirección en la que nos pullean.
		virtual std::pair<int, int> onPull(Entity *ent, Direction dir);

		// Indicamos en qué direcciones puede pullearse (Activa los constraints)
		void setConstraints(set<Direction> pushConstrains);
};


#endif
*/