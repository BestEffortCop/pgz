#pragma once

#ifndef _DUNGEONM_H_
#define _DUNGEONM_H_

#include "Dungeon.h"
#include "DunScreen.h"

class DungeonM : public Dungeon {
    private:
        short n_areas;                  // Número de áreas en las que se divide la mazmorra
        DunScreen*** layout;               // Matriz de pantallas de la mazmorra, para trabajar con mayor comodidad
        vector<DunScreen*>** areas;         // Array de vectores de pantallas, que representa a qué zona pertenece cada pantalla

        void calculate_size();          // Según la dificultad y el número de la mazmorra a generar, calcula el tamaño del layout y el número de zonas
        void create_rooms();            // Instancia las habitaciones de la mazmorra, la matriz layout
        void divide_into_areas();       // Establece áreas aisladas en la mazmorra (rectangulares)
        void allocate_goodies();        // Coloca boss, minibosses, llaves, llave del boss y herramienta de la mazmorra
        void connect_rooms(short area); // Conecta las habitaciones de una determinada área
        void connect_areas();           // Conecta las zonas de la mazmorra, colocando los bloqueos oportunos entre ellas
        // Distribuye las llaves y la llave del jefe por la mazmorra
        void allocate_keys(short boss_area);
        // Intenta hacer una puerta que conecte dos habitaciones de la misma zona
        DunScreen* make_door(DunScreen* s, int* connected, int* current_room, int dir_or, short area);
        // Intenta colocar un bloqueo entre dos habitaciones de zonas contiguas
        DunScreen* make_lock(DunScreen* s1, short area);

    public:
        DungeonM(string zone, string theme, short gameDiff, short dungNumber, short ratio, short tool, DBManager* db);
        ~DungeonM();

        void generate();

		void print_dungeon();	// DEBUG
};

#endif
