#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include "World.h"
#include "GenVoroWorld.h"
#include "GenWormZone.h"

class Game{
	private:
		World* world;
		Overworld* ow;
		GenOverworld* genOw;
		vector<GenZone*>* zones;

	public:
		// Constructora
		Game();
		// Destructora
		~Game();

		// Generamos el mundo
		void genGame(int diff, int wSize, int numZones, int numDungeions, int numSafeZones, DBManager* myDB);
};

#endif