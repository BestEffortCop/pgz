#pragma once

#ifndef _ARENAENTITY_H_
#define _ARENAENTITY_H_

#include "iNotificable.h"
#include "GamePuzzleElement.h"
#include "Enemy.h"

class ArenaEntity : public GamePuzzleElement, public iNotificable
{
	private:
		std::list<Enemy*>* enemies;

	public:
		ArenaEntity();
		~ArenaEntity();

		void addEnemy(Enemy* e);
		void removeEnemy(Enemy* e);
		void onNotified(Entity* e);

		void init(GamePuzzle* puzzle);

		void solvePuzzle();
};

#endif