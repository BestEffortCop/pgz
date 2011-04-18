#pragma once

#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include <vector>
#include <stdlib.h>
#include <time.h>
#include "DunScreen.h"

using namespace std;

/*
	Clase encargada de generar una mazmorra. Una vez generado el layout, colocadas las entidades que aparecerán en ella,
	y generadas las pantallas de la misma, guarda un archivo con la información de la mazmorra. Este archivo será el que
	lea el módulo shortérprete posteriormente al ejecutar el juego.
*/

class Dungeon {
    protected:
        vector<Screen*>* screenList;	/* Lista de pantallas */
		short difficulty;				/* Dificultad del juego */
		short numDungeon;				/* Número de la mazmorra */
		short size;						/* Tamaño de la mazmorra (nº de pantallas) */
		short tool;						/* Identificador de la herramienta que va a estar en la mazmorra */
		short boss;						/* Identificador del boss que va a estar en la mazmorra */
		short miniboss;					/* Identificador del miniboss que va a estar en la mazmorra (-1 si no hay) */
		short keyItem;					/* Identificador del objeto clave que va a estar en la mazmorra */
		short ratio;					/* Ratio puzzle/acción */
		string zone;					// Zona a la que pertenece la mazmorra
		string theme;					// Temática del juego
		short width, height;			// Dimensiones del layout
		short iniX, iniY;               // Posición de la pantalla inicial de la mazmorra
		DBManager* db;					// Puntero al manager de la base de datos

		// información sobre elementos persistentes de la mazmorra
		short n_puzzles;
		short n_collectables;
		short n_puertas;
		short n_minibosses;

	public:


		// Debe encargarse de realizar las operaciones con la BDI, para que las clases hijas se centren en generar la mazmorra
		Dungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, DBManager* db);

		// Destructora
		virtual ~Dungeon();

		virtual void generate() = 0;
		bool save();

		void index_collectables();
};


#endif
