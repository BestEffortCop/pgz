#pragma once

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameEntity.h"
#include "Component.h"
#include <vector>

class Enemy : public GameEntity
{
	private:
		vector<Component*>* components;	
	public:

		EnemySpawnData spawnData;

		friend class Component;
		Enemy(int x, int y, Game* game, GameState* world, vector<Component*>* components);
		~Enemy();
		void onInit();
		void onStep();
		void onRender();
		void onTimer(int timer);
		void onCollision(CollisionPair other, Entity* e);
		void onDestroy();
		void onCustomEvent(int event);
		void onInitStep();
		void onEndStep();
		void onEndWorld();
};
#endif __ENEMY_H__
