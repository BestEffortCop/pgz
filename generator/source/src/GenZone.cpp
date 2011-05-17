#include "GenZone.h"

GenZone::GenZone(string zone, int zoneNumber, short idTileSet, Overworld* ow, short numEnemies, short difficulty,
				 GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, Decorator* decorator, DBManager* myDB)
{
	this->idTileSet = idTileSet;
	this->zone = zone;

	this->zoneNumber = zoneNumber;
	this->numEnemies = numEnemies;

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