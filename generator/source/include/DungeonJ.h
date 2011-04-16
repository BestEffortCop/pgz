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
#define BOSS_KEY 5
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

		// Distribuye por las zonas de la mazmora lo siguiente:
		//	- objeto clave 
		//	- herramienta
		//	- puzzles 
		//	- minibosses (si los hay)
		//	- boss
		void placeItems();

		DunScreen* findScreen(int x, int y);

		int countRooms(int** layout);

		int getEnemies(int zone);

		void placeKeys(int zone);

		void placeBoss();

		bool checkBlocks(Screen* s);

		bool checkElement(Screen* s);

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