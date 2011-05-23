#pragma once

#ifndef _DUNGEONAUTOTILER_H_
#define _DUNGEONAUTOTILER_H_

#include "AutoTiler.h"
#include <vector>
#include <map>
#include "DungeonWall.h"

	enum DunDecorationPos {top, left, right, bottom};
	struct DungeonDecoData{
		DunDecorationPos pos; // si es hangable (antorchas) nos dice en qué pared ponerla
	};

class DungeonAutoTiler : public AutoTiler{
	
private:
		// mapa que guarda la 
		std::map<int, DungeonDecoData> dungeonDecos;

		// Carga la configuración propia de la mazmorra
		bool loadDungeonConfig(FILE* file);

		// Carga todos los muros posibles
		bool loadWalls(FILE* file);

		// Carga todas las decoraciones posibles
		bool loadDunDecorationList(FILE* file);

		// Carga los datos de cada muro
		DungeonWall* loadWall(FILE* file);

		// Carga la lista de decoraciones de mazmorra
		bool loadDungeonDecoList(FILE* file);

		// Carga los datos de cada decoración de mazmorra
		void loadDungeonDeco(FILE* file);

	public:

		// Constructora
		DungeonAutoTiler(std::string tileSetPath);
		// Destructora
		~DungeonAutoTiler();

		// devuelve la decoración de una antorcha para esa dirección
		Decoration* getDungeonDeco(DunDecorationPos pos, Decoration::DecorationType type);
};

#endif