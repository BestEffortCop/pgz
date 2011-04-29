#include "GenZone.h"

GenZone::GenZone(string theme, string zone, int zoneNumber, GPolygon* zoneShape, Overworld* ow, short numEnemies,
				 GenDungeon* genDungeon, short numDungeon, short idTool, short ratioDungeon, vector<SafeZoneInfo>* safeZones, Decorator* decorator, DBManager* myDB)
{
	shape = zoneShape;
	this->theme = theme;
	this->zone = zone;

	this->zoneNumber = zoneNumber;
	this->numEnemies = numEnemies;

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

// Devuelve el tipo de zona en forma de int.
string GenZone::getTheme(){
	return theme;
}

// Permite modificar el tipo asociado a una zona.
void GenZone::setTheme(string tId){
	theme = tId;
}

string GenZone::getZone()
{
	return zone;
}

// Devuelve el conjunto de puntos delimitador de zona.
GPolygon* GenZone::getShape(){
	return shape;
}

// Permite modificar el delimitador de zona.
void GenZone::setShape(GPolygon* s){
	shape = s;
}

short GenZone::getNumEnemies()
{
	return numEnemies;
}

MapTile* GenZone::inZone(GPoint pos){
	MapTile* mp = overworld->getMapTile(pos.x, pos.y);
	return mp;
}

int GenZone::getTileOfScreen(int& screenNumber){
	int screensPerRow = overworld->getWorldSizeW() / SCREEN_WIDTH;
	int tilesPerRow = overworld->getWorldSizeW();

	int startScreenN = screenList->at(rand() % screenList->size())->getScreenNumber();

	screenNumber = startScreenN;

	//coordenadas dentro de la matriz de screens de startScreenN
	int screenX = startScreenN % screensPerRow;
	int screenY = startScreenN / screensPerRow;

	// coordenada X e Y del tile incial de pantalla
	int tileY = screenY * SCREEN_HEIGHT;
	int tileX = screenX * SCREEN_WIDTH;
	
	// el tile dentro del mapa de tiles grande.
	int iniTile = (tileY * tilesPerRow) + tileX;

	int add = rand() % SCREEN_WIDTH*SCREEN_HEIGHT;

	iniTile += add % SCREEN_WIDTH;
	iniTile += (add / SCREEN_HEIGHT)*overworld->getWorldSizeW();

	return iniTile;
}

bool GenZone::isFrontierNear(int iniT, int range){

	int iniTile = iniT - range - (range*overworld->getWorldSizeW());
	if (iniTile < 0) 
		return true;

	bool frontierFound = false;
	int tile = 0;
	for (int i = 0; i < (range*2+1); i++){
		tile = iniTile + i*overworld->getWorldSizeW();
		for (int j = 0; j < (range*2+1); j++){
			if ( !frontierFound) 
				if (tile >= overworld->mapTileMatrix->size() || overworld->mapTileMatrix->at(tile)->getSolid() == 4
					|| overworld->mapTileMatrix->at(tile)->getZoneNumber() != overworld->mapTileMatrix->at(iniT)->getZoneNumber() )
					frontierFound = true;
			tile++;
		}	
	}

	if (frontierFound)
		return true;
	else
		return false;

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