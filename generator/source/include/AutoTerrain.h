#pragma once

#ifndef _AUTOTERRAIN_H_
#define _AUTOTERRAIN_H_

#include "Terrain.h"

using namespace std;

class AutoTerrain : public Terrain{
	private:

		/* Vector con las distintas posiciones del terreno (esquina superior izquieda, centro...):
		0 1 2
		3 4 5
		6 7 8*/

		int terrainPos[9];
	
	public:
		// Constructora
		AutoTerrain();
		// Destructora
		virtual ~AutoTerrain();

		// Hablar este método
		void toTiles(int** terrainIdMap, int** screen, int w, int h, int i, int j);
		void toSolids(int** terrainIdMap, int** solids, int w, int h, int i, int j) {};
};

#endif