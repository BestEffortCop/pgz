#pragma once

#ifndef __COMPONENTMELEE_H__
#define __COMPONENTMELEE_H__

#include "Enemy.h"
#include "Stamp.h"
#include "HelperTypes.h"
#include "iDamageable.h"

class Enemy;

class ComponentMelee : public Component, public iDamageable
{
	private:
		Direction dir;
		Direction lastEnemyDirection;
		enum EnemyState { Normal, Attacking, Damaged, Dead };
		enum EnemyAction { aWalk, aAttack, aDamaged };
		enum EnemyAnim { Walk, Attack, Hit };
		EnemyState state;
		EnemyAction currentAction;
		EnemyAnim currentAnim;
		
		bool dead;

		//HP PROVISIONAL
		static const int hpProv = 20;

	public:
		ComponentMelee(Game* game, Controller* cont );
		~ComponentMelee(){};
		
		void onCInit(Enemy* e);
		void onCStep(Enemy* e);
		void onCRender(Enemy* e);
		virtual void onCTimer(Enemy* e, int timer);
		virtual void onCCollision(Enemy* enemy, CollisionPair other, Entity* e);
		virtual void onCDestroy(Enemy* e){};
		virtual void onCCustomEvent(Enemy* e, int event){};
		virtual void onCInitStep(Enemy* e){};
		virtual void onCEndStep(Enemy* e){};
		virtual void onCEndWorld(Enemy* e){};

		void onDeath();
};
#endif __COMPONENTMELEE_H__
