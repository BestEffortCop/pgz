#include "OwScreen.h"

/*OwScreen::OwScreen(int iniT, int screenW, Overworld* ow, int screenH){
	screenNumber = screenH;

	matrix = new vector<MapTile>();

    int iniTile = iniT;
	for (int i = 0; i< screenH; i++){
        iniTile = iniT + 16*screenW*i;
	    for (int j = 0; j< screenW; j++){
            matrix->push_back(ow->mapTileMatrix->at(j+iniTile));
	    }
	}
}*/


//Constructora en la que nos pasan la MapTileMatrix y tenemos que meter nosotros los tiles.
OwScreen::OwScreen(int init, int screensPerRow, vector<MapTile*>* mapMatrix, int screenN, vector<int>* enemies, vector<MapTile*>* details){

	matrix = new vector<MapTile*>();

	int iniTile;
	for (int i = 0; i < screenHeight; i++)
	{
		iniTile = init + screenWidth*screensPerRow*i;
		for (int j = 0; j < screenWidth; j++)
			matrix->push_back(mapMatrix->at(iniTile + j));
	}

    screenNumber = screenN;
	enemyList = enemies;
	detailsList = details;
}


OwScreen::~OwScreen(){		// BORRADO MIRAR MEJOR
	delete enemyList;
	delete detailsList;
	delete matrix;
	enemyList = NULL;
	detailsList = NULL;
	matrix = NULL;

}

void OwScreen::placeDetails(){
	cout << "Ejecutando función <OwScreen::placeDetails()>" << endl;
}

void OwScreen::placeEnemies(){
	cout << "Ejecutando función <OwScreen::placeEnemies()>" << endl;
}

string OwScreen::createScreenFiles(){
	cout << "Ejecutando función <OwScreen::createScreenFiles()> ya implementada" << endl;
	
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

