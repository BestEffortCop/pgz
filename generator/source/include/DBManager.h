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

using namespace std;

class DBManager {
	private:
		sqlite3* db;					// Puntero a la base de datos a tratar
		bool db_status;					// Estado de la base de datos tras ejecutar el último comando
		
		// Datos usados hasta el momento que habrá que volcar a la BDJ
		set<enemy_t>* enemies;			// Conjunto de enemigos del juego
		set<npc_t>* npcs;				// Conjunto de NPCs del juego
		set<item_t>* items;				// Conjunto de ítems del juego
		set<item_t>* powUps;			// Conjunto de PowerUps del juego
		set<exchange_t>* exchange;		// Conjunto de objetos de intercambio del juego
		set<boss_t>* bosses;			// Conjunto de bosses del juego
		set<block_t>* blocks;			// Conjunto de bloqueos que aparecen en el juego
		set<worldGen_t>* worldGens;		// Conjunto de generadores de mundo
		set<dungeonGen_t>* dungeonGens;	// Conjunto de generadores de mazmorra

		vector<gfx_t>* graphics;		// Vector de gráficos usados en el juego
		vector<sfx_t>* sounds;			// Vector de sonidos usados en el juego

		short last_exchange;			// Id del último objeto de intercambio en la cadena

		int rowNumber(char* query);	// Devuelve el número de filas que produce la consulta
		void saveEnemies();			// Guarda el conjunto de enemigos en el archivo de enemigos de la BDJ
		void saveNPCs();			// Guarda el conjunto de npcs en el archivo de enemigos de la BDJ
		void saveItems();			// Guarda el conjunto de ítems en el archivo de enemigos de la BDJ
		void savePowUps();			// Guarda el conjunto de power ups en el archivo de power ups de la BDJ
		void saveExchange();		// Guarda el conjunto de objetos de intercambio en el archivo de objetos de intercambio de la BDJ
		void saveBosses();			// Guarda el conjunto de bosses en el archivo de bosses de la BDJ
		void saveBlocks();			// Guarda el conjunto de bloqueos en el archivo de bloqueos de la BDJ

		char* getPath(char* table, short id);	// Devuelve el path al archivo de la tabla 'table' con id 'id'

		void saveGfx();							// Guarda los archivos de gráficos en la BDJ
		void copyGfx();							// Copia los archivos de gráficos de la BDD a la BDJ
		void saveSfx();							// Guarda los archivos de sonido en la BDJ
		void copySfx();							// Copia los archivos de sonido de la BDD a la BDJ

	public:
		DBManager();
		~DBManager();

		short getEnemy(string zone, string theme);
		short getPowUp(string theme);
		zone_t* getZone(string theme);
		short getExchange(string theme);
		block_t getBlock(string theme, string zone, short tool);
		short getItem(string zone);
		short getNPC(string zone, string theme);
		short getWorldGen(string theme);
		short getDungeonGen(string theme);

		void save();							// Vuelca todos los datos y archivos necesarios a la BDJ
};

#endif