#pragma once
#ifndef __GAMEPUZZLEELEMENT_H__
#define __GAMEPUZZLEELEMENT_H__

#include "GamePuzzle.h"

class GamePuzzleElement
{
protected:
	GamePuzzle* puzzle;
public:
	GamePuzzleElement();
	virtual ~GamePuzzleElement();
	virtual void init(GamePuzzle* puzzle);

	virtual void solvePuzzle();
	virtual void unsolvePuzzle();
	//! Cambia el valor del puzzle y devuelve el nuevo
	virtual bool switchPuzzle();
	virtual bool isPuzzleSolved();
};

#endif