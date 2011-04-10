#include "OwScreen.h"

//Constructora en la que nos pasan la MapTileMatrix y tenemos que meter nosotros los tiles.

OwScreen::OwScreen(short mapNumber, int screenN, vector<MapTile*>* screenMatrix, int zoneNum, short posX, short posY, short n_enemies, string zone, string theme, DBManager * db)
	: Screen(mapNumber, posX, posY, n_enemies, zone, theme, db){
	screenNumber = screenN;
	matrix = screenMatrix;
	this->zoneNum = zoneNum;
}

OwScreen::~OwScreen()
{
	delete matrix; //esto no borra los MapTile que contiene.
	matrix = NULL;
}

void OwScreen::placeDetails()
{
	//cout << "Ejecutando funcion <OwScreen::placeDetails()>" << endl;
}

void OwScreen::placeEnemies()
{
	//cout << "Ejecutando funcion <OwScreen::placeEnemies()>" << endl;
}

int OwScreen::getScreenNumber()
{
	return screenNumber;
}

void OwScreen::generate()
{
	int x, y;

	//volcamos nuestra info de los tiles en la clase padre
	for (int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++){
		x = i % SCREEN_WIDTH;
		y = i / SCREEN_WIDTH;
		tiles[x][y] = matrix->at(i)->getTileId();
		solids[x][y] = matrix->at(i)->getSolid();
	}

}
//getters & setters

vector<MapTile*>* OwScreen::getMatrix()
{
	return matrix;
}

int OwScreen::getZoneNum()
{
	return zoneNum;
}