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

#include "GenZone.h"

GenZone::GenZone(string zone, int zoneNumber, short idTileSet, Overworld* ow, short numEnemies, short difficulty,
				 GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, Decorator* decorator, DBManager* myDB, short keyObj)
{
	this->idTileSet = idTileSet;
	this->zone = zone;
	this->keyObj = keyObj;

	this->zoneNumber = zoneNumber;
	this->numEnemies = numEnemies+(zoneNumber/2);

	gameDifficulty = difficulty;

	this->overworld = ow;
	screenList = new vector<OwScreen*>();
	this->safeZones = safeZones;

	dungEntranceTile = -1;

	this->genDungeon = genDungeon;
	this->numDungeon = numDungeon;
	this->idTool = idTool;
	this->ratioDungeon = ratioDungeon;

	this->decorator = decorator;

	this->myDB = myDB;
}

GenZone::~GenZone()
{
	delete screenList; 
	screenList = NULL;
	
	safeZones = NULL;
	overworld = NULL;
}

// Setters & Getters

string GenZone::getZone()
{
	return zone;
}

short GenZone::getNumEnemies()
{
	return numEnemies;
}

MapTile* GenZone::inZone(GPoint pos){
	MapTile* mp = overworld->getMapTile(pos.x, pos.y);
	return mp;
}




// Devuelve el número de orden de la mazmorra que se encuentra en la zona
int GenZone::getNumDungeon(){
	return numDungeon;
}

// Establece un nuevo número de orden de la mazmorra de la zona
void GenZone::setNumDungeon(int dunNum){
	numDungeon = dunNum;
}

void GenZone::addScreen(OwScreen* ows){
	screenList->push_back(ows);
}

int GenZone::getNumScreens(){
	if (screenList != NULL)
		return screenList->size();
	return 0;
}

int GenZone::getDungEntranceTile(){
	return dungEntranceTile;
}

int GenZone::getZoneNumber(){
	return zoneNumber;
}