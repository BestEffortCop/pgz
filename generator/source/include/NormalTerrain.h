#pragma once

#ifndef _NORMALTERRAIN_H_
#define _NORMALTERRAIN_H_

#include "Terrain.h"

using namespace std;

class NormalTerrain : public Terrain{
	private:
	
	public:
		// Constructora
		NormalTerrain();
		// Destructora
		virtual ~NormalTerrain();

		// Hablar este método
		void toTiles(int** screen, int w, int h, int i, int j);

};

#endif