#include <iostream.h>
#include "World.h"
#include "GenTypes"

// Cosas que nos dara decidator:
//------------------------------------------------
int wSize = 5;
vector<ZoneInfo> zonesI;
vector<DungeonInfo> dungeonsI;
vector<SafeZoneInfo> safeZonesI;
//------------------------------------------------

main(int argc, char *argv[])
{
// Procesar argumentos...
/* 
for(int i=1; i<argc; i++)
{
	cosa = argv[i];
}
*/
	int diff;
	
	if (argc > 2)
		diff = argv[1];
	else 
		diff = 1;
		
	World* w = new World(diff);
	// TODO: poner algo en los ****Info <----
	Overworld* ow = new Overworld(int wSize, vector<ZoneInfo> zonesI, vector<DungeonInfo> dungeonsI, vector<SafeZoneInfo> safeZonesI);
	w->setOverworld(ow);
	
	GenOverworld* gow = new GenOverworld(ow);
	gow->genFrontiers();
	gow->genShape();
	gow->genGeoDetail();
	gow->genDecoration(BDInterface myDB);
	gow->placeDungeons();
	gow->placeSafeZones();
	gow->genMainRoad();
	gow->genRoadRamifications();
	gow->genBlockades();
	
	gow->genScreens(); // deberia llamar a un genScreens de Zone por cada zona que tenga
	
	// TODO: terminar ...

	return 0;
}
