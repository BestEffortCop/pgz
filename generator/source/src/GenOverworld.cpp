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
	cout << "Ejecutando función <GenOverworld::genFrontiers()>" << endl;
}

void GenOverworld::genShape(){
	cout << "Ejecutando función <GenOverworld::genShape()>" << endl;
}

void GenOverworld::genGeoDetail(){
	cout << "Ejecutando función <GenOverworld::genGeoDetail()>" << endl;
}

void GenOverworld::genDecoration(BDInterface* myDB)
{
    // Esto se cambiará en un futuro, de momento es para meter porqueria en la matriz
	vector<int>* candidatos = myDB->getTiles(1);
	int aux;
	srand ( time(NULL) );

	for (unsigned int i = 0; i < overworld->mapTileMatrix->size(); i++)
	{
		aux = rand() % 3;
		overworld->mapTileMatrix->at(i).setTileId(candidatos->at(aux));
	}
}

void GenOverworld::placeDungeons(){
	cout << "Ejecutando función <GenOverworld::placeDungeons()>" << endl;
}

void GenOverworld::placeSafeZones(){
	cout << "Ejecutando función <GenOverworld::placeSafeZones()>" << endl;
}

void GenOverworld::genMainRoad(){
	cout << "Ejecutando función <GenOverworld::genMainRoad()>" << endl;
}

void GenOverworld::genRoadRamifications(){
	cout << "Ejecutando función <GenOverworld::genRoadRamifications()>" << endl;
}

void GenOverworld::genBlockades(){
	cout << "Ejecutando función <GenOverworld::genBlockades()>" << endl;
}

//Generar un screen para cada Zona
void GenOverworld::genScreens(){
	//Esto se puede hacer con Iterators, pero no sé hacerlo
	for (unsigned int i = 0; i < zones->size(); i++){
		Zone* zone = zones->at(i);
		zone->genScreens();
	}
}
