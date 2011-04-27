#include "Game.h"

Game::Game(){}

void Game::genGame(DBManager* myDB){
	/* ---- Decidator obtiene los datos para los generadores ---- */
	// la GUI guardará el archivo que posteriormente leerá decidator para obtener la información
	decidator = new Decidator(myDB, "./file.txt");
	int wSize = decidator->getWorldSize();
	int numDungeons = decidator->getNumDungeons();
	int numZones = decidator->getNumZones();
	int diff = decidator->getDifficulty();
	int ratioDungeon = decidator->getRatio();
	int numSafeZones = decidator->getNumSafeZones();
	int numEnemies = decidator->getNumEnemies();

	zones = new vector<GenZone*>();
	ow = new Overworld(wSize, diff, numZones, numDungeons, numSafeZones);
	GenDungeon* genDungeon = new GenDungeon();
	Decorator* decorator = new Decorator();
	int numDungeon = 1; 
	int idTool = 1;   //params para la dungeon
	vector<SafeZoneInfo>* safeZones = NULL;//new vector<SafeZoneInfo>();
	string zoneTheme;
	for (int zoneNumber = 1; zoneNumber <= numZones; zoneNumber++)
	{
		switch(zoneNumber){ //esto lo haría decidator pero no hay tiempo de pensar ahora o.O!
		case 1:{
				zoneTheme = "Forest";
				GenZone* myGenZone = new GenForestZone("theme-default", zoneTheme, zoneNumber, NULL, ow, numEnemies, genDungeon, /*numDungeon*/zoneNumber, idTool, ratioDungeon, safeZones, myDB);
				zones->push_back(myGenZone);
			break;}
		case 2:{
				zoneTheme = "Field";
				GenZone* myGenZone = new GenFieldZone("theme-default", zoneTheme, zoneNumber, NULL, ow, numEnemies, genDungeon, /*numDungeon*/zoneNumber, idTool, ratioDungeon, safeZones, myDB);
				zones->push_back(myGenZone);
			break;}
		case 3:{
				zoneTheme = "Swamp";  //pantano
				GenZone* myGenZone = new GenWormZone("theme-default", zoneTheme, zoneNumber, NULL, ow, numEnemies, genDungeon, /*numDungeon*/zoneNumber, idTool, ratioDungeon, safeZones, myDB);
				zones->push_back(myGenZone);
			break;}
		default:{
				zoneTheme = "Desert";  
				GenZone* myGenZone = new GenWormZone("theme-default", zoneTheme, zoneNumber, NULL, ow, numEnemies, genDungeon, /*numDungeon*/zoneNumber, idTool, ratioDungeon, safeZones, myDB);
				zones->push_back(myGenZone);
			break;}
		}
	}
	
	// Decidator obtiene de la base de dator el generador de mundo a utilizar
	/*switch (decidator->getWorldGen()){   Lo comento de momento porque la consulta no devuelve na y estalla esto x.x
	case 1:
		genOw = new GenVoroWorld(ow, zones, myDB);	
		break;
	}*/
	genOw = new GenVoroWorld(ow, zones, myDB);	

	world = new World(diff, genOw, myDB);

	world->buildOverworld();
	ow->save(); //ahora aquí se hace el guardado
	for (int i = 0; i < genDungeon->getNumDungeons(); i++) //guardamos todas las dungeons
		genDungeon->getDungeon(i)->save();

	// Decidator guarda la información que necesita el intérprete (como número de piezas de corazón, etc...)
	decidator->save();

	delete genDungeon; 
	genDungeon = NULL;

	delete decorator;
	decorator = NULL;
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

	delete decidator;
	decidator = NULL;
}
