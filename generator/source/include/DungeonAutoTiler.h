#pragma once

#ifndef _DUNGEONAUTOTILER_H_
#define _DUNGEONAUTOTILER_H_

#include "AutoTiler.h"
#include <vector>
#include "DungeonWall.h"

class DungeonAutoTiler : public AutoTiler{
	private:

		// Carga la configuración propia de la mazmorra
		bool loadDungeonConfig(FILE* file);

		// Carga todos los muros posibles
		bool loadWalls(FILE* file);

		// Carga todas las decoraciones posibles
		bool loadDunDecorationList(FILE* file);

		// Carga los datos de cada muro
		DungeonWall* loadWall(FILE* file);

	public:

		// Constructora
		DungeonAutoTiler(std::string tileSetPath);
		// Destructora
		~DungeonAutoTiler();
};

#endif