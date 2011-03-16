#pragma once
#ifndef __GAMEPLAYSTATE_H__
#define __GAMEPLAYSTATE_H__

#include <list>

#include "GameState.h"
#include "Entity.h"

class GamePlayState : public GameState
{
private:
	// Controller & friends here

	// Lista de Entidades a borrar y eliminar bajo una transición
	std::list<Entity*> deathRow;
public:

	// Constructora
	GamePlayState(int w, int h, Game* g);

	// Destructora
	~GamePlayState();

	// Sobrecarga del método del padre para utilizar la lista de eliminables
	bool add(Entity* e, bool condemned = true);

	// Sobrecarga del método del padre para utilizar la lista de eliminables
	bool remove(Entity* e, bool deleteAlso = false);

	// Temporal
	void renderBG();
};

#endif