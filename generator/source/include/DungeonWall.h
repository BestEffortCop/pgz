#pragma once

#ifndef _DUNGEONWALL_H_
#define _DUNGEONWALL_H_

#include <vector>
#include "AutoTerrain.h"

class DungeonWall : public AutoTerrain{
	private:

		void setTile(Screen* s, int col, int row, int tile);

	public:

		// Constructora
		DungeonWall();
		// Destructora
		virtual ~DungeonWall();

		// Inicialización de atributos
		void init(int wallId, int tileId, vector<int> variations, int chipsetWidth);

		// Hablar este método
		void toTiles(int** source, Screen* screen, int w, int h, int i, int j);
};

#endif