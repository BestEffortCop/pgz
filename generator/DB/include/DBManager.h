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

#include "DefTypes.h"			// Incluye los structs que de datos que formarán la BDJ

using namespace std;

class DBManager {
	private:
		sqlite3* db;			// Puntero a la base de datos a tratar
		bool db_status;			// Estado de la base de datos tras ejecutar el último comando
		
		// Datos usados hasta el momento que habrá que volcar a la BDJ
		set<enemy_t>* enemies;		// Conjunto de enemigos del juego
		set<npc_t>* npcs;			// Conjunto de NPCs del juego
		set<item_t>* items;			// Conjunto de ítems del juego
		set<item_t>* powUps;		// Conjunto de PowerUps del juego
		set<exchange_t>* exchange;	// Conjunto de objetos de intercambio del juego
		set<boss_t>* bosses;		// Conjunto de bosses del juego

		short last_exchange;		// Id del último objeto de intercambio en la cadena

		int rowNumber(char* query);	// Devuelve el número de filas que produce la consulta

	public:
		DBManager();
		~DBManager();

		short getEnemy(string zone);
		short getExchange(string theme);
		short getItem(string zone);
		npc_t getNPCbyZone(string zone);
		npc_t getNPCbyTheme(string theme);

		void saveToBDJ();
};

#endif