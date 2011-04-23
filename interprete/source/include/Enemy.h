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
		enum StandardEnemyAnimation {NONE, STAND, WALK, ATKMELEE, ATKRANGED, ATKSPECIAL, DAMAGED, DEAD};

		EnemySpawnData spawnData;
		int hpMax, mpMax, strength, defence;
		std::string gfxPath;
		StandardEnemyAnimation currentAnim;
		Direction dir;
		bool inAnim;

		bool dead;

		void init(std::string gfxPath, int hpMax, int mpMax, int strength, int defense);

		friend class Component;
		Enemy(int x, int y, Game* game, GameState* world, vector<Component*>* components);
		virtual ~Enemy();
		virtual void onInit();
		virtual void onStep();
		virtual void onRender();
		virtual void onTimer(int timer);
		virtual void onCollision(CollisionPair other, Entity* e);
		virtual void onDestroy();
		virtual void onCustomEvent(int event);
		virtual void onInitStep();
		virtual void onEndStep();
		virtual void onEndWorld();
};
#endif __ENEMY_H__
