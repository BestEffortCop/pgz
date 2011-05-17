#pragma once

#ifndef _DBACCESS_H_
#define _DBACESS_H_

#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

#define DB_PATH ".\\PGZ.db"
#define MAX_STR_LENGTH 255

class DBAccess {
	private:
		sqlite3* db;					// Puntero a la base de datos a tratar
		bool db_status;					// Estado de la base de datos tras ejecutar el último comando
	public:
		DBAccess();
		~DBAccess();

		void obtain_data();				// Obtiene la info de la BD y la escribe en un archivo
};

#endif