#pragma once

#ifndef __I_DAMAGEABLE_H__
#define __I_DAMAGEABLE_H__

class iDamageable
{
	public:
		enum DamageTypes { PHYSICAL, MAGIC, PROJECTILE, FIRE, ICE, EARTH, ELECTRIC, DEATH };
		
		int hp;
		int maxHp;
		int defense;
		short typeWeakness;

		iDamageable();
		iDamageable(int hp, int maxHp, int defense, short typeWeakness);
		~iDamageable();

		virtual void onDeath();

		void init(int hp, int maxHp, int defense, short typeWeakness);
		void onDamage(int damage, short damageType);
};

#endif
