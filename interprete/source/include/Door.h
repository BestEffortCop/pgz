#pragma once
#ifndef __DOOR_H__
#define __DOOR_H__

#include "Entity.h"
#include "SpriteMap.h"
#include "MapStatus.h"
#include "HelperTypes.h"

class Door : public Entity
{
public:
	enum DoorType {NORMAL, BLOCKED, KEYDOOR, BOSSDOOR};

protected:
	DoorType doorType;

	MapStatus* myMapStatus;
	int idDoor;

public:

	bool closed;
	bool transition;
	Direction dir;

	Door(int x, int y, Direction dir, Game* game, GameState* world);
	~Door();

	void init(int idDoor, MapStatus* mapStatus);

	void playAnimation(std::string s);

	void onStep();

	void open();
	void close();

	bool isOpen();

	void setDoorType(DoorType doorType);
	DoorType getDoorType();
};

#endif