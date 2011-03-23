#pragma once

#ifndef __HELPER_TYPES_H__
#define __HELPER_TYPES_H__

enum Dir {UP, DOWN, LEFT, RIGHT,NONE};

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

#endif