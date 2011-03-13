#pragma once

#ifndef _WORLD_H_
#define _WORLD_H_

#include "Overworld.h"
#include "GenOverworld.h"
	
class World {
	private:
		int gameDiff;	// dificultad del juego a generar
		Overworld* overworld; // Puntero al OverWorld que instancia la clase
	
	public:	
		// Constructora y destructora
		World(int difficulty);
		~World();

		//Setter de overworld
		void setOverworld(Overworld* ow);
};
	
#endif
