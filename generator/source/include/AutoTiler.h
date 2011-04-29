#pragma once

#ifndef _AUTOTILER_H_
#define _AUTOTILER_H_

#include "Terrain.h"
#include "AutoTerrain.h"
#include "NormalTerrain.h"
#include "Decoration.h"
#include <vector>

class AutoTiler
{
	private:
//		string zone;						// Tipo de zona en la que se encuentra la pantalla	(No necesario)
//		string theme;						// Temática del juego								(No necesario)
		std::vector<Terrain*> terrainList;		// Vector de terrenos
		std::vector<Decoration::DecorationData> decorationList;	// Vector de decoraciones

		// -------------------------- Métodos auxiliares ---------------------------------------------

		int findTerrain(int id); // devuelve la posición en la lista de terrenos del terreno indicado por id

		bool loadTilesetConfig(std::string tilesetPath);
		std::string getConfigurationFileName(std::string gfxPath);

		bool loadTerrainList(FILE* file);
		bool loadDecorationList(FILE* file);

		Terrain* loadTerrain(FILE* file);
		Decoration::DecorationData loadDecoration(FILE* file);
		bool loadDecorationTiles(FILE* file, int num, Decoration::DecorationData* dest);

		Decoration::DecorationSize computeSize(Decoration::DecorationData data);

	public:
		// Constructora
		AutoTiler(std::string tileSetPath);

		// Destructora
		~AutoTiler();

		//int getTerrain();
		Terrain* getTerrain(int id);
		int getTerrainId(Terrain::TerrainType type);
		//int getVariation(int id);
		int getVariation(int id, Terrain::TerrainType type);

		//Decoration* getDecoration(mySize size);
		//Decoration* getDecoration(int idTile);
		Decoration* getDecoration(Decoration::DecorationType type, Decoration::DecorationSize size, int idTerrain);
};

#endif