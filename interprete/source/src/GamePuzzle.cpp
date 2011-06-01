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

#include "GamePuzzle.h"

GamePuzzle::GamePuzzle(int id, MapStatus* mapStatus, Game* g, GameState* gs) : Entity(-1, -1, g, gs)
{
	collidable = false;

	puzzleId = id;
	myMap = mapStatus;

	subscribers.clear();
};

GamePuzzle::~GamePuzzle()
{
	// Se elimina la suscripción de los listeners
	std::list<GamePuzzleListener*>::iterator it = subscribers.begin();
	while (it != subscribers.end())
	{
		(*it)->init(NULL, -1);
		it++;
	}
};

int GamePuzzle::addListener(GamePuzzleListener* listener)
{
	subscribers.push_back(listener);
	return subscribers.size()-1;
};

bool GamePuzzle::removeListener(GamePuzzleListener* listener)
{
	unsigned int oldsize = subscribers.size();
	subscribers.remove(listener);
	return oldsize > subscribers.size();
};

void GamePuzzle::solve()
{
	if (puzzleId >= 0)
		// Se resuelve el puzzle
		myMap->setPuzzleStatus(puzzleId, true);

	// y se avisa a los listeners aun si no hay puzzleId
	std::list<GamePuzzleListener*>::iterator it = subscribers.begin();
	while (it != subscribers.end())
	{
		(*it)->onSolve();
		it++;
	}
};

void GamePuzzle::unsolve()
{
	if (puzzleId >= 0)
		// Se desresuelve el puzzle
		myMap->setPuzzleStatus(puzzleId, false);

	// y se avisa a los listeners aun si no hay puzzleId
	std::list<GamePuzzleListener*>::iterator it = subscribers.begin();
	while (it != subscribers.end())
	{
		(*it)->onUnsolve();
		it++;
	}
};

bool GamePuzzle::isSolved()
{
	return myMap->getPuzzleStatus(puzzleId);
};

int GamePuzzle::getPuzzleId()
{
	return puzzleId;
};