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