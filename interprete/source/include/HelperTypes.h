#pragma once

#ifndef __HELPER_TYPES_H__
#define __HELPER_TYPES_H__

#include "Input.h"

enum Direction {NONE, UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};
enum TransitionEffect {SCROLL, FADE};

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