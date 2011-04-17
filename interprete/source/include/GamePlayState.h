#pragma once
#ifndef __GAMEPLAYSTATE_H__
#define __GAMEPLAYSTATE_H__

#include <list>

#include "GameState.h"
#include "controller.h"
#include "TileTextLabel.h"

class Controller;

class GamePlayState : public GameState
{
	friend class Controller;

	private:

		list<Entity*>* localEntities;
		
	public:

		// Constructora
		GamePlayState(int w, int h, Game* g);

		// Destructora
		~GamePlayState();

		// Sobrecarga del método del padre para utilizar la lista de eliminables
		bool add(Entity* e, bool local = true);

		// Envoltorio del método del padre para utilizar la lista de eliminables
		// que comprueba automaticamente si la entidad está en deathRow
		bool removeLocals();

		// Temporal
		void renderBG();

		void onStep();
};

#endif