/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "MapTile.h"

// Constructora.
MapTile::MapTile(){
	tileId = 0;
	solid = 0;
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
