#pragma once

#ifndef _WORLDAUTOTILER_H_
#define _WORLDAUTOTILER_H_

#include "AutoTiler.h"

class WorldAutoTiler : public AutoTiler
{
	protected:

		// cargamos las decoraciones propias del mundo
		FILE* loadWorldConfig(FILE* f);

		// cargamos cada decoración
		bool loadWorldDeco(FILE* f);

	public:
		// Constructora	
		WorldAutoTiler(std::string tileSetPath);

		// Destructora
		~WorldAutoTiler();
};

#endif