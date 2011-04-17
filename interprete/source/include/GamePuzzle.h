#pragma once
#ifndef __GAMEPUZZLE_H__
#define __GAMEPUZZLE_H__

#include <list>
#include "MapStatus.h"
#include "GamePuzzleListener.h"
#include "Entity.h"

class GamePuzzleListener;

class GamePuzzle : public Entity
{
protected:
	int puzzleId;
	MapStatus* myMap;
	std::list<GamePuzzleListener*> subscribers;
public:
	GamePuzzle(int id, MapStatus* mapstatus);
	virtual ~GamePuzzle();

	//! Añade el listener y devuelve su id
	int addListener(GamePuzzleListener* listener);
	//! Elimina el listener
	bool removeListener(GamePuzzleListener* listener);

	void solve();
	void unsolve();

	//! Devuelve true si está resuelto
	bool isSolved();

	int getPuzzleId();
};

#endif