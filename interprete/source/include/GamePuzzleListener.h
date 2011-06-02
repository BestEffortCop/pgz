/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

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