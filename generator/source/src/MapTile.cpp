#include "MapTile.h"

// Constructora.
MapTile::MapTile(){
	tileId;
	solid;
	zoneNumber;
	entity = new GenEntity();
}

// Destructora.
MapTile::~MapTile(){
}

// Getters.
int MapTile::getTileId(){
	return tileId;
}

int MapTile::getSolid(){
	return solid;
}

int MapTile::getZoneNumber(){
	return zoneNumber;
}

GenEntity* MapTile::getEntity(){
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

void MapTile::setEntity(GenEntity* ent){
	entity = ent;
}
