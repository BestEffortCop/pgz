#include <iostream>
#include "Game.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Cosas que nos dara decidator:
//------------------------------------------------
int wSize = 2;
//vector<ZoneInfo>* zonesI;
//vector<DungeonInfo>* dungeonsI;
//vector<SafeZoneInfo>* safeZonesI;

// Cosas Chendo:
int numZones = 5;
int numDungeons = 5;
int numSafeZones = 1;
int diff = 1;
DBManager* myDB = new DBManager();
//vector<pair<int,int>> themeIdZones;			// Será el vector que contiene el tema y el número de zona de la misma

//------------------------------------------------

int main(int argc, char *argv[])
{
	srand(time(NULL));
	clock_t t1 = clock();
	Game* myGame = new Game();
	myGame->genGame(diff, wSize, numZones, numDungeons, numSafeZones, myDB);

	delete myDB;
	delete myGame;
	
	clock_t t2 = clock();
	cout<<"Tiempo empleado: " << double(t2-t1)/CLOCKS_PER_SEC<<" segundos."<<endl;

	cin.peek();
	_CrtDumpMemoryLeaks();	

	return 0;
}
