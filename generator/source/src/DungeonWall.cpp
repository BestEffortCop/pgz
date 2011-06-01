/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//or by playing it in its actual state.												//
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

#include "DungeonWall.h"

DungeonWall::DungeonWall() : AutoTerrain(){}

DungeonWall::~DungeonWall(){}

void DungeonWall::toTiles(int** source, Screen* screen, int w, int h, int col, int row){

	short* aux = new short[1];
	aux[0] = 1;

	if (col < w && col >= 0 && row < h && row >= 0 && screen != NULL && source != NULL)
	{
		// Estamos en un borde de la pantalla
		if (col == 0 || row == 0 || col == w - 1 || row == h - 1)
		{
			// Los cuatro casos en los que hay una puerta adyacente
			if (col != 0 && source[col-1][row] != idTerrain)		// puerta de arriba o de abajo
				setTile(screen, col, row, getTileIdAt(4, 0));
			else if (col != w-1 && source[col+1][row] != idTerrain)	// puerta de arriba o de abajo
				setTile(screen, col, row, getTileIdAt(4, 4));
			else if (row != 0 && source[col][row-1] != idTerrain)	// puerta de izquierda o derecha
				setTile(screen, col, row, getTileIdAt(2, 2));
			else if (row != h-1 && source[col][row+1] != idTerrain)	// puerta de izquierda o derecha
				setTile(screen, col, row, getTileIdAt(6, 2));

			// Caso en el que no hay puerta adyacente
			else
				setTile(screen, col, row, getTileIdAt(2, 2)); // debería ser 4, 2 pero peta por el tile maldito
		}
		// No estamos en un borde de la pantalla
		else
			if (source[col][row - 1] == idTerrain)	// Arriba
				if (source[col - 1][row] == idTerrain) // Izquierda
					if (source[col + 1][row] == idTerrain) // Derecha
						if (source[col][row + 1] == idTerrain) // Abajo
							if (source[col+1][row+1] == idTerrain) // Abajo-Derecha
								if (source[col-1][row+1] == idTerrain) // Abajo-Izquierda
									setTile(screen, col, row, getTileIdAt(4, 2));
								else
									setTile(screen, col, row, getTileIdAt(0, 0));
							else
								setTile(screen, col, row, getTileIdAt(0, 4));
						else
							setTile(screen, col, row, getTileIdAt(6, 2));
					else
						if (source[col][row + 1] == idTerrain)	// Abajo
							setTile(screen, col, row, getTileIdAt(4, 4));
						else
							setTile(screen, col, row, getTileIdAt(6, 4));
				else
					if (source[col + 1][row] == idTerrain) // Derecha
						if (source[col][row + 1] == idTerrain) // Abajo
							setTile(screen, col, row, getTileIdAt(4, 0));
						else
							setTile(screen, col, row, getTileIdAt(6, 0));
					else
						setTile(screen, col, row, getTileIdAt(4, 2));			// NO DEBERIA DE METERSE AQUI JAMAS DE LOS JAMASES!!!!!!

			else 
				if (source[col - 1][row] == idTerrain) // Izquierda
					if (source[col + 1][row] == idTerrain) // Derecha
						if (source[col][row + 1] == idTerrain){ // Abajo
							setTile(screen, col, row, getTileIdAt(2, 2));		// AQUI METER ENTIDADES
							//screen->addEntity(new EntityTiled(TILEDENTITY, col , row, -1, -1, 1, chipsetW / 2 + tile16 + 1, aux, 1));
						}
						else
							setTile(screen, col, row, getTileIdAt(2, 2));		// NO DEBERIA DE METERSE AQUI JAMAS DE LOS JAMASES!!!!!!
					else
						if (source[col][row + 1] == idTerrain){	// Abajo
							//setTile(screen, col, row, getTileIdAt(2, 4));		// AQUI METER ENTIDADES
							screen->addEntity(new EntityTiled(TILEDENTITY, col, row, -1, -1, 1, chipsetW / 2 + tile16 + 2, aux, 1));
						}
						else
							setTile(screen, col, row, getTileIdAt(2, 2));		// NO DEBERIA DE METERSE AQUI JAMAS DE LOS JAMASES!!!!!!
				else
					if (source[col + 1][row] == idTerrain) // Derecha
						if (source[col][row + 1] == idTerrain){ // Abajo
							//setTile(screen, col, row, getTileIdAt(2, 0));		// AQUI METER ENTIDADES
							screen->addEntity(new EntityTiled(TILEDENTITY, col, row, -1, -1, 1, chipsetW / 2 + tile16, aux, 1));
						}
						else
							setTile(screen, col, row, getTileIdAt(2, 2));		// NO DEBERIA DE METERSE AQUI JAMAS DE LOS JAMASES!!!!!!
					else
						setTile(screen, col, row, getTileIdAt(2, 2));			// NO DEBERIA DE METERSE AQUI JAMAS DE LOS JAMASES!!!!!!						
	}
}

void DungeonWall::setTile(Screen* s, int col, int row, int tile){

	// pintamos en 8x8
	col = 2*col;
	row = 2*row;

	s->setTile(col, row, tile);					// Arriba izquierda
	s->setTile(col+1, row, tile+1);				// Arriba derecha
	s->setTile(col, row+1, tile+chipsetW);		// Abajo izquierda
	s->setTile(col+1, row+1, tile+chipsetW+1);	// Abajo derecha
}