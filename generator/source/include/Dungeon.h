/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//or by playing it in its actual state.												//
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

#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include <vector>
#include <stdlib.h>
#include <time.h>
#include "DunScreen.h"
#include "DunDecorator.h"

using namespace std;

/*
	Clase encargada de generar una mazmorra. Una vez generado el layout, colocadas las entidades que aparecerán en ella,
	y generadas las pantallas de la misma, guarda un archivo con la información de la mazmorra. Este archivo será el que
	lea el módulo shortérprete posteriormente al ejecutar el juego.
*/
struct DungeonPos { short screenX; short screenY; short tileX; short tileY; };


class Dungeon {
    protected:
        vector<DunScreen*>* screenList;		/* Lista de pantallas */
		short difficulty;					/* Dificultad del juego */
		short numDungeon;					/* Número de la mazmorra */
		short size;							/* Tamaño de la mazmorra (nº de pantallas) */
		short tool;							/* Identificador de la herramienta que va a estar en la mazmorra */
		short keyObj;						// Id del objeto clave que hay en la mazmorra
		short boss;							/* Identificador del boss que va a estar en la mazmorra */
		short miniboss;						/* Identificador del miniboss que va a estar en la mazmorra (-1 si no hay) */
		short keyItem;						/* Identificador del objeto clave que va a estar en la mazmorra */
		short ratio;						/* Ratio puzzle/acción */
		string zone;						// Zona a la que pertenece la mazmorra
		string theme;						// Temática del juego
		short width, height;				// Dimensiones del layout
		short iniX, iniY;					// Posición de la pantalla inicial de la mazmorra
		short wScreenX, wScreenY;			// Posición de la pantalla del mundo en la que se encuentra la mazmorra
		short wTileX, wTileY;				// Posición del tile en la pantalla del mundo por el que se entra en la mazmorra
		DBManager* db;						// Puntero al manager de la base de datos
		Decorator* decorator;				// Puntero al decorador de pantallas
		GenPuzzle* genPuzzle;				// Puntero al generador de Puzzles. Para debug lo pongo aquí de momento. 

		// información sobre elementos persistentes de la mazmorra
		short n_puzzles;
		short n_collectables;
		short n_puertas;
		short n_minibosses;

		// Busca en el vector de pantallas aquella con las coordenadas dadas
		DunScreen* findScreen(int x, int y); 

		void saveLayout(FILE* file);

	public:


		// Debe encargarse de realizar las operaciones con la BDI, para que las clases hijas se centren en generar la mazmorra
		Dungeon(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db);

		// Destructora
		virtual ~Dungeon();

		// Desencadena la generación de la mazmorra (a implementar en las clases hijas)
		virtual void generate() = 0;

		// Guarda la mazmorra actual en sus archivos correspondientes
		bool save(std::string path);

		// Cuenta e indexa las entidades collectables de la mazmorra
		void index_collectables();

		// Getters
		short getWScreenX();
		short getWScreenY();
		short getWTileX();
		short getWTileY();

		short getIniDScreenX();
		short getIniDScreenY();
		short getIniDTileX();
		short getIniDTileY();
};


#endif
