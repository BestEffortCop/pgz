#include "GenGame.h"

GenGame::GenGame(){}

void GenGame::genGame(DBManager* myDB){
	/* ---- Decidator obtiene los datos para los generadores ---- */
	// la GUI guardará el archivo que posteriormente leerá decidator para obtener la información
	decidator = new Decidator(myDB, "./input.dat");
	int wSize = 15;//decidator->getWorldSize();
	int numDungeons = decidator->getNumDungeons();
	/*
	int numZones = decidator->getNumZones();*/
	int numZones = 4;
	int diff = decidator->getDifficulty();
	int ratioDungeon = decidator->getRatio();
	int numSafeZones = decidator->getNumSafeZones();
	int numEnemies = decidator->getNumEnemies();

	/* Pedimos cosas a la DB */
	myDB->getPlayer();
	myDB->getKey();
	myDB->getBossKey();
	myDB->getDoors();

	zones = new vector<GenZone*>();

	//int numHearts = decidator->getInitialMaxLife();
	ow = new Overworld(wSize, diff, numZones, numDungeons, numSafeZones, 5, 50);
	GenDungeon* genDungeon = new GenDungeon();
	Decorator* decorator = new Decorator(myDB);
	int numDungeon = 1; 
	int idTool = 1;   //params para la dungeon
	vector<SafeZoneInfo>* safeZones = NULL;//new vector<SafeZoneInfo>();
	ZoneInfo zInfo;
	int zoneNumber = 1;
	string lastzone = "";
	while(zones->size() < numZones)
	{
		while(strcmp(zInfo.gen.c_str(),lastzone.c_str()) == 0)
			zInfo = myDB->getZone();
		if(strcmp(zInfo.gen.c_str(), "Forest") == 0)
		{
				GenZone* myGenZone = new GenForestZone(zInfo.gen, zoneNumber, zInfo.tileSetId, ow, numEnemies, genDungeon, /*numDungeon*/1, idTool, ratioDungeon, safeZones, decorator, myDB);
				zoneNumber++;
				zones->push_back(myGenZone);
		}
		else if(strcmp(zInfo.gen.c_str(), "Prairie") == 0)
		{
				GenZone* myGenZone = new GenFieldZone(zInfo.gen, zoneNumber, zInfo.tileSetId, ow, numEnemies, genDungeon, /*numDungeon*/1, idTool, ratioDungeon, safeZones, decorator, myDB);
				zoneNumber++;
				zones->push_back(myGenZone);
		}
		else if(strcmp(zInfo.gen.c_str(), "Lake") == 0)
		{
				//GenZone* myGenZone = new GenWormZone("theme-default", zoneTheme, zoneNumber, NULL, ow, numEnemies, genDungeon, /*numDungeon*/zoneNumber, idTool, ratioDungeon, safeZones, decorator, myDB);
				GenZone* myGenZone = new GenLagoonZone(zInfo.gen, zoneNumber, zInfo.tileSetId, ow, numEnemies, genDungeon, /*numDungeon*/1, idTool, ratioDungeon, safeZones, decorator, myDB);
				zoneNumber++;
				zones->push_back(myGenZone);
		}
		else if(strcmp(zInfo.gen.c_str(), "Desert") == 0)
		{
				//GenZone* myGenZone = new GenWormZone("theme-default", zoneTheme, zoneNumber, NULL, ow, numEnemies, genDungeon, /*numDungeon*/zoneNumber, idTool, ratioDungeon, safeZones, decorator, myDB);
				GenZone* myGenZone = new GenDesertZone(zInfo.gen, zoneNumber, zInfo.tileSetId, ow, numEnemies, genDungeon, /*numDungeon*/1, idTool, ratioDungeon, safeZones, decorator, myDB);
				zoneNumber++;
				zones->push_back(myGenZone);
		}
		lastzone = zInfo.gen;
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

GenGame::~GenGame(){

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
