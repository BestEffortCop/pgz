/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameEntity.h"
#include "ComponentAnim.h"
#include "EnemyTool.h"
#include "Component.h"
//#include "iNotificable.h"
#include "ArenaEntity.h"
#include "DataBaseInterface.h"

#include <vector>

class EnemyTool;
class ComponentAnim;
class Component;
class ArenaEntity;

class Enemy : public GameEntity, public iDamageable
{
	public:
		enum EnemyDifficulty {EASY, NORMAL, DIFFICULT, HARD};

	private:
		vector<Component*>* components;
		iNotificable* toNotify;

	public:

		// STATIC INFO
			// Personal info
			EnemySpawnData spawnData;
			// General info (from DB)
			// maxHp from iDamageable
			// defense from iDamageable
			// typeWeakness from iDamageable
			int mpMax;
			int strength;
			EnemyDifficulty difficulty;

		// DYNAMIC INFO
			// hp from iDamageable
			int mp;
			Direction dir;
			bool dead;
			bool blinking;


		ArenaEntity* arena;

		ComponentAnim* cAnim;
		StandardEnemyAnimation currentAnim;

		void init(EnemySpawnData, vector<Component*>* components, ComponentAnim* cAnim, int hpMax, int mpMax, int strength, int defense, iNotificable* toNotify = NULL);

		void damagePlayer(Player* p, int damage, short damageType);
		std::vector<Component*>* getComponents();

		friend class Component;
		friend class EnemyTool;

		Enemy(Game* game, GameState* world);
		virtual ~Enemy();
		virtual void onInit();
		virtual void onStep();
		virtual void onRender();

		// Reservamos el timer 9 para uso único del enemy
		virtual void onTimer(int timer);

		virtual void onCollision(CollisionPair other, Entity* e);
		virtual void onDestroy();
		virtual void onCustomEvent(int event);
		virtual void onInitStep();
		virtual void onEndStep();
		virtual void onEndWorld();


		void onDamage(int damage, short damageType);
		void onHeal(int healthPoints);
		void onDeath();

		DataBaseInterface::ItemData getRandomItem();
};

#endif __ENEMY_H__
