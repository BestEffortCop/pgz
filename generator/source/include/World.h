#pragma once

#ifndef _WORLD_H_
#define _WORLD_H_

#include "Overworld.h"
#include "GenOverworld.h"
	
class World {
	private:
		int gameDiff;	// dificultad del juego a generar
	public:
		Overworld* overworld; // Puntero al OverWorld que instancia la clase
		
		// Constructora y destructora
		World(int gameDiff);
		~World();
		
		bool save();
};
	

#endif
