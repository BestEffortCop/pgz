#pragma once

#ifndef __DAMAGEABLEBLOCKADE_H__
#define __DAMAGEABLEBLOCKADE_H__

#include "Entity.h"
#include "iDamageable.h"

using namespace std;


class DamageableBlockade:public Entity, iDamageable
{
public:
	DamageableBlockade(int x, int y, Game* game, GameState* gameState);
	//Indica la debilidad ante la cual el bloque caerá
	void init(short typeWeakness, Graphic* graphic, int xColision, int yColision);
	void onDeath();
	void onCollision(CollisionPair other, Entity* e);
};
#endif __DAMAGEABLEBLOCKADE_H__