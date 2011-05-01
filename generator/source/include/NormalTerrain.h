#pragma once

#ifndef _NORMALTERRAIN_H_
#define _NORMALTERRAIN_H_

#include "Terrain.h"

class NormalTerrain : public Terrain{

	public:
		// Constructora
		NormalTerrain();
		// Destructora
		virtual ~NormalTerrain();

		// Hablar este método
		void toTiles(int** source, Screen* screen, int w, int h, int i, int j);
		void toSolids(int** screen, int w, int h, int i, int j);
};

#endif