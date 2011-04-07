#pragma once

#ifndef __GAME_ENTITY_H__
#define __GAME_ENTITY_H__

#include "Entity.h"


class GameEntity : public Entity
{
	public: 
		GameEntity(int x, int y, Game* game, GameState* world);
};

#endif
