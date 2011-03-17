#include "OwScreen.h"

//Constructora en la que nos pasan la MapTileMatrix y tenemos que meter nosotros los tiles.

OwScreen::OwScreen(int screenN, vector<MapTile*>* screenMatrix, int zoneNum){
	screenNumber = screenN;
	matrix = screenMatrix;
	zoneId = zoneNum;
	enemyList = NULL;
	detailsList = NULL;
}

OwScreen::~OwScreen(){
	delete enemyList;
	delete detailsList;
	delete matrix;
	enemyList = NULL;
	detailsList = NULL;
	matrix = NULL;
}

void OwScreen::placeDetails(){
	cout << "Ejecutando funcion <OwScreen::placeDetails()>" << endl;
}

void OwScreen::placeEnemies(){
	cout << "Ejecutando funcion <OwScreen::placeEnemies()>" << endl;
}

string OwScreen::createScreenFiles(){
	cout << "Ejecutando funcion <OwScreen::createScreenFiles()> ya implementada" << endl;
	
	ofstream file;
	char auxstr[20];
	string path = "../screens/screen";
	_itoa_s(screenNumber,auxstr,10);
	path += auxstr;
	path += ".screen";
	
	file.open(path.c_str(), ios::binary | ios::trunc);

	if (file.is_open())
		cout << "Archivo abierto correctamente" <<endl;
	else
		cout << "Archivo abierto incorrectamente" <<endl;

	//Número de Pantalla
	file.write((char*)& screenNumber, sizeof(int));

	//Tipo de zona
	file.write((char*)& zoneId,sizeof(int));

	 //Tile por tile
	for (unsigned int i=0; i<matrix->size(); i++){
		MapTile* tile = matrix->at(i);
		//TileId
		int aux = tile->getTileId();
		file.write((char*)& aux, sizeof(int));
		//Solid
		aux = tile->getSolid();
		file.write((char*)& aux, sizeof(int));
		//ZoneNumber
		aux = tile->getZoneNumber();
		file.write((char*)& aux, sizeof(int));
		//Entidad
			//Type
			file.write((char*)& tile->getEntity()->type, sizeof(EntType));
			//DungeonPath
			writeInFile(tile->getEntity()->dungeonPath, file);
			//Dest
			file.write((char*)& tile->getEntity()->dest.x, sizeof(int));
			file.write((char*)& tile->getEntity()->dest.y, sizeof(int));
		//Se guarda la lista de enemigos
		if (enemyList != NULL){
			for (unsigned int i = 0; i<enemyList->size(); i++){
				int aux = enemyList->at(i);
				file.write((char*)& aux, sizeof(int));
			}
		}
	}

	if (file.good())
		cout << "Archivo guardado correctamente" <<endl;
	else
		cout << "Archivo incorrectamente guardado" <<endl;

	file.close();

	return path;
}

void OwScreen::writeInFile(const string& cad, ofstream& sal)const{
    int size = cad.size();
    sal.write((char*)& size, sizeof(int));
    sal.write((char*) cad.data(), sizeof(char) * cad.size());
}

void OwScreen::setEnemyList(vector<int>* lEnemy){
	enemyList = lEnemy;
}

void OwScreen::setDetailsList(vector<MapTile*>* lDetail){
	detailsList = lDetail;
}
