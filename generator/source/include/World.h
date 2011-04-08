#pragma once

#ifndef _WORLD_H_
#define _WORLD_H_

#include "Overworld.h"
#include "GenOverworld.h"
	
class World {
	private:
		int gameDiff;	// dificultad del juego a generar
		Overworld* overworld; // Puntero al OverWorld que instancia la clase
		GenOverworld* genOw;
		DBManager* myDB;
	
	public:	
		// Constructora y destructora
		World(int difficulty, GenOverworld* genOverw, DBManager* myDataB);
		~World();

		// Setter de overworld
		void setOverworld(Overworld* ow);
		// Construcción del overworld
		void buildOverworld();
};
	
#endif
