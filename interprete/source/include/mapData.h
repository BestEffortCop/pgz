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

#ifndef _MAPDATA_H
#define _MAPDATA_H

#include <utility>

#include "OverWorldMapStatus.h"
#include "DungeonMapStatus.h"

class MapData 
{

private:
	// Ancho en pantallas del mapa
	int width;

	// Alto en pantallas del mapa
	int height;

	// Layout del mapa
	int** layout;

	// Número de minibosses del mapa
	int numMiniBosses;

	// Número de Puzzles del mapa
	int numPuzzles;

	// Número de puertas del mapa
	int numDoors;

	// Número de collectables del mapa
	int numCollectables;

	// Identificador del mapa
	int mapId;

	// Tipo del mapa (0: ow, 1: d)
	char mapType;

	// Pantalla inicial del mapa
	std::pair<int, int> startScreen;

	// Estado del mapa
	MapStatus* mapStatus;

	// Libera la memoria del layout
	void freeLayout(int** layout);

public:
	MapData(void);

	~MapData(void);

	void init(int mapId, char type, int w, int h, const int** layout, int numPuzzles, int numDoors, int numMinibosses, int numCollectables);

	//! Obtiene el id del mapa
	int getId();

	//! Obtiene el ancho del mapa (en pantallas)
	int getWidth();

	//! Obtiene el alto del mapa (en pantallas)
	int getHeight();

	//! Obtiene el layout del mapa
	const int** getLayout();

	//! Indica si la pantalla indicada existe o no
	bool hasScreen(int x, int y);

	//! Obtiene el número total de minibosses del mapa
	int getNumMiniBosses();

	//! Obtiene el número total de puzzles del mapa
	int getNumPuzzles();

	//! Obtiene el número total de puertas del mapa
	int getNumDoors();

	//! Obtiene el número de collectables
	int getNumCollectables();

	// getExit, getStartPoint, ...
	std::pair<int, int> getStartScreen();

	//! Establece la pantalla inicial del mapa
	bool setStartScreen(int screenX, int screenY);

	MapStatus* getMapStatus();

	char getType();

	void setId(int id);
	void setWidth(int width);
	void setHeight(int height);
	void setLayout(int** layout);
	void setNumMiniBosses(int miniBosses);
	void setNumPuzzles(int puzzles);
	void setNumDoors(int doors);
	void setNumCollectables(int collectables);

	void save(FILE* f);

	void load(FILE* f);
};
#endif
