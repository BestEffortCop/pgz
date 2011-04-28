#include "DoorOpener.h"


DoorOpener::DoorOpener(Game* g, GameState* gs) : Entity(-1, -1, g, gs), GamePuzzleListener()
{
	toOpen.clear();
}

DoorOpener::~DoorOpener()
{
}

void DoorOpener::addDoor(Door* door)
{
	toOpen.push_back(door);
}

void DoorOpener::onSolve()
{
	// Se añaden todas las entidades
	for (std::list<Door*>::iterator it = toOpen.begin(); it != toOpen.end(); it++)
	{
		if ((*it) != NULL)
			(*it)->open();
	}

	instance_destroy();
}
