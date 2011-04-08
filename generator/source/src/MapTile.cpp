#include "MapTile.h"

// Constructora.
MapTile::MapTile(){
	tileId = -1;
	solid = -1;
	zoneNumber = -1;
	GPoint p;
	p.x = -1;
	p.y = -1;
}

// Destructora.
MapTile::~MapTile(){
}

// Getters.
short MapTile::getTileId(){
	return tileId;
}

short MapTile::getSolid(){
	return solid;
}

short MapTile::getZoneNumber(){
	return zoneNumber;
}

// Setters.
void MapTile::setTileId(short id){
	tileId = id;
}

void MapTile::setSolid(short sol){
	solid = sol;
}

void MapTile::setZoneNumber(int num){
	zoneNumber = num;
}
