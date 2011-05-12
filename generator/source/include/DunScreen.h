#pragma once

#ifndef _DUNSCREEN_H_
#define _DUNSCREEN_H_

#include <vector>
#include <string>
#include <stdlib.h>
#include "Screen.h"

// Direcciones
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Simetrías
#define NO_SYM 0            // Sin simetría
#define HOR_SYM 1           // Simetría horizontal
#define VER_SYM 2           // Simetría vertical
#define TOT_SYM 3           // Simetría horizontal

using namespace std;

// Clase que provee la funcionalidad para generar una de las pantallas de la mazmorra, especificándole todos los elementos que debe colocar.
/*
	La clase Dungeon, como parte del proceso de generación, instancia un número determinado de objetos Screen pasándole los parámetros que
	considere oportuno de los que ha recibido del generador de Mundo.
*/

class DunScreen : public Screen {
	private:
		bool door[4]; 		// Representa la existencia de cada una de las puertas de la pantalla
		bool lock[4];		// Representa la existencia o no de un bloqueo en cada una de las puertas de la pantalla
		bool boss_lock[4];	// Representa la existencia o no de un bloqueo para el jefe en alguna dirección
		short lockId[4];	// Indica el id de los bloqueos de la pantalla (-1 si no hay bloqueo)

        // Elementos a colocar en la pantalla
        bool key;
        bool boss_key;
		short puzzle; // Tipo de puzzle (Genérico 0 - herramienta >0). Valor negativo si no hay puzzle
		short boss;
		short miniboss;
		short tool;
		short keyObj;

		// Atributos y métodos necesarios para la generación de la pantalla
		short wall_size;                    // Tamaño de la pared de la mazmorra (en tiles, lo normal sería 2)
		short sym_type;                     // Tipo de simetría elegida
		bool empty_room;					// Indica si la pantalla actual debe generarse vacía (sin bloques por medio, salvo las paredes)
		bool initialRoom;					// Indica si la pantalla actual es la entrada a la mazmorra

		void modify_isolated_solids();		// Cambia sólidos aislados de la pantalla por bloques a reemplazar por Decorator
		void genQuadrants();                // Coloca elementos en la pantalla según la simetría elegido
        void genQuadrant(short q);          // Coloca elementos en el cuadrante elegido
        void genSymmetry();                 // Según el tipo de simetría, refleja los cuadrantes apropiados
        void genHorSymmetry();              // Refleja los cuadrantes superiores sobre los inferiores
        void genVerSymmetry();              // Refleja los cuadrantes de la izquierda sobre los de la derecha

		// Coloca en la habitación actual el puzzle que le ha sido indicado
		void placePuzzle();

		// Crea las paredes y las puertas de la pantalla
		void placeWalls();

		// Distribuye sólidos y semisólidos por la pantalla, además de entidades básicas, como las puertas
		void decorate();

		void placeLocks();				// Coloca los bloqueos entre áreas y el del jefe
		void placeKeys();				// Coloca una llave o llave del jefe
		void placeEntrance();			// Busca el teletransporte de la pantalla inicial y lo coloca en un trozo de pared libre
		void placeEntities();			// Coloca en la pantalla las entidades que sean necesarias
		void placeEnemies();			// Coloca tantos enemigos como requiera la pantalla

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
		DunScreen(short posX, short posY, short puzzle, short n_enemies, short boss, short miniboss, short tool, string zone, string theme, DBManager* db, short mapNumber);

		// Destructora
		~DunScreen();
		
		// Genera la pantalla en función de los elementos que se le hayan pedido que estén presentes
		void generate();
		int getFreePos(vector<int>* posUsed);

		// Coloca una puerta en la dirección d
		void setDoor(short d);
		// Coloca un bloqueo en la dirección d (se supone que se ha creado una puerta con anterioridad)
		void setLock(short d);
		void setLock(short d, short id);
		// Elimina una puerta en la dirección d
		void unSetDoor(short d);
		// Elimina un bloqueo en la dirección d 
		void unSetLock(short d);
		// Coloca un bloqueo del jefe en la dirección d
		void setBoss_lock(short d);
		void setBoss_lock(short d, short id);
		// Comprueba si la habitación tiene algún bloqueo
		bool has_lock();
		// Comprueba si la habitación tiene una única puerta
		bool has_one_door();
		// Comprueba si la posición (x, y) se encuentra delante de una puerta
		bool blocksDoor(short x, short y); 

		// Coloca un teletransporte a una posición determinada
		void placeTeleporter(short idMap, short screenX, short screenY, short tileX, short tileY);
		
		// Devuelve una posición libre de sólidos y alejada de puertas 
		void get_valid_position(int& x, int& y);

        // Getters
		short getSym_type();
		short getWall_size();
		bool getDoor(short door);
		bool getLock(short lock);
		short getPuzzle();
		short getMiniBoss();
		short getBoss();
		short getTool();
		short getDoorNum();
		bool getInitialRoom();

        // Setters
		void setWall_size(short wall_size);
		void setKey();
		void setBoss_key();
		void setTool(short tool);
		void setBoss(short boss);
		void setEmpty_room(short empty_room);
		void setKeyObj(short keyObj);
		void setInitialRoom(bool initialRoom);

		void print_screen();			// DEBUG
};

#endif
