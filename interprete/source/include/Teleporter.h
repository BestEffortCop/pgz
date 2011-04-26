#pragma once
#ifndef _TELEPORTER_H_
#define _TELEPORTER_H_

#include "Entity.h"
#include "Stamp.h"
#include "PGZGame.h"

class Teleporter : public Entity
{
public:

	MapLocation destination;

	Teleporter(MapLocation m, int x, int y, Game* g, GameState* gs, int w = 16, int h = 16);

	~Teleporter();

	void onCollision(CollisionPair pair, Entity* other);
};

#endif