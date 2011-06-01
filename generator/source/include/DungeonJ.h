/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef _DUNGEONJ_H_
#define _DUNGEONJ_H_

#include "Dungeon.h"
#include "DunScreen.h"
#include <vector>
#include "IGraphControl.h"
#include "DBManager.h"


#define ENEMY_NUMBER 16
#define LONG(x1,y1,x2,y2) std::abs(x1-x2) + std::abs(y1-y2)

using namespace std;

typedef enum zoneType{ ENTRANCE, PUZZLE, MINIBOSS, COLLECTABLE, BOSS, BOSSS_KEY};

// Clase hija de Dungeon
class DungeonJ: public Dungeon {
	
	private:
		// Información relacionada con el generador de layout
		int** layout;
		int nZones; // número de zonas de la mazmorra.
		zoneType* dist;	// asignación de elementos a zonas
		int* enemies; // distribución de enemigos por zonas
		int n_enemies; // número de enemigos en toda la mazmorra.
		
		short idLock; // contador para la asignación de identificadores a bloqueos
		short idPuzzle;  // contador para la asignación de identificadores a puzzles
		short idCollectable; // contador de entidades puzzle.

		// calcula enemigos n_puzzles, n_zones, n_collectables y n_minibosses
		void compute(int gameDiff, int dungNumber,int ratio,int tool);

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

		// Coloca las llaves de la mazmorra
		void placeKeys(int zone);

		// Coloca el jefe, la habitación del objeto clave y el bloqueo del jefe 
		void placeBoss(int posIniX,int posIniY);

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
		DungeonJ(string zone, string theme, int gameDiff, int dungNumber, int ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db);
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