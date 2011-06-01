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

#include "NormalTerrain.h"

// Constructora
NormalTerrain::NormalTerrain() : Terrain()
{
}

// Destructora
NormalTerrain::~NormalTerrain()
{
}

// i columnas, j filas
void NormalTerrain::toTiles(int** source, Screen* screen, int w, int h, int i, int j)
{
	int col = 2*i;
	int row = 2*j;

	if (i < w && i >= 0 && j < h && j >= 0 && screen != NULL){
		// simplemente pone su tile gráfico en la posición indicada de la pantalla
		screen->setTile(col, row, tile);
		screen->setTile(col+1, row, tile + 1);
		screen->setTile(col, row+1, tile + chipsetW);
		screen->setTile(col+1, row+1, tile + chipsetW + 1);
	}
}

void NormalTerrain::toSolids(int** screen, int w, int h, int i, int j)
{
	// ??
}