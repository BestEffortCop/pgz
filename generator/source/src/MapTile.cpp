#include "MapTile.h"

// Constructora.
MapTile::MapTile(){
}

// Destructora.
~MapTile(){
}

// Getters.
int MapTile::getTileId(){
	return tileId;
}

int MapTile::getSolid(){
	return solid;
}

int MapTile::getZoneNumber(){
	return zonNumber;
}

entity_t* MapTile::getEntity(){
	return entity;
}

// Setters.
void MapTile::setTileId(int id){
	tileId = id;
}

void MapTile::setSolid(int sol){
	solid = sol;
}

void MapTile::setZoneNumber(int num){
	zoneNumber = num;
}

void MapTile::setEntity(entity_t* ent){
	entity = ent;
}