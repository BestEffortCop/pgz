#pragma once

#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <vector>
#include "Screen.h"

using namespace std;

class Terrain
{
	public:
		enum TerrainType {none, walk, solid, water, dungeonWall, dungeonEntrance};

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