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

#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <vector>
#include <string>
#include <stdlib.h>
#include "DBManager.h"
#include "Entity.h"
#include "Paths.h"

#define SCREEN_WIDTH 14		// Ancho de pantalla en número de tiles
#define SCREEN_HEIGHT 12 	// Alto de la pantalla en número de tiles
#define TILE_WIDTH 16		// Ancho del tile en píxeles
#define TILE_HEIGHT 16		// Alto del tile en píxeles
#define AUTOTILE_DIVISION 2 // En cuantos tiles divide el autotiler

using namespace std;

struct enemy {
	short id;			// ID del enemigo en la BDJ
	short posX, posY;	// Posición del enemigo en la pantalla
	short linkedTo;		// idCollectable de la entidad a la que está conectado
};

struct tileFG {		// Tile en foreground
	short id;			// identificador del tile
	short posX, posY;	// posición del tile en la pantalla
};

struct puzzle_t {
	short id;			// Id para identificar el puzzle dentro de la mazmorra
	short type;
};

typedef enum entityType { DOOR, BOSSDOOR, ITEM, TILEDENTITY, DMGBLOCKADE, TILEDPUSHABLE, FLOORBUTTON, INSTANCIATOR, DOOR_OPEN_CLOSE, ARENA, TELEPORTATOR, TOOL, DOOR_CLOSER, NOKEYDOOR, FINAL_DOOR, FINAL_ELEMENT, NPC };

typedef enum dungeonType { NORMAL, FINAL};

class Screen {
	protected:
		short solids[SCREEN_WIDTH][SCREEN_HEIGHT]; // Disposición física de la pantalla.
		short tiles[SCREEN_WIDTH*AUTOTILE_DIVISION][SCREEN_HEIGHT*AUTOTILE_DIVISION];  // Distribución gráfica de la pantalla.

		DBManager* db;			// Puntero al manager de la base de datos del generador

		short idTileSet; 		// identificador del tileSet que usa la pantalla
		short idMusic;			// identificador de la música que suena en la pantalla

		short mapNumber;		// Numero de mapa al que pertence.
		short posIniX, posIniY;	// Posición inicial del personaje en la pantalla

		// Elementos que aparecen en la pantalla
		vector<Entity*>* entities; 	// Lista de entidades que aparecen en la pantalla
		vector<enemy>* enemies;		// Lista de enemigos que aparecen en la pantalla
		vector<tileFG>* fgTiles;		// Lista de tiles en foreground
		vector<puzzle_t>* puzzles;		// Lista de puzzles que aparecen en la pantalla

		short posX, posY;   // Coordenada en x, y de la pantalla en el mapa (ya sea de mundo o mazmorra)
		short n_enemies; 	// Número de enemigos que debería haber en la pantalla
		short n_entities;	// Número de entidades que hay en la pantalla
		short n_tilesFG; 	// Número de tiles en foreground de la pantalla
		short n_puzzles; 	// Número de puzzles de la pantalla

		string zone;	// Tipo de zona en la que se encuentra la pantalla

		void saveFGTiles(FILE* file);	// guarda los tiles de foreground en el archivo file abierto
		void savePuzzles(FILE* file);	// guarda el número y la lista de puzzles de la pantalla
		void saveEntities(FILE* file);	// guarda el número y la lista de las entidades de la pantalla en el file abierto
		void saveEnemies(FILE* file);	// guarda el número y la lista de los enemigos de la pantalla en file

		//* Cajita de mierda de Rafa *//
		int tileW, tileH;
		

	public:
		// Constructora de la pantalla
		/*
			mapNumber número de mapa al que pertence esta screen.
			posX coordenada en x de la pantalla en el layout de la mazmorra.
			posY coordenada en y de la pantalla en el layout de la mazmorra.
			n_enemies es el número de enemigos que debe aparecer en la pantalla
			zone y theme son la zona del juego a la que pertenece la pantalla y la temática del juego 
			db es una referencia a la interfaz con la base de datos
		*/
		Screen(short mapNumber, short posX, short posY, short n_enemies, string zone, DBManager* db);

		// Destructora
		virtual ~Screen();

		// Guarda la información de la pantalla en un archivo
		bool save(std::string path);

		

		// Comprueba si un elemento se encuentra en el vector
		bool contains(int elem, vector<int>* collect);

		virtual void generate() = 0;
		virtual int getFreePos(vector<int>* posUsed) = 0;

		// Comprueba si hay una entidad en la posición pos
		bool isThereAnyEntityAt(vector<Entity*>* entities, int pos);
		

        // Getters
		short getPosX();
		short getPosY();
		short getPosIniX();
		short getPosIniY();
		short getSolid(short x, short y);
		short getNEnemies();
		vector<Entity*>* getEntities();
		string getZone();
		vector<puzzle_t>* getPuzzles();

		//short[SCREEN_WIDTH*AUTOTILE_DIVISION][SCREEN_HEIGHT*AUTOTILE_DIVISION] getTiles();
		short getTile(int x, int y);
		void setTile(int x, int y, short tileId);
		void setSolid(int x, int y, short solidId);
		void setPosIni(int x, int y);
		void setIdTileset(short id);
		void addEntity(Entity* ent);
		void addEnemy(enemy e);
		void addPuzzle(puzzle_t p);
};
#endif
