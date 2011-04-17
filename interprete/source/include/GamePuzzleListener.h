#pragma once
#ifndef __GAMEPUZZLELISTENER_H__
#define __GAMEPUZZLELISTENER_H__

#include "GamePuzzle.h"

class GamePuzzle;

class GamePuzzleListener
{
protected:
	int listenerId;
	GamePuzzle* puzzle;

public:
	GamePuzzleListener();
	// Autodessuscripción
	virtual ~GamePuzzleListener();

	// Init autosubscriptor si id = -1
	virtual void init(GamePuzzle* puzzle, int id = -1);

	virtual GamePuzzle* getPuzzle();
	virtual int getListenerId();

	virtual void onSolve();
	virtual void onUnsolve();
	
	virtual bool isPuzzleSolved();
};

#endif