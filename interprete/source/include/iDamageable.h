/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef __I_DAMAGEABLE_H__
#define __I_DAMAGEABLE_H__

#define PHYSICAL 1
#define MAGIC 2
#define PROJECTILE 4
#define FIRE 8
#define ICE 16
#define EARTH 32
#define ELECTRIC 64
#define DEATH 128
#define ANY 255 

#include "HelperTypes.h"
#include "Entity.h"

class iDamageable
{
	protected:
		Direction lastHitDirection;
	public:
		//enum DamageTypes { PHYSICAL, MAGIC, PROJECTILE, FIRE, ICE, EARTH, ELECTRIC, DEATH };
		
		int hp;
		int maxHp;
		int defense;
		bool invincible;
		short typeWeakness;

		iDamageable();
		iDamageable(int hp, int maxHp, int defense, short typeWeakness);
		~iDamageable();

		virtual void onDeath() = 0;

		virtual void init(int hp, int maxHp, int defense, short typeWeakness);
		virtual void onDamage(int damage, short damageType);
		virtual void onHeal(int healthPoints);
		void setLastHitDirection(Direction dir);
		Direction getLastHitDirection();
		Direction computeHitDirection(Entity* hazard, Entity* damaged);
		virtual void setInvincible(bool inv);
		virtual bool isInvincible();
};

#endif
