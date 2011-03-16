#pragma once

#ifndef _MAPTILE_H_
#define _MAPTILE_H_

#include <string>

#include "GenTypes.h"

using namespace std;

class MapTile
{
	private:

		int tileId;			// id del tipo de tile que corresponde a esta posición
		int solid;			// tipo de sólido que corresponde a esta posición
		int zoneNumber;		// zona del mapa a la que pertenece esta posición
		GenEntity* entity;	// entidad que hay (o no) en esta posición

	public:
		// Constructora y destructora
		MapTile();
		~MapTile();

		// Getters y Setters
		int getTileId();
		int getSolid();
		int getZoneNumber();
		GenEntity* getEntity();

		void setTileId(int id);
		void setSolid(int sol);
		void setZoneNumber(int num);
		void setEntity(GenEntity* ent);
};

#endif
