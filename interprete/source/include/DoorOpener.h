#pragma once
#include "Gamepuzzlelistener.h"
#include "Door.h"

class DoorOpener : public Entity, public GamePuzzleListener
{
protected:
	std::list<Door*> toOpen;

public:
	DoorOpener(Game* g, GameState* gs);
	~DoorOpener();

	void addDoor(Door* door);
	void onSolve();
};

