/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "GamePuzzleListener.h"

GamePuzzleListener::GamePuzzleListener()
{
	puzzle = NULL;
	listenerId = -1;
};

GamePuzzleListener::~GamePuzzleListener()
{
	if (puzzle != NULL && listenerId >= 0)
		puzzle->removeListener(this);
	listenerId = -1;
	puzzle = NULL;
};

void GamePuzzleListener::init(GamePuzzle* puzzle, int id)
{
	this->puzzle = puzzle;

	if (puzzle == NULL)
		return;

	// Si id < 0 se autosuscribe
	if (id < 0)
		listenerId = puzzle->addListener(this);
	else
		// Si no, ya nos han suscrito
		listenerId = id;

	if (isPuzzleSolved())
		onSolve();
	else
		onUnsolve();
};

GamePuzzle* GamePuzzleListener::getPuzzle()
{
	return puzzle;
};

int GamePuzzleListener::getListenerId()
{
	return listenerId;
};

void GamePuzzleListener::onSolve()
{
	// To be overriden
};

void GamePuzzleListener::onUnsolve()
{
	// To be overriden
};

bool GamePuzzleListener::isPuzzleSolved()
{
	return puzzle->isSolved();
};