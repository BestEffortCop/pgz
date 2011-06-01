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
		enum MeleeEnemyState { Standing, Walking, Chasing, ReceivingDamage};
		MeleeEnemyState state;

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
