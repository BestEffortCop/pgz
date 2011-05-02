#pragma once

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameEntity.h"
#include "Component.h"
#include "iNotificable.h"
#include "iDamageable.h"
#include <vector>

class EnemyTool;

class Component;

class Enemy : public GameEntity, public iDamageable
{
	private:
		vector<Component*>* components;
		iNotificable* toNotify;
		// Dirección de colisión con la ultima cosa que nos dañó
		Direction lastEnemyDirection;

	public:
		enum StandardEnemyAnimation {NONE, STAND, WALK, ATKMELEE, ATKRANGED, ATKSPECIAL, DAMAGED, DEAD};
		enum EnemyDifficulty {EASY, NORMAL, DIFFICULT, INSANE};

		EnemySpawnData spawnData;

		int hpMax, mpMax, strength, defence;
		std::string gfxPath;
		StandardEnemyAnimation currentAnim;
		Direction dir;
		bool inAnim, dead;

		void init(std::string gfxPath, int hpMax, int mpMax, int strength, int defense, iNotificable* toNotify = NULL);
		void setLastDmgDirection(Direction dir);
		Direction getLastDmgDirection();

		friend class Component;
		friend class EnemyTool;

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
		void onDamage(int damage, short damageType);
		void onDeath();

		std::vector<Component*>* getComponents();
};
#endif __ENEMY_H__
