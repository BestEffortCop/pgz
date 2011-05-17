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
	protected:
//		string zone;						// Tipo de zona en la que se encuentra la pantalla	(No necesario)
//		string theme;						// Temática del juego								(No necesario)
		std::vector<Terrain*> terrainList;		// Vector de terrenos
		std::vector<Decoration::DecorationData> decorationList;	// Vector de decoraciones

		// -------------------------- Métodos auxiliares ---------------------------------------------

		int findTerrain(int id); // devuelve la posición en la lista de terrenos del terreno indicado por id

		std::string getConfigurationFileName(std::string gfxPath);

		bool loadTerrainList(FILE* file);
		bool loadDecorationList(FILE* file);

		Terrain* loadTerrain(FILE* file);
		Decoration::DecorationData loadDecoration(FILE* file);
		bool loadDecorationTiles(FILE* file, int num, Decoration::DecorationData* dest);

		Decoration::DecorationSize computeSize(Decoration::DecorationData data);

		int chipsetWidth;

		// Devuelve el archivo abierto para el DungeonAutoTiler y WorldAutoTiler sigan leyendo datos
		FILE* loadTilesetConfig(std::string tilesetPath);

	public:
		// Constructora	
		AutoTiler();

		// Destructora
		~AutoTiler();

		//int getTerrain();
		virtual Terrain* getTerrain(int id);
		virtual int getTerrainId(Terrain::TerrainType type);
		//int getVariation(int id);
		virtual int getVariation(int id, Terrain::TerrainType type);

		//Decoration* getDecoration(mySize size);
		Decoration* getDecoration(int idDeco);
		Decoration* getDecoration(Decoration::DecorationType type, Decoration::DecorationSize size, int idTerrain);
};

#endif