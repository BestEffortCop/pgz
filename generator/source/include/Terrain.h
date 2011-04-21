#pragma once

#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <vector>

using namespace std;

class Terrain
{
	public:
		enum TerrainType {none, walk, solid, water};

	protected:
		int idTerrain;			// Identificador del terreno
		int tile;				// Número del tile del terreno dentro del tileset
		vector<int> variations;	// Vector de variaciones o combinaciones de terrenos (otros terrenos que quedarían bien con el actual)
		TerrainType type;		// Tipo de terreno

	public:
		// Constructora
		Terrain();
		// Destructora
		virtual ~Terrain();

		// inicia el terreno
		void init(int idTerrain, vector<int> variations, TerrainType type);

		// Hablar este método
		virtual void toTiles(int** screen, int w, int h, int i, int j) = 0;

		// Getter del vector de variaciones
		vector<int> getVariations();

		// Getter del tipo
		TerrainType getType();

		// Getter del Id
		int getId();
};

#endif