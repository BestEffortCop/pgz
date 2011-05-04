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

bool OwScreen::contains(int elem, vector<int>* collect){
	for (int i = 0; i < collect->size(); i++)
		if (collect->at(i) == elem)
			return true;

	return false;
}

bool OwScreen::isThereAnyEntityAt(vector<Entity*>* entities, int pos){
	for (int i = 0; i < entities->size(); i++)
		if (pos == entities->at(i)->x + (entities->at(i)->y*SCREEN_WIDTH)) return true;

	return false;
}

void OwScreen::placeEnemies()
{
	//cout << "Ejecutando funcion <OwScreen::placeEnemies()>" << endl;

	int pos = 0;
	enemy myEnemy;
	int Nenemies = n_enemies;		// Número de enemigos de un mismo tipo de enemigos
	int idEnemy = 0;
	vector<int>* enemiesUsed = new vector<int>();
	vector<int>* posUsed = new vector<int>();

	while ( enemies->size() != n_enemies ){
		// Elegimos el número de enemigos que colocaremos de un tipo asegurándonos que pongamos por lo menos uno
		Nenemies = rand() % (n_enemies - enemies->size()) + 1;

		// Cogemos el id del enemigo
		idEnemy = db->getEnemy(zone);
		//while(contains(idEnemy, enemiesUsed))
			//idEnemy = db->getEnemy(zone);
		enemiesUsed->push_back(idEnemy);
		
		// Colocamos el numero de enemigos calculado en enemies con identificador idEnemie por la pantalla
		for (int j = 0; j < Nenemies; j++){
			// Calculamos una posición random libre (sin entidades ni solidos)
			int posFirst;
			do
				posFirst = rand() % matrix->size();
			while ( contains(posFirst,posUsed)); // Se busca una posición sin enemigo

			if ((matrix->at(posFirst)->getSolid() == 0 || matrix->at(posFirst)->getSolid() == 3) && (!isThereAnyEntityAt(entities, posFirst)))
				pos = posFirst;
			else
				while ((pos != posFirst) && (!(matrix->at((pos + 1)%matrix->size())->getSolid() == 0 || matrix->at((pos + 1)%matrix->size())->getSolid() == 3) && (!isThereAnyEntityAt(entities, (pos + 1)%matrix->size()))) && !contains((pos + 1)%matrix->size(),posUsed))
					pos = (pos + 1) % matrix->size();

			// Creamos el enemigo y fijamos sus atributos
			myEnemy.id = idEnemy;
			myEnemy.posX = pos % SCREEN_WIDTH;
			myEnemy.posY = pos / SCREEN_WIDTH;
			// Añadimos el enemigo a la lista de los mismos
			enemies->push_back(myEnemy);
		}
	}

	delete enemiesUsed;
	enemiesUsed = NULL;
	delete posUsed;
	posUsed = NULL;
}

int OwScreen::getScreenNumber(){
	return screenNumber;
}

void OwScreen::generate()
{
	int x, y;

	//volcamos nuestra info de los tiles en la clase padre
	for (int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++){
		x = i % SCREEN_WIDTH;
		y = i / SCREEN_WIDTH;
		//!!!!!!!!!!!!!!!!!!!!! CUIDADO!!  Cableado para que salgo algo bonito, cuando se termine decorator ha de descomentarse y borrar la siguiente !!!!!!!!!!!!!!!!!!!!!!!!!!!!!>
		//tiles[x][y] = matrix->at(i)->getTileId();
		//tiles[x][y] = matrix->at(i)->getSolid();
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

short OwScreen::getSolid(int x, int y)
{
	int pos;
	pos = (y * SCREEN_WIDTH) + x;
	if(pos < matrix->size())
		return matrix->at(pos)->getSolid();
	else
		return -1;
}

short OwScreen::getSolid(int pos)
{
	if(pos < matrix->size())
		return matrix->at(pos)->getSolid();
	else return -1;
}

void OwScreen::setSolid(int pos, short solid)
{
	if(pos < matrix->size())
		matrix->at(pos)->setSolid(solid);
}

void OwScreen::setSolid(int x, int y, short solid)
{
	int pos;
	pos = (y * SCREEN_WIDTH) + x;
	if(pos < matrix->size())
		matrix->at(pos)->setSolid(solid);
}