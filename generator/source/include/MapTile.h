#pragma once

#ifndef _MAPTILE_H_
#define _MAPTILE_H_

#include <string>

using namespace std;

typedef enum {portal_w, portal_d} type_t;

struct Point 
{
	int x;
	int y;
};

// Paquete de información sobre una Zona
struct ZoneInfo 
{
	// Tema de la zona, si es NULL significa que no la especificamos y genOverworld la elige.
	string themeId;
	// Mássssssssssss ? 
};

struct entity_t 
{
	type_t type;
	string dungeon_path;
	pair<int, int> dest;
};

class MapTile 
{
	private:
			
		int tileId;			// id del tipo de tile que corresponde a esta posición
		int solid;			// tipo de sólido que corresponde a esta posición
		int zoneNumber;		// zona del mapa a la que pertenece esta posición
		entity_t* entity;	// entidad que hay (o no) en esta posición
	
	public:
		// Constructora y destructora
		MapTile();
		~MapTile();
		
		// Getters y Setters
		int getTileId();
		int getSolid();
		int getZoneNumber();
		entity_t* getEntity();
		
		void setTileId(int id);
		void setSolid(int sol);
		void setZoneNumber(int num);
		void setEntity(entity_t* ent);
};

#endif
