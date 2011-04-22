#pragma once

#ifndef __ENTITY_READER_H__
#define __ENTITY_READER_H__

#include <stdio.h>
#include <vector>
#include "Entity.h"
#include "DataBaseInterface.h"

class EntityReader 
{
	public:
		enum EntityTypes { Door, BossDoor, Item, TiledEntity, DmgBlockade, TiledPushable, FloorButton, Instantiator, AbreDoors, Arena, Teleporter };
		Game* game;
		GameState* gamestate;
		DataBaseInterface* dbi;

		EntityReader(Game* g, GameState* gs, DataBaseInterface* dbi);
		~EntityReader();

		bool readEntities(FILE* file, vector<Entity*>* screenEntities);
};


#endif