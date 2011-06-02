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

#ifndef __HELPER_TYPES_H__
#define __HELPER_TYPES_H__

#include "Input.h"

enum Direction {NONE, UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};
enum TransitionEffect {SCROLL, FADE};
enum StandardEnemyAnimation {NOTHING, STAND, WALK, ATKMELEE, ATKRANGED, ATKSPECIAL, DAMAGED, DEAD};

struct MapLocation
{
	int id;
	int screenX;
	int screenY;
	int positionX;
	int positionY;
};

struct ToolInfo
{
	int idTool;
	bool available;
	int idAmmo;
	int ammoQuantity;
};

struct EnemySpawnData
{
	int id;
	int x;
	int y;
};

struct InputConfig
{
	bool joyMode;
		
	int gamePad;
	int xAxis, yAxis;
	int joyA, joyB, joySTART, joySELECT;

	Input::Key keyLeft, keyRight, keyUp, keyDown;
	Input::Key keyA, keyB, keySTART, keySELECT;
};

enum ButtonState { OFF, ON, PRESSED, RELEASED };

#endif