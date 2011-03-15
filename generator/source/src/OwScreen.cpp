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

OwScreen::OwScreen(int init, int screenW, int screenH, vector<MapTile>* mapMatrix, vector<MapTile>* tiles, int screenN, vector<MapTile>* enemies, vector<MapTile>* details){
	
	matrix = new vector<MapTile>();

	int iniTile;
	for (int i = 0; i < screenH; i++)
	{
		iniTile = init + 16*screenW*i;
		for (int j = 0; j < screenW; j++)
			matrix->push_back(mapMatrix->at(j+iniTile));
	}
	
    //matrix = tiles;			ECHAR UN OJO
    screenNumber = screenN;
	enemyList = enemies;
	detailsList = details;
}

OwScreen::~OwScreen(){		// BORRADO MIRAR MEJOR
	delete matrix;
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
	//Tengo que guardar:
	ofstream file;
	string path = "../../screens/screen";
	path += screenNumber;
	path += ".screen";
	file.open(path.c_str(), ios::binary);

	//Tile Inicial
	//file.write((char*)& iniTile, sizeof(int));
	//Tile Final
	//file.write((char*)& endTile, sizeof(int));
	//Número de Pantalla
	file.write((char*)& screenNumber, sizeof(int));

	//Tile por tile
	for (int i=0; i<matrix->size(); i++){
		MapTile tile = matrix->at(i);
		//TileId
		file.write((char*) tile.getTileId(), sizeof(int));
		//Solid
		file.write((char*) tile.getSolid(), sizeof(int));
		//ZoneNumber
		file.write((char*) tile.getZoneNumber(), sizeof(int));
		//Entidad
        //Type
        file.write((char*) tile.getEntity()->type, sizeof(type_t));
        //DungeonPath
        writeInFile(tile.getEntity()->dungeon_path, file);
        //Dest
        file.write((char*) tile.getEntity()->dest.first, sizeof(int));
        file.write((char*) tile.getEntity()->dest.second, sizeof(int));
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

