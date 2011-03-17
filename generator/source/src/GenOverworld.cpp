#include "GenOverworld.h"

GenOverworld::GenOverworld(Overworld* overworld)
{
	this->overworld = overworld;
	zones = new vector<Zone*>();
	blockadeVerts = new vector<set<Point> >();
	mainRoadVerts = new vector<Point>();
	interestingPoints = new vector<Point>();
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

	if (blockadeVerts != NULL)
	{
		blockadeVerts->clear();
		delete blockadeVerts;
		blockadeVerts = NULL;
	}

	if (mainRoadVerts != NULL)
	{
		mainRoadVerts->clear();
		delete mainRoadVerts;
		mainRoadVerts = NULL;
	}

	if (interestingPoints != NULL)
	{
		interestingPoints->clear();
		delete interestingPoints;
		interestingPoints = NULL;
	}
}

void GenOverworld::genFrontiers(){
	// TODO esto lo recibiremos de Decidator
	Zone *z = new Zone(1, NULL, overworld->mapTileMatrix);
	zones->push_back(z);

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

	delete candidates;
	candidates = NULL;

	return new OwScreen(screenNumber, screenMatrix, maxPosition);	
}

int GenOverworld::checkTileinZone(MapTile* mTile){
	// TODO cuando tengamos division de zonas
	return 0;
}

void GenOverworld::genGeoDetail(){
	cout << "Ejecutando funcion <GenOverworld::genGeoDetail()>" << endl;
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
}
