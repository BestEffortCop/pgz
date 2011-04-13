#pragma once

#ifndef _MAPTILE_H_
#define _MAPTILE_H_

#include <string>
#include "GenMath.h"

using namespace std;

class MapTile
{
	private:

		short tileId;			// id del tipo de tile que corresponde a esta posición
		short solid;			// tipo de sólido que corresponde a esta posición
		short zoneNumber;		// zona del mapa a la que pertenece esta posición

	public:
		// Constructora y destructora
		MapTile();
		~MapTile();

		// Getters y Setters
		short getTileId();
		short getSolid();
		short getZoneNumber();

		void setTileId(short id);
		void setSolid(short sol);
		void setZoneNumber(int num);
};

#endif
