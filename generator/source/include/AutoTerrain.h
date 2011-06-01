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

#ifndef _AUTOTERRAIN_H_
#define _AUTOTERRAIN_H_

#include "Terrain.h"

class AutoTerrain : public Terrain{
	protected:

		/* Vector con las distintas posiciones del terreno (esquina superior izquieda, centro...):
		0  1  2
		3  4  5
		6  7  8
		9  10 11*/

		// Devuelve el identificador del tile en la posición indicada dentro del autotile
		int getTileIdAt(int row, int col);
		short getTileAt(int x, int y);
	
	public:
		// Constructora
		AutoTerrain();
		// Destructora
		virtual ~AutoTerrain();

		// Hablar este método
		virtual void toTiles(int** source, Screen* screen, int w, int h, int i, int j);
};

#endif