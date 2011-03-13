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

void GenOverworld::genDecoration(BDInterface myDB)
{
	// Esto se cambiará en un futuro, de momento es para meter porqueria en la matriz
	vector<int>* candidatos = myDB.getTiles(1);
	int aux;
	srand ( time(NULL) );

	for (int i = 0; i < overworld->mapTileMatrix->size(); i++)
	{
		aux = rand() % 3;
		overworld->mapTileMatrix->at(i).setTileId(candidatos->at(aux));
	}
}