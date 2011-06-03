/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef _DBMANAGER_H_
#define _DBMANAGER_H

#define DB_PATH ".\\PGZ.db"
#define MAX_STR_LENGTH 255

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string>
#include <set>
#include <vector>

#include "DefTypes.h"			// Incluye los structs que de datos que formarán la BDJ
#include "Paths.h"

using namespace std;

typedef enum entityEffect { NONE, HP, MP, MONEY, KEY, HPMAX, MPMAX, BOSSKEY, KEYOBJ, TOOLEFFECT, PIGEON };

struct ZoneInfo { int tileSetId; string gen; };
struct PairIdGfxId { int id; int gfxId; };
struct NPCInfo { int gfxId; int npcType; };

class DBManager {
	private:
		sqlite3* db;					// Puntero a la base de datos a tratar
		bool db_status;					// Estado de la base de datos tras ejecutar el último comando
		short keyGfxId;					// Id del gráfico de las llaves que van a aparecer en el juego
		short bossKeyGfxId;				// Id del gráfico de las llaves del jefe que van a aparercer en el juego
		short keyId;
		short bossKeyId;
		obj_t keyObj;					// Objeto clave del juego
		obj_t pigeon;					// Pigeon del juego
		obj_t finalElem;				// Elemento final del juego
		
		// Datos usados hasta el momento que habrá que volcar a la BDJ
		set<enemy_t>* enemies;			// Conjunto de enemigos del juego
		set<npc_t>* npcs;				// Conjunto de NPCs del juego
		set<tool_t>* tools;				// Conjunto de herramientas del juego
		set<item_t>* items;				// Conjunto de ítems del juego
		set<item_t>* powUps;			// Conjunto de PowerUps del juego
		set<boss_t>* bosses;			// Conjunto de bosses del juego
		set<block_t>* blocks;			// Conjunto de bloqueos que aparecen en el juego
		set<zone_t>* zones;				// Conjunto de zonas que aparecen en el mundo
		set<dungeon_t>* dungeons;		// Conjunto de (generadores de) mazmorras
		set<player_t>* players;			// Conjunto de players del juego
		set<puzzle_elem_t>* puzzle_elems;	// Conjunto de elementos de puzzle del juego
		string doorPath;				// Path al gráfico de las puertas de las mazmorras del juego
		string bossDoorPath;			// Path al gráfico de las puertas de los bosses del juego

		vector<gfx_t>* graphics;		// Vector de gráficos usados en el juego
		vector<sfx_t>* sounds;			// Vector de sonidos usados en el juego
		vector<essential_elem_t>* essential_elems;	// Vector de gráficos que se usan en todos los juegos (imprescindibles)
		vector<gfx_t>* tileSets;		// Vector de tileSets que aparecerán en el juego

		vector<string>* tags;			// Vector con las etiquetas que ha elegido Decidator para el juego

		int rowNumber(char* query);	// Devuelve el número de filas que produce la consulta
		void savePlayers();			// Guarda el conjunto de players en el archivo de players de la BDJ
		void saveEnemies();			// Guarda el conjunto de enemigos en el archivo de enemigos de la BDJ
		void saveNPCs();			// Guarda el conjunto de npcs en el archivo de enemigos de la BDJ
		void saveTools();			// Guarda el conjunto de herramientas en el archivo de herramientas de la BDJ
		void saveItems();			// Guarda el conjunto de ítems en el archivo de enemigos de la BDJ
		void savePowUps();			// Guarda el conjunto de power ups en el archivo de power ups de la BDJ
		void saveBosses();			// Guarda el conjunto de bosses en el archivo de bosses de la BDJ
		void saveBlocks();			// Guarda el conjunto de bloqueos en el archivo de bloqueos de la BDJ
		void saveDoors();
		void savePigeon();
		void saveKeyObj();
		void saveFinalElem();
		void savePuzzleElems();

		void saveGfx();				// Guarda los archivos de gráficos en la BDJ
		void copyGfx();				// Copia los archivos de gráficos de la BDD a la BDJ
		void saveSfx();				// Guarda los archivos de sonido en la BDJ
		void copySfx();				// Copia los archivos de sonido de la BDD a la BDJ
		void saveTileSets();		// Guarda los datos de los tileSets
		void copyTileSets();		// Copia los tileSets de la BDD a la BDJ
		void saveEssentialElems();	// Guarda los datos de los elementos comunes a todos los juegos
		void copyEssentialElems();	// Copia los archivos comunes a todos los juegos de la BDD a la BDJ
		void copyDoors();
		void copyEnemyComponents();	// Copia los .nmy que necesitan los enemigos del juego
		
		void gather_essential_elements();		// Obtiene de la BDD los datos de los elementos comunes a todos los juegos
		void read_tags();						// Lee las etiquetas que Decidator ha escogido para el juego

		vector<short>* get_valid_elems(char* elem); // Devuelve un conjunto de ids de una tabla que cumplen con las tags de Decidator
		vector<short>* filter_by_zone(char* elem, string zone, vector<short>* elems);	// Coge el vector de ids válidos por temática y se queda con los que cumplen con la zona

		bool belongsTo(int id, vector<short>* elems);	// Comprueba si el id pertenece al vector de ids

	public:
		DBManager();
		~DBManager();

		// Ahora ya nada depende de Theme (bueno, sí, pero no lo indica el cliente)
		short getEnemy(string zone);
		short getPowUp();
		short getBlock(string zone, short tool);
		short getTool();
		short getItem();
		NPCInfo getNPC(string zone);
		ZoneInfo getZone();						// Devuelve el nombre del generador de zona que se debe usar
		short getDungeon(string zone);			// Al contrario que los demás, este método devuelve el id del tileSet usado
		short getFinalDungeon(string zone);		// Lo mismo que getDungeon
		short getFinalElem();					// Devuelve el gfxId que usa
		short getPigeon();						// Devuelve el id
		short getKeyObj();						// Devuelve el id
		short getPlayer();
		short getFloorButton();					// Devuelve el gfxId del floorButton
		void getDoors();

		short getTileSet(string zone);			// Devuelve el id del tilset que usa una determinada zona
		short getDungeonTileSet(string zone);

		string getPath(char* table, short id);	// Devuelve el path al archivo de la tabla 'table' con id 'id'

		short getGfxId(char* table, short id);	// Devuelve el id del gráfico de la fila de identificador 'id' de la tabla 'table'
		short getPowUpEffect(short id);			// Devuelve el efecto del power up de identificador 'id'
		short getPower(char* table, short id);	// Devuelve el power de la tabla especificada
		short getDmgType(short idBlockade);		// Devuelve el tipo de daño que rompe el blockade de id idBlockade
		short getKeyGfxId();					// Devuelve el id del gráfico de la llave que se usa en el juego (tarea de decidator)
		short getBossKeyGfxId();				// Devuelve el id del gráfico de la llave del boss que se usa en el juego
		short getKeyId();
		short getBossKeyId();

		void getKey();				// Obtiene la llave que se usará en el juego
		void getBossKey();			// Obtiene la llave del jefe que se usará en el juego

		void save();							// Vuelca todos los datos y archivos necesarios a la BDJ
};

#endif