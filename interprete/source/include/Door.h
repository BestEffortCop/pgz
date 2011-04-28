#pragma once
#ifndef __DOOR_H__
#define __DOOR_H__

#include "Entity.h"
#include "SpriteMap.h"
#include "HelperTypes.h"

class Door : public Entity
{
public:
	bool closed;
	bool transition;
	Direction dir;

	Door(int x, int y, Direction dir, Game* game, GameState* world);
	~Door();

	void playAnimation(std::string s);

	void onStep();

	void open();
	void close();
};

#endif