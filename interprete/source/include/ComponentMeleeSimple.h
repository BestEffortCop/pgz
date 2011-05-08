#pragma once

#ifndef __COMPONENTMELEE_SIMPLE_H__
#define __COMPONENTMELEE_SIMPLE_H__

#include "Enemy.h"
#include "Stamp.h"
#include "HelperTypes.h"
#include "iDamageable.h"
#include <cmath>

class Enemy;

class ComponentMeleeSimple : public Component
{
	private:
		enum MeleeEnemyState { Standing, Walking, Chasing, ReceivingDamage, Dying};
		MeleeEnemyState state, savedState;

		void playAnim(StandardEnemyAnimation anim, int speed, Direction dir);
		bool checkPlayerNear(Player* p, Enemy* e, int dist);
		int getDistance(int x1, int y1, int x2, int y2);
		bool moveInDir(Enemy* e, int speed);
		Direction getDifDir(Direction direc);

		bool resting;

		static const int turnRatio = 4;
		static const int searchDist = 50;
		static const int moveSpeed = 1;

	public:
		ComponentMeleeSimple(Game* game, Controller* cont);
		~ComponentMeleeSimple();
		
		void onCInit(Enemy* e);
		void onCStep(Enemy* e);
		void onCRender(Enemy* e){};
		virtual void onCTimer(Enemy* e, int timer);
		virtual void onCCollision(Enemy* enemy, CollisionPair other, Entity* e);
		virtual void onCDestroy(Enemy* e){};
		virtual void onCCustomEvent(Enemy* e, int event){};
		virtual void onCInitStep(Enemy* e){};
		virtual void onCEndStep(Enemy* e){};
		virtual void onCEndWorld(Enemy* e){};
};
#endif __ComponentMeleeSimple_H__
