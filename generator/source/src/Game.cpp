#include "Game.h"

Game::Game(){}

void Game::genGame(int diff, int wSize, int numZones, int numDungeons, int numSafeZones, DBManager* myDB){

	zonesI = new vector<ZoneInfo*>();
	ow = new Overworld(wSize, diff, numZones, numDungeons, numSafeZones);

	ZoneInfo* zone; 
	for (int zoneNumber = 1; zoneNumber <= numZones; zoneNumber++){
		// Esto en un futuro tendra un MEGACASE para diferenciar los tipos de generadores a usar que nos dirá Decidator (ENTE MARAVILLOSO)
		GenZone* myZone = new GenWormZone("theme-default", "zone-default", zoneNumber, NULL, ow); // zoneNumber + 10 = themeId (en un futuro proximo)
		vector<DungeonInfo>* dungeons = NULL;//new vector<DungeonInfo>();
		vector<SafeZoneInfo>* safeZones = NULL;//new vector<SafeZoneInfo>();
		zone = new ZoneInfo("theme-default", "zone-default", zoneNumber, myZone, dungeons, safeZones, 3);	// 3 es el número de enemigos. Debería depender de dificultad
		zonesI->push_back(zone);
	}
	
	// Aquí debiera de ir un Case para seleccionar el tipo de generador
	// segun indique Decidator
	genOw = new GenVoroWorld(ow, zonesI, myDB);
	world = new World(diff, genOw, myDB);

	world->buildOverworld();
	ow->save(); //ahora aquí se hace el guardado
}

Game::~Game(){

	vector<ZoneInfo*>::iterator it;
    for(it = zonesI->begin(); it != zonesI->end(); it++)
        if ((*it) != NULL)
        {
			delete (*it);
			(*it) = NULL;
        }
	delete zonesI;
	zonesI = NULL;
	
	delete ow;			// SOLO LO BORRA ESTE PORQUE ES EL CLIENTE DICTADOR
	ow = NULL;

	delete genOw;		// Así nos aseguramos que llama al delete del GenVoronoiOW
	genOw = NULL;

	delete world; 
	world = NULL;
}
