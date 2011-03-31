#pragma once

#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <vector>
#include <string>
#include <stdlib.h>
#include "DBManager.h"

#define SCREEN_WIDTH 14		// Ancho de pantalla en número de tiles
#define SCREEN_HEIGHT 12 	// Alto de la pantalla en número de tiles

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define NO_SYM 0            // Sin simetría
#define HOR_SYM 1           // Simetría horizontal
#define VER_SYM 2           // Simetría vertical
#define TOT_SYM 3           // Simetría horizontal

using namespace std;

// Los structs "enemy", "entity" y "tileFG" son candidatos a fusionarse

struct enemy {
	short id;			// ID del enemigo en la BDJ
	short posX, posY;	// Posición del enemigo en la pantalla
};

struct entity {
	short id;			// ID de la entidad en la BDJ
	short posX, posY;	// Posición de la entidad en la pantalla
	// Tipo?
};

struct tileFG {		// Tile en foreground
	short id;			// identificador del tile
	short posX, posY;	// posición del tile en la pantalla
};

struct puzzle_t {
	short type;		// Tipo del puzzle
	short id;			// Id para identificar el puzzle dentro de la mazmorra
};

// Clase que provee la funcionalidad para generar una de las pantallas de la mazmorra, especificándole todos los elementos que debe colocar.
/*
	La clase Dungeon, como parte del proceso de generación, instancia un número determinado de objetos Screen pasándole los parámetros que
	considere oportuno de los que ha recibido del generador de Mundo.
*/

class Screen {
	private:
		short solids[SCREEN_WIDTH][SCREEN_HEIGHT]; // Disposición física de la pantalla.
		short tiles[SCREEN_WIDTH][SCREEN_HEIGHT];  // Distribución gráfica de la pantalla.

		DBManager* db;			// Puntero al manager de la base de datos del generador

		short idTileSet; 		// identificador del tileSet que usa la pantalla
		short idMusic;		// identificador de la música que suena en la pantalla

		short posIniX, posIniY;	// Posición inicial del personaje en la pantalla

		bool door[4]; 		// Representa la existencia de cada una de las puertas de la pantalla
		bool lock[4];		// Representa la existencia o no de un bloqueo en cada una de las puertas de la pantalla

		// Elementos que aparecen en la pantalla
		vector<entity>* entities; 	// Lista de entidades que aparecen en la pantalla
		vector<enemy>* enemies;		// Lista de enemigos que aparecen en la pantalla
		vector<tileFG>* fgTiles;		// Lista de tiles en foreground
		vector<puzzle_t>* puzzles;		// Lista de puzzles que aparecen en la pantalla

		short posX, posY;   // Coordenada en x, y de la pantalla en el layout de la mazmorra.
		short n_enemies; 	// Número de enemigos que debería haber en la pantalla
		short n_entities;	// Número de entidades que hay en la pantalla
		short n_tilesFG; 	// Número de tiles en foreground de la pantalla
		short n_puzzles; 	// Número de puzzles de la pantalla

        // Elementos a colocar en la pantalla
        bool key;
        bool boss_key;
		short puzzle; // Tipo de puzzle (Genérico 0 - herramienta >0). Valor negativo si no hay puzzle
		short boss;
		short miniboss;
		short tool;

		string zone; // Tipo de zona.

		// Atributos y métodos necesarios para la generación de la pantalla
		short wall_size;                    // Tamaño de la pared de la mazmorra (en tiles, lo normal sería 2)
		short sym_type;                     // Tipo de simetría elegida
		void genQuadrants();                // Coloca elementos en la pantalla según la simetría elegido
        void genQuadrant(short q);          // Coloca elementos en el cuadrante elegido
        void genSymmetry();                 // Según el tipo de simetría, refleja los cuadrantes apropiados
        void genHorSymmetry();              // Refleja los cuadrantes superiores sobre los inferiores
        void genVerSymmetry();              // Refleja los cuadrantes de la izquierda sobre los de la derecha
        bool blocksDoor(short x, short y);  // Comprueba si la posición (x, y) se encuentra delante de una puerta

		// Coloca en la habitación actual el puzzle que le ha sido indicado
		void placePuzzle();

		// Crea las paredes y las puertas de la pantalla
		void placeWalls();

		// Distribuye sólidos y semisólidos por la pantalla, además de entidades básicas, como las puertas
		void decorate();

		void placeEntities();			// Coloca en la pantalla las entidades que sean necesarias
		void placeEnemies();			// Coloca tantos enemigos como requiera la pantalla
		void saveFGTiles(FILE* file);	// guarda los tiles de foreground en el archivo file abierto
		void savePuzzles(FILE* file);	// guarda el número y la lista de puzzles de la pantalla
		void saveEntities(FILE* file);	// guarda el número y la lista de las entidades de la pantalla en el file abierto
		void saveEnemies(FILE* file);	// guarda el número y la lista de los enemigos de la pantalla en file

	public:
		// Crea un objeto pantalla de toda la mazmorra listo para generar su contenido mediante la llamada al método generate().
		// Incialmente no tiene ninguna puerta ni ningún bloqueo
		/*
			posX coordenada en x de la pantalla en el layout de la mazmorra.
			posY coordenada en y de la pantalla en el layout de la mazmorra.
			puzzle tipo de puzzle que se colocara en la pantalla mediante un identificador. Si es negativo no existe puzzle.
			door indica el número de puertas de la pantalla, sus conexiones con otras estancias de la mazmorra.
			n_enemies es el número de enemigos que debe aparecer en la pantalla
			boss indica si hay jefe en esta habitación, y cuál
			miniboss indica si hay minijefe en esta habitación, y cuál
			tool indica si hay herramienta en esta habitación, y cuál
			db es una referencia a la interfaz con la base de datos
		*/
		Screen(short posX, short posY, short puzzle, short n_enemies, short boss, short miniboss, short tool, string zone, DBManager* db);

		// Destructora
		~Screen();


		// Genera la pantalla en función de los elementos que se le hayan pedido que estén presentes
		void generate();

		// Guarda la información de la pantalla en el archivo file previamente abierto por el generador
		bool save();

		// Coloca una puerta en la dirección d
		void setDoor(short d);
		// Coloca un bloqueo en la dirección d (se supone que se ha creado una puerta con anterioridad)
		void setLock(short d);

        // Getters
		short getPosX();
		short getPosY();
		short getSolid(short x, short y);
		short getSym_type();
		short getWall_size();
		bool getDoor(short door);
		bool getLock(short lock);

        // Setters
		void setWall_size(short wall_size);
		void setKey();
		void setBoss_key();
		void setTool(short tool);
		void setBoss(short boss);

		void print_screen();			// DEBUG
};


#endif
