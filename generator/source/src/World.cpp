#include "World.h"

// Constructora
World::World(int difficulty, GenOverworld* genOverw, DBManager* myDataB){
	// Asignamos dificultad
	gameDiff = difficulty;
	genOw = genOverw;
	myDB = myDataB;			// AÑADIDO DB PARA INVOCACION DE GENDECORATION
}

// Destructora
World::~World(){
	overworld = NULL;
	genOw = NULL;
	myDB = NULL;
}

// Setter Overworld
void World::setOverworld(Overworld* ow){
	overworld = ow;
}

// Construcción del overworld
void World::buildOverworld(){
	genOw->genFrontiers();
	genOw->genShape();
	genOw->assignTilesAndScreens();
	genOw->genGeoDetail();
	genOw->placeDungeons();
	genOw->placeSafeZones();
	genOw->genMainRoad();
	genOw->genRoadRamifications();
	genOw->genBlockades();
	genOw->genDecoration(myDB);
	genOw->genScreens();	
	genOw->guardameSolids("solids.txt");
	genOw->guardameZonas("Zones.txt");
	genOw->guardamePant("Pant.txt");
}