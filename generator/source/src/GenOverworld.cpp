#include "GenOverworld.h"

GenOverworld::GenOverworld(Overworld* overworld)
{
	this->overworld = overworld;
	zones = new vector<Zone*>();
	blockadeVerts = new vector<set<GPoint> >();
	mainRoadVerts = new vector<GPoint>();
	interestingPoints = new vector<GPoint>();
}

GenOverworld::~GenOverworld()
{
	overworld = NULL;	// Se encargará de destruirlo el que lo crea

	vector<Zone*>::iterator it;
    for(it = zones->begin(); it != zones->end(); it++)
        if ((*it) != NULL)
        {
			delete (*it);
			(*it) = NULL;
        }
	delete zones;
	zones = NULL;

	delete blockadeVerts;
	blockadeVerts = NULL;
	
	delete mainRoadVerts;
	mainRoadVerts = NULL;

	delete interestingPoints;
	interestingPoints = NULL;
}

void GenOverworld::genFrontiers(){
	// TODO esto lo recibiremos de Decidator

	for ( unsigned int i = 0; i<overworld->getNumZones(); i++){
		Zone* z = new Zone(overworld->getZonesInfo()->at(i).themeId, NULL, overworld->mapTileMatrix);
		/**********************añado para debug ***************************/
		z->setZoneNumber(overworld->getZonesInfo()->at(i).themeId);
		zones->push_back(z);
	}

	cout << "Ejecutando funcion <GenOverworld::genFrontiers()>" << endl;
}

void GenOverworld::genShape(){
	cout << "Ejecutando funcion <GenOverworld::genShape()>" << endl;
}

void GenOverworld::assignTilesScreens(){
	cout << "Ejecutando funcion <GenOverworld::assignTilesScreens()>" << endl;

	int screensPerCol = overworld->getWorldSizeH() / screenHeight;
	int screensPerRow = overworld->getWorldSizeW() / screenWidth;

	int screenNumber = 0;
    int iniTileRow;
    int iniTile;

    for (int row = 0; row < screensPerCol; row++){
        iniTileRow = screenWidth*screenHeight*screenNumber;
        for (int col = 0; col < screensPerRow; col++){
            iniTile = col*screenWidth + iniTileRow;
			OwScreen* screen = makeNewScreen(iniTile,screenNumber);
			zones->at(screen->zoneId)->addScreen(screen);
			screenNumber++;
        }
    }
}

OwScreen* GenOverworld::makeNewScreen(int iniT, int screenNumber){
	int screensPerRow = overworld->getWorldSizeW() / screenWidth;
	int iniTile;
	MapTile* t;
	int zoneNum;
	int* candidates = new int[overworld->getNumZones()];
	for (int i=0; i<overworld->getNumZones(); i++) {
		candidates[i] = 0;
	}

	vector<MapTile*>* screenMatrix = new vector<MapTile*>();

	for (int i = 0; i < screenHeight; i++)
	{
		iniTile = iniT + screenWidth*screensPerRow*i;
		for (int j = 0; j < screenWidth; j++){
			t = overworld->mapTileMatrix->at(iniTile + j); // pillamos el mapTile que toque
			zoneNum = checkTileinZone(t); // este nos dice en que zona esta el mapTile
			t->setZoneNumber(zoneNum); // se lo ponemos al mapTile
			candidates[zoneNum]++; // incrementamos el numero de tiles de una zona dentro de una pantalla
			screenMatrix->push_back(overworld->mapTileMatrix->at(iniTile + j));
		}
	}

	int maxNumber = 0;
	int maxPosition = 0;
	for ( int i = 0; i<overworld->getNumZones(); i++){
		if ( candidates[i] > maxNumber ){
			maxNumber = candidates[i];
			maxPosition = i;
		}
	}

	/******************************comento esto************************/
	//delete candidates;
	//candidates = NULL;

	return new OwScreen(screenNumber, screenMatrix, maxPosition);
}

//Devuelve el número de la zona en el q está el tile
int GenOverworld::checkTileinZone(MapTile* mTile){
	return 1;//(rand() % 3);
	//return 0;
}

void GenOverworld::genGeoDetail(){
	cout << "Ejecutando funcion <GenOverworld::genGeoDetail()>" << endl;

	for (unsigned int i = 0; i<zones->size(); i++){
		Zone* zone = zones->at(i);
		zone->genGeoDetail( overworld->getWorldSizeW() / screenWidth);
	}


}

void GenOverworld::genDecoration(DBInterface* myDB)
{
    // Esto se cambiará en un futuro, de momento es para meter porqueria en la matriz
	vector<int>* candidatos = myDB->getTiles(1);
	int aux;

	for (unsigned int i = 0; i < overworld->mapTileMatrix->size(); i++)
	{
		aux = rand() % 3;
		overworld->mapTileMatrix->at(i)->setTileId(candidatos->at(aux));
	}
	delete candidatos;
	candidatos = NULL;
}

void GenOverworld::placeDungeons(){
	cout << "Ejecutando funcion <GenOverworld::placeDungeons()>" << endl;
}

void GenOverworld::placeSafeZones(){
	cout << "Ejecutando funcion <GenOverworld::placeSafeZones()>" << endl;
}

void GenOverworld::genMainRoad(){
	cout << "Ejecutando funcion <GenOverworld::genMainRoad()>" << endl;
}

void GenOverworld::genRoadRamifications(){
	cout << "Ejecutando funcion <GenOverworld::genRoadRamifications()>" << endl;
}

void GenOverworld::genBlockades(){
	cout << "Ejecutando funcion <GenOverworld::genBlockades()>" << endl;
}

//Generar un screen para cada Zona
void GenOverworld::genScreens(){
	for (unsigned int i = 0; i < zones->size(); i++){
		Zone* zone = zones->at(i);
		zone->genScreens();
	}

    //DE COÑA
	cout<< overworld->mapTileMatrix->size() << " tiles de mapa" << endl;
}

/*******************************FUNCIONES AÑADIDAS PARA DEBUG*********************************************/
//DE COÑA
void GenOverworld::guardameSolids(string path){

	string fichero (path);
	ofstream f_lista (fichero.c_str());
	if (!f_lista) {
		cout << "El fichero " << fichero << " no existe.";
		exit (0);
	}

	for(int i = 0; i < overworld->getWorldSizeH()*overworld->getWorldSizeW(); i++){
		if( overworld->mapTileMatrix->at(i)->getSolid() == 0)
			f_lista << "·" << " ";
		else
			f_lista << "0" << " ";
		if((i+1) % overworld->getWorldSizeW() == 0)
			f_lista << endl;
	}

	f_lista.close();
}

//DE COÑA
void GenOverworld::guardameZonas(string path){

	string fichero (path);
	ofstream f_lista (fichero.c_str());
	if (!f_lista) {
		cout << "El fichero " << fichero << " no existe.";
		exit (0);
	}

	for(int i = 0; i < overworld->getWorldSizeH()*overworld->getWorldSizeW(); i++){
		f_lista << overworld->mapTileMatrix->at(i)->getZoneNumber() << " ";
		if((i+1) % overworld->getWorldSizeW() == 0)
			f_lista << endl;
	}

	f_lista.close();
}

