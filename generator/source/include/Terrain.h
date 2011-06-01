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

#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <vector>
#include "Screen.h"

using namespace std;

class Terrain
{
	public:
		enum TerrainType {none, floor, solid, water, dungeonWall, dungeonEntrance, path};

	protected:
		int idTerrain;			// Identificador del terreno
		int chipsetW;			// Ancho del chipset medido en tiles (8x8)
		int tile;				// Identificador del primer tile del terreno (8x8)
		int tile16;				// Identificador del tile en 16x16
		vector<int> variations;	// Vector de variaciones o combinaciones de terrenos (otros terrenos que quedarían bien con el actual)
		TerrainType type;		// Tipo de terreno

	public:
		// Constructora
		Terrain();
		// Destructora
		virtual ~Terrain();

		// inicia el terreno
		/*	idTerrain identificador del terreno
			tile identificador del tile dentro del chipset (en 16x16)
			variations vector de identificadores de las posibles variaciones del terreno
			type tipo del terreno
			width ancho del chipset (en 16x16) */
		void init(int idTerrain, int tile, vector<int> variations, TerrainType type, int width);

		// Hablar este método
		virtual void toTiles(int** source, Screen* screen, int w, int h, int i, int j) = 0;

		// Getter del vector de variaciones
		vector<int> getVariations();

		// Getter del tipo
		TerrainType getType();

		// Getter del Id
		int getId();
};

#endif