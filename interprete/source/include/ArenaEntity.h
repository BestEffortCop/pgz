#pragma once

#ifndef _ARENAENTITY_H_
#define _ARENAENTITY_H_

#include "iNotificable.h"
#include "GamePuzzleElement.h"
#include "Entity.h"
#include "Enemy.h"

class ArenaEntity : public Entity, public GamePuzzleElement, public iNotificable
{
	private:
		std::list<Enemy*> enemies;

	public:
		ArenaEntity(int x, int y, Game* g, GameState* gs);
		~ArenaEntity();

		void addEnemy(Enemy* e);
		void onNotified(Entity* e);

		void init(GamePuzzle* puzzle);
		void onStep();
};

#endif