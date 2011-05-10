#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include "World.h"
#include "GenVoroWorld.h"
#include "GenWormZone.h"
#include "GenForestZone.h"
#include "GenFieldZone.h"
#include "Decidator.h"
#include "Decorator.h"
#include "GenLagoonZone.h"
#include "GenDesertZone.h"

class GenGame{
	private:
		World* world;
		Overworld* ow;
		GenOverworld* genOw;
		vector<GenZone*>* zones;
		Decidator* decidator;

	public:
		// Constructora
		GenGame();
		// Destructora
		~GenGame();

		// Generamos el mundo
		void genGame(DBManager* myDB);
};

#endif