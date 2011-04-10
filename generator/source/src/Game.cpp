#include "Game.h"

Game::Game(){}

void Game::genGame(int diff, int wSize, int numZones, int numDungeons, int numSafeZones, DBManager* myDB){

	zones = new vector<GenZone*>();
	ow = new Overworld(wSize, diff, numZones, numDungeons, numSafeZones);
	GenDungeon* genDungeon = new GenDungeon();
	int numDungeon = 1; int idTool = 1; int ratioDungeon = 50;  //params para la dungeon
	int numEnemies = 3;  // 3 es el número de enemigos. Debería depender de dificultad
	vector<SafeZoneInfo>* safeZones = NULL;//new vector<SafeZoneInfo>();
	for (int zoneNumber = 1; zoneNumber <= numZones; zoneNumber++)
	{
		GenZone* myGenZone = new GenWormZone("theme-default", "zone-default", zoneNumber, NULL, ow, numEnemies, genDungeon, /*numDungeon*/zoneNumber, idTool, ratioDungeon, safeZones, myDB);
		zones->push_back(myGenZone);
	}
	
	// Aquí debiera de ir un Case para seleccionar el tipo de generador
	// segun indique Decidator
	genOw = new GenVoroWorld(ow, zones, myDB);
	world = new World(diff, genOw, myDB);

	world->buildOverworld();
	ow->save(); //ahora aquí se hace el guardado
	for(int i = 0; i < genDungeon->getNumDungeons(); i++) //guardamos todas las dungeons
		genDungeon->getDungeon(i)->save();

	delete genDungeon; 
	genDungeon = NULL;
}

Game::~Game(){

	vector<GenZone*>::iterator it;
    for(it = zones->begin(); it != zones->end(); it++)
        if ((*it) != NULL)
        {
			delete (*it);
			(*it) = NULL;
        }
	delete zones;
	zones = NULL;
	
	delete ow;			// SOLO LO BORRA ESTE PORQUE ES EL CLIENTE DICTADOR
	ow = NULL;

	delete genOw;		// Así nos aseguramos que llama al delete del GenVoronoiOW
	genOw = NULL;

	delete world; 
	world = NULL;
}
