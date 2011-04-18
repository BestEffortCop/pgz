#pragma once

#ifndef _DUNGEONJ_H_
#define _DUNGEONJ_H_

#include "Dungeon.h"
#include "DunScreen.h"
#include <vector>
#include "IGraphControl.h"
#include "DBManager.h"

#define ENTRANCE 0
#define PUZZLE 1
#define MINIBOSS 2
#define COLLECTABLE 3
#define BOSS 4
#define BOSSS_KEY 5
#define ENEMY_NUMBER 16
#define DIST(x1,y1,x2,y2) std::abs(x1-x2) + std::abs(y1-y2)
using namespace std;

// Clase hija de Dungeon
class DungeonJ: public Dungeon {
	
	private:
		// Información relacionada con el generador de layout
		int ** layout;
		int nZones; // número de zonas de la mazmorra.
		int* dist;	// asignación de elementos a zonas
		int* enemies; // distribución de enemigos por zonas
		int n_enemies; // número de enemigos en toda la mazmorra.

		// Genera el layout principal de la mazmorra, quedando determinada la siguiente información:
		// - Habitaciones transitables y conexiones entre ellas
		// - Habitación inicial
		// - Habitación final
		void genLayout();

		// Nada
		void blockPath();

		// Distribuye a nivel de zona.
		//	- objeto clave 
		//	- herramienta
		//	- puzzles 
		//	- minibosses (si los hay)
		//	- boss
		void zoneAllocations();

		// Distribuye a nivel de pantalla:
		//	- objeto clave 
		//	- herramienta
		//	- puzzles 
		//	- minibosses (si los hay)
		//	- boss
		void placeItems();

		DunScreen* findScreen(int x, int y);

		//Cuenta las pantallas de la mazmorra
		int countRooms(int** layout);

		// Calcula la cantidad de enemigos para una pantalla a partir de su zona
		int getEnemies(int zone);

		void placeKeys(int zone);

		void placeBoss();

		// Dada una pantalla comprueba si tiene bloqueos
		bool checkBlocks(Screen* s);

		// Dada una pantalla comprueba si tiene elementos
		bool checkElement(Screen* s);
		
		// Comprueba si el layout es correcto empleando checkzone
		bool checkDungeon(int** layout);

		// Comprueba si no existen zonas mal colocadas
		bool checkZone(int** layout, int x, int y);

		// asigna elementos importantes(llave boss, puzzle, colectable, boss, entrada...) a zonas
		void placeZoneItems();

	public:
		// Constructora, llama a la constructora de la superclase (que no debería hacer mucho)
		DungeonJ(string zone, string theme, int gameDiff, int dungNumber, int ratio, short tool, DBManager* db);
		~DungeonJ();
		
		// Ejecuta la generación de la mazmorra, invocando secuencialmente a:
		// 	- genLayout()
		//	- blockPath()
		//	- placeItems()
		//	- genScreen()
		void generate();

		void genTable(int dungeonNumber,int gameDiff, double ratio);

};

#endif