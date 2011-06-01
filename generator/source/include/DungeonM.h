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

#ifndef _DUNGEONM_H_
#define _DUNGEONM_H_

#include "Dungeon.h"
#include "DunScreen.h"

class DungeonM : public Dungeon {
    private:
        short n_areas;                  // Número de áreas en las que se divide la mazmorra
        DunScreen*** layout;            // Matriz de pantallas de la mazmorra, para trabajar con mayor comodidad
        vector<DunScreen*>** areas;     // Array de vectores de pantallas, que representa a qué zona pertenece cada pantalla
		int** room_areas;				// Matriz que indica, para cada habitación, la zona de la mazmorra a la que pertenece
		short boss_corner;				// Esquina de la mazmorra en la que se encuentra el jefe
		short boss_area;				// Zona de la mazmorra por la que se accede al jefe
		short bossX, bossY;				// Coordenadas del jefe
		short finalX, finalY;			// Coordenadas de la pantalla final
		DunScreen *boss_screen, *final_screen;	// Pantallas del boss y posterior

        void calculate_size();          // Según la dificultad y el número de la mazmorra a generar, calcula el tamaño del layout y el número de zonas
        void create_rooms();            // Instancia las habitaciones de la mazmorra, la matriz layout
        void divide_into_areas();       // Establece áreas aisladas en la mazmorra (rectangulares)
		void allocate_boss();			// Coloca la habitación del boss, y lo que ello implica
        void allocate_goodies();        // Coloca llaves, llave del boss y herramienta de la mazmorra
        void connect_rooms(short area); // Conecta las habitaciones de una determinada área
        void connect_areas();           // Conecta las zonas de la mazmorra, colocando los bloqueos oportunos entre ellas
        // Distribuye las llaves y la llave del jefe por la mazmorra
        void allocate_keys();
        // Intenta hacer una puerta que conecte dos habitaciones de la misma zona
        DunScreen* make_door(DunScreen* s, int* connected, int* current_room, int dir_or, short area);
		// Comprueba si se puede ir de una habitación a otra dentro de la misma área
		bool check_room(short x1, short y1, short x2, short y2, short area, short room);
		// Añade las habitaciones que quedan aisladas a las zonas ya existentes de la mazmorra
		void add_isolated_rooms();
		// Añade una habitación aislada a una determinada zona de la mazmorra
		bool add_room_to_area(short x, short y, short area);

    public:
        DungeonM(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, short keyObj, DungeonPos dungeonPos, DBManager* db);
        ~DungeonM();

        void generate();

		void print_dungeon();	// DEBUG
};

#endif
