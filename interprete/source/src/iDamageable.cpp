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

#include "iDamageable.h"

//Inicializa los valores por defecto, vida 2 defensa 0 debilidad todo.
iDamageable::iDamageable()
{
	init(2, 2, 0, 0xf);
}

iDamageable::iDamageable(int hp, int maxHp, int defense, short typeWeakness)
{
	init(hp,maxHp,defense,typeWeakness);
}

iDamageable::~iDamageable()
{
};

void iDamageable::init(int hp, int maxHp, int defense, short typeWeakness)
{
	this->hp = hp;
	this->maxHp = maxHp;
	this->defense = defense;
	this->typeWeakness = typeWeakness;
	lastHitDirection = NONE;
	invincible = false;
}

/*Comprueba si la entidad que implementa la interfaz es debil a ese tipo de daño y en caso
  afirmativo realiza el daño, a continuación si la vida es <= 0 llama a onDeath y pone la 
  vida a 0*/
void iDamageable::onDamage(int damage, short damageType)
{
	if (invincible)
		return;
	short aux = typeWeakness & damageType;
	if ((aux != 0x0) || (typeWeakness == ANY) || (damageType == ANY))
	{
		if(damage - defense > 0)
			hp = hp - (damage - defense);
		if (hp <= 0)
		{
			hp = 0;
			onDeath();
		}
	}
};

void iDamageable::onHeal(int healthPoints)
{
	if (hp + healthPoints > maxHp)
		hp = maxHp;
	else
		hp += healthPoints;
};

void iDamageable::setLastHitDirection(Direction dir)
{
	lastHitDirection = dir;
};

Direction iDamageable::getLastHitDirection()
{
	return lastHitDirection;
};

Direction iDamageable::computeHitDirection(Entity* a, Entity* b)
{
	if (a == NULL || b == NULL)
		return NONE;
	if (a != NULL && a->mask == NULL || b != NULL && b->mask == NULL)
		return NONE;
	
	Direction d;
	int ocx, ocy, mcx, mcy, vunit, hunit;

	mcx = a->x+a->mask->xoffset;
	mcy = a->y+a->mask->yoffset;

	ocx = b->x+b->mask->xoffset+(b->mask->width/2);
	ocy = b->y+b->mask->yoffset+(b->mask->height/2);

	vunit = a->mask->height/3;
	hunit = a->mask->width/3;

	if (ocx < mcx+hunit)
	{
		if (ocy < mcy+vunit) d = DOWNRIGHT;
		else if (ocy >= mcy+vunit && ocy < mcy+vunit*2) d = RIGHT;
		else d = UPRIGHT;
	}
	else if (ocx >= mcx+hunit && ocx < mcx+hunit*2)
	{
		if (ocy < mcy+vunit) d = DOWN;
		else if (ocy >= mcy+vunit && ocy < mcy+vunit*2) d = NONE;
		else d = UP;
	}
	else
	{
		if (ocy < mcy+vunit) d = DOWNLEFT;
		else if (ocy >= mcy+vunit && ocy < mcy+vunit*2) d = LEFT;
		else d = UPLEFT;
	}

	return d;
};

void iDamageable::setInvincible(bool inv)
{
	invincible = inv;
};

bool iDamageable::isInvincible()
{
	return invincible;
};