#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include "World.h"
#include "GenVoroWorld.h"
#include "GenWormZone.h"
#include "Decidator.h"

class Game{
	private:
		World* world;
		Overworld* ow;
		GenOverworld* genOw;
		vector<GenZone*>* zones;
		Decidator* decidator;

	public:
		// Constructora
		Game();
		// Destructora
		~Game();

		// Generamos el mundo
		void genGame(DBManager* myDB);
};

#endif