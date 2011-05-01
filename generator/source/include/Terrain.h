#pragma once

#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <vector>
#include "Screen.h"

using namespace std;

class Terrain
{
	public:
		enum TerrainType {none, walk, solid, water};

	protected:
		int idTerrain;			// Identificador del terreno
		int chipsetW;			// Ancho del chipset medido en tiles(8x8)
		int tile;				// Identificador del primer tile del terreno
		vector<int> variations;	// Vector de variaciones o combinaciones de terrenos (otros terrenos que quedarían bien con el actual)
		TerrainType type;		// Tipo de terreno

	public:
		// Constructora
		Terrain();
		// Destructora
		virtual ~Terrain();

		// inicia el terreno
		void init(int idTerrain, int tile, vector<int> variations, TerrainType type, int width);

		// Hablar este método
		virtual void toTiles(int** source, int** screen, int w, int h, int i, int j) = 0;

		// Getter del vector de variaciones
		vector<int> getVariations();

		// Getter del tipo
		TerrainType getType();

		// Getter del Id
		int getId();
};

#endif