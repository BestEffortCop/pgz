#include <iostream>
#include "World.h"
#include "GenTypes.h"
#include "DBInterface.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

// Cosas que nos dara decidator:
//------------------------------------------------
int wSize = 2;
vector<ZoneInfo>* zonesI;
vector<DungeonInfo>* dungeonsI;
vector<SafeZoneInfo>* safeZonesI;
//------------------------------------------------

int main(int argc, char *argv[])
{
// Procesar argumentos...
/*
for(int i=1; i<argc; i++)
{
	cosa = argv[i];
}
*/
	DBInterface* myDB = new DBInterface();

	zonesI = new vector<ZoneInfo>();
	dungeonsI = new vector<DungeonInfo>();
	safeZonesI = new vector<SafeZoneInfo>();

	// Añadimos una zona de prueba
	ZoneInfo inf(1);
	ZoneInfo inf2(4);
	ZoneInfo inf3(2);
	zonesI->push_back(inf);
	zonesI->push_back(inf2);
	zonesI->push_back(inf3);

	int diff;

	if (argc > 2)
		diff = (int)argv[1];
	else
		diff = 1;

	srand(time(NULL));

	World* w = new World(diff);
	// TODO: poner algo en los ****Info <----
	Overworld* ow = new Overworld(wSize, zonesI, dungeonsI, safeZonesI);
	w->setOverworld(ow);

	GenOverworld* gow = new GenOverworld(ow);
	gow->genFrontiers();
	gow->genShape();
	gow->assignTilesScreens();
	gow->genGeoDetail();
	gow->genDecoration(myDB);
	gow->placeDungeons();
	gow->placeSafeZones();
	gow->genMainRoad();
	gow->genRoadRamifications();
	gow->genBlockades();
	gow->genScreens();
	gow->guardameSolids("solids.txt");
	gow->guardameZonas("Zones.txt");
	// TODO: terminar ...

	delete myDB;
	delete zonesI;
	delete dungeonsI;
	delete safeZonesI;
	delete gow;
	delete ow;
	delete w;

	//_CrtDumpMemoryLeaks();
	cin.peek();
	return 0;
}
