#pragma once

#ifndef __HELPER_TYPES_H__
#define __HELPER_TYPES_H__

enum Dir {UP, DOWN, LEFT, RIGHT,NONE};
struct MapId
{
	int id;
	int mapX;
	int mapY;
};

#endif