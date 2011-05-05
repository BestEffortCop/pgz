#pragma once

#ifndef _DUNGEONAUTOTILER_H_
#define _DUNGEONAUTOTILER_H_

#include "AutoTiler.h"
#include <vector>

class DungeonAutoTiler : public AutoTiler{
	private:

		// Carga la configuración propia de la mazmorra
		bool loadDungeonConfig(FILE* file);

	public:

		// Constructora
		DungeonAutoTiler(std::string tileSetPath);
		// Destructora
		~DungeonAutoTiler();
};

#endif