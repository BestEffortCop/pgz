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
#define ANY 256 


class iDamageable
{
	public:
		//enum DamageTypes { PHYSICAL, MAGIC, PROJECTILE, FIRE, ICE, EARTH, ELECTRIC, DEATH };
		
		int hp;
		int maxHp;
		int defense;
		short typeWeakness;

		iDamageable();
		iDamageable(int hp, int maxHp, int defense, short typeWeakness);
		~iDamageable();

		virtual void onDeath() = 0;

		void init(int hp, int maxHp, int defense, short typeWeakness);
		void onDamage(int damage, short damageType);
		void onHeal(int healtPoints);
};

#endif
