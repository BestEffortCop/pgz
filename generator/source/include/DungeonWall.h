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

#ifndef _DUNGEONWALL_H_
#define _DUNGEONWALL_H_

#include <vector>
#include "AutoTerrain.h"

class DungeonWall : public AutoTerrain{
	private:

		void setTile(Screen* s, int col, int row, int tile);

	public:

		// Constructora
		DungeonWall();
		// Destructora
		virtual ~DungeonWall();

/*		// Inicialización de atributos
		void init(int wallId, int tileId, vector<int> variations, TerrainType type, int chipsetWidth);
*/
		// Hablar este método
		void toTiles(int** source, Screen* screen, int w, int h, int i, int j);
};

#endif