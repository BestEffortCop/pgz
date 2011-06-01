/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
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

#ifndef _MAPTILE_H_
#define _MAPTILE_H_

#include <string>
#include "GenMath.h"

using namespace std;

class MapTile
{
	private:

		short tileId;			// id del tipo de tile que corresponde a esta posición
		short solid;			// tipo de sólido que corresponde a esta posición
		short zoneNumber;		// zona del mapa a la que pertenece esta posición

	public:
		// Constructora y destructora
		MapTile();
		~MapTile();

		// Getters y Setters
		short getTileId();
		short getSolid();
		short getZoneNumber();

		void setTileId(short id);
		void setSolid(short sol);
		void setZoneNumber(int num);
};

#endif
