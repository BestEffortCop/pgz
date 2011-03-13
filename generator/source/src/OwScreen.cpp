#include "OwScreen.h"

OwScreen::OwScreen(ZoneInfo zonesInfo, int iniT, int screensW, Overworld* ow, int screenN){
	*infozone = zonesInfo;
	screenNumber = screenN;

	matrix = new vector<MapTile>();

    int iniTile = iniT;
	for (int i = 0; i< screenH; i++){
        iniTile = iniT + 16*screensW*i;
	    for (int j = 0; j< screenW; j++){
            matrix->push_back(ow->mapTileMatrix->at(j+iniTile));
	    }
	}
}

OwScreen::OwScreen(ZoneInfo zonesInfo, vector<MapTile>* tiles, int screenN){
    *infoZone = zonesInfo;
    matrix = tiles;
    screenNumber = screenN;

}

OwScreen::~OwScreen(){
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
	file.write((char*)& iniTile, sizeof(int));
	//Tile Final
	file.write((char*)& endTile, sizeof(int));
	//Número de Pantalla
	file.write((char*)& screenNumber, sizeof(int));

	//Tile por tile
	for (int i=0; i<matrix->size(); i++){
		MapTile tile = matrix->at(i);
		//Type
		file.write((char*)& tile.getType(), sizeof(int));
		//Solid
		file.write((char*)& tile.getSolid(), sizeof(int));
		//ZoneNumber
		file.write((char*)& tile.getZoneNumber(), sizeof(int));
		//Entidad
        //Type
        file.write((char*)& tile.getEntity()->type, sizeof(type_t));
        //DungeonPath
        writeInFile(tile.getEntity()->dungeon_path, file);
        //Dest
        file.write((char*)& tile.getEntity()->dest.first, sizeof(int));
        file.write((char*)& tile.getEntity()->dest.second, sizeof(int));
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

