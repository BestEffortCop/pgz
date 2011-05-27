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
	cout<<"5#Generating World Frontiers\n";
	genOw->genFrontiers();
	cout<<"5#Subdividing World Space\n";
	genOw->genShape();
	cout<<"5#Generating World Zones Screens\n";
	genOw->assignTilesAndScreens();
	cout<<"5#Generating Geographical Detail\n";
	genOw->genGeoDetail();
	cout<<"5#Generating Dungeons\n";
	genOw->placeDungeons();
	cout<<"5#Generating Final Dungeon\n";
	genOw->placeFinalDungeon();
	cout<<"5#Placing Safe Zones\n";
	genOw->placeSafeZones();
	cout<<"5#Creating Main Road\n";
	genOw->genMainRoad();
	cout<<"5#Generating Road Ramifications\n";
	genOw->genRoadRamifications();
	cout<<"5#Placing Zone Blockades\n";
	genOw->genBlockades();
	cout<<"5#Placing Powerups and Pidgeons\n";
	genOw->placePowUPandPigeons();
	cout<<"5#Placing NPC's\n";
	genOw->placeNPCs();
	cout<<"5#Decorating World\n";
	genOw->genDecoration(myDB);
	cout<<"5#Saving Screens\n";
	genOw->genScreens();
	// Archivos debug:
	//genOw->guardameSolids("solids.txt");
	//genOw->guardameZonas("Zones.txt");
	//genOw->guardamePant("Pant.txt");
	//genOw->guardameAutotile("Auto.txt");
}