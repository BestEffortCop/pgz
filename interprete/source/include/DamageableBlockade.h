#pragma once

#ifndef __DAMAGEABLEBLOCKADE_H__
#define __DAMAGEABLEBLOCKADE_H__

#include "Entity.h"
#include "iDamageable.h"
#include "SpriteMap.h"

using namespace std;


class DamageableBlockade:public Entity, iDamageable
{
public:
	enum BlockadeAnim { Stand, Death };

	DamageableBlockade(int x, int y, Game* game, GameState* gameState);
	//Indica la debilidad ante la cual el bloque caerá
	void init(short typeWeakness,string gfxPath, int xColision, int yColision);
	void onDeath();

	bool loadAnimations(string fname);
	bool loadAnimation(BlockadeAnim anim, string name, FILE* from);

	//Metodo temporal, hay que esperar a fin de animación, no esto
	void onTimer(int n);

	//Metodo temporal, deberia avisar el arma a onDamage, no yo
	void onCollision(CollisionPair other, Entity* e);
};
#endif __DAMAGEABLEBLOCKADE_H__