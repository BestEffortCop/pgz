#pragma once

#ifndef __COMPONENTRANGED_H__
#define __COMPONENTRANGED_H__

#include "Enemy.h"
#include "Stamp.h"
#include "HelperTypes.h"
#include "iDamageable.h"
#include "EnemyTool.h"
#include <cmath>

class Enemy;

class ComponentRanged : public Component
{
	private:
		enum MeleeEnemyState { Standing, Walking, Attacking, ReceivingDamage};
		MeleeEnemyState state;

		void playAnim(StandardEnemyAnimation anim, int speed, Direction dir);
		bool checkPlayerNear(Player* p, Enemy* e, int dist, Direction & dir);
		int getDistance(int x1, int y1, int x2, int y2);
		bool moveInDir(Enemy* e, int speed);
		Direction getDifDir(Direction direc);

		bool resting;

		//TODO Estos podremos cambiarlos en el CInit en funcion de la dificultad del enemigo
		static const int turnRatio = 4;
		static const int searchDist = 50;
		static const int moveSpeed = 1; //ovejita que te pillo
		EnemyTool* eToolKameha;

		//HP PROVISIONAL
		static const int hpProv = 20;

	public:
		ComponentRanged(Game* game, Controller* cont);
		~ComponentRanged();
		
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
#endif __ComponentRanged_H__
