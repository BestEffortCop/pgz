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

#include "Enemy.h"
#include "GameItem.h"

Enemy::Enemy(Game* game, GameState* world):GameEntity(-1,-1,game,world), iDamageable()
{
	// POSSIBLE DEBRIS
	currentAnim = NOTHING;
	cAnim = NULL;

	arena = NULL;
}

Enemy::~Enemy()
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); it++) 
	{
		delete (*it);
		(*it) = NULL;
	}
	delete components;
	components = NULL;

	if (cAnim != NULL)
		delete cAnim;
	cAnim = NULL;
};

void Enemy::init(EnemySpawnData spawnData, vector<Component*>* components, ComponentAnim* cAnim, int hpMax, int mpMax, int strength, int defense, iNotificable* toNoty){
	
	this->spawnData.x = this->x = spawnData.x;
	this->spawnData.y = this->y = spawnData.y;
	this->spawnData.id = spawnData.id;
		
	this->maxHp = hpMax;
	this->mpMax = mpMax;
	this->strength = strength;
	this->defense = defense;

	this->components = components;

	iDamageable::init(maxHp, maxHp, defense, typeWeakness);
	dead = false;
	blinking = false;

	// POSSIBLE DEBRIS
	this->cAnim = cAnim;
	toNotify = toNoty;

	if (mask != NULL)
		depth = y + mask->yoffset;
	else
		depth = y;
};

void Enemy::onInit()
{
	if (cAnim != NULL)
		cAnim->onCInit();
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCInit(this);
	}
};

void Enemy::onStep()
{
	if (GameEntity::isPaused())
		return;

	if (cAnim != NULL)
		cAnim->onCStep();

	if (blinking && graphic != NULL)
	{
		graphic->setAlpha((getTimer(9) % 2));
	}

	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCStep(this);
	}

	if (mask != NULL)
		depth = y + mask->yoffset;
	else
		depth = y;
};

void Enemy::onRender()
{
	/* Render de la sombra en la posición correcta */
	Graphic* g = graphic;
	graphic = NULL;
	if (visible && enabled)
		GameEntity::onRender();
	graphic = g;

	/* Render del gráfico elevado si hace falta */
	if (cAnim != NULL)
		cAnim->onCRender();

	/* Dejamos que los componentes lo gocen */
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCRender(this);
	}
};

void Enemy::onTimer(int timer)
{
	cAnim->onCTimer(timer);

	if (timer == 9)
	{
		blinking = false;
		graphic->setAlpha(1.f);
	}
	else
	{
		for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
		{
			(*it)->onCTimer(this, timer);
		}
	}
};

void Enemy::onCollision(CollisionPair other, Entity* e)
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCCollision(this, other, e);
	}
};

void Enemy::onDestroy()
{
	if (dead)
	{
		if (rand()%20 > 1)
		{
			DataBaseInterface* dbi = ((PGZGame*) game)->controller->getDataBaseInterface();
			DataBaseInterface::ItemData idata = getRandomItem();
			if (idata.gfxId != -1)
			{
				GameItem* gi = new GameItem(x, y, game, world);
				world->add(gi);
				gi->init(dbi->getImagePath(idata.gfxId), (GameItem::ItemType) idata.effect, idata.power);
			}
			else
				int n = 2;
		}
	}

	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCDestroy(this);
	}
};

void Enemy::onCustomEvent(int event)
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCCustomEvent(this, event);
	}
};

void Enemy::onInitStep()
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCInitStep(this);
	}
};

void Enemy::onEndStep()
{
	depth = y-cAnim->getHeight();

	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCEndStep(this);
	}
};

void Enemy::onEndWorld()
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCEndWorld(this);
	}
};

std::vector<Component*>* Enemy::getComponents()
{
	return components;
};

void Enemy::damagePlayer(Player* p, int damage, short damageType)
{
	p->setLastHitDirection(p->computeHitDirection(this, p));
	p->onDamage(damage, damageType);
};

void Enemy::onDamage(int damage, short damageType)
{
	iDamageable::onDamage(damage, damageType);
	blinking = true;
	setTimer(9, 30);
}
void Enemy::onHeal(int healthPoints)
{
	iDamageable::onHeal(healthPoints);
}

void Enemy::onDeath()
{
	dead = true;
	instance_destroy();
}



/*
void Enemy::setLastDmgDirection(Direction dir)
{
	lastEnemyDirection = dir;
};

Direction Enemy::getLastDmgDirection()
{
	return lastEnemyDirection;
};
*/

/*
OLD SHIT

void Enemy::onDamage(int damage, short damageType)
{
	iDamageable::onDamage(damage, damageType);
};

void Enemy::onDeath()
{
	dead = true;
};
*/

DataBaseInterface::ItemData Enemy::getRandomItem()
{
	// Devuelve un item no llave ni cosas
	int tries = 5; // En honor a pferv, nº de intentos
	bool valid = false;
	DataBaseInterface* dbi = ((PGZGame*) game)->controller->getDataBaseInterface();
	GameStatus* status = ((PGZGame*) game)->controller->getData()->getGameData()->getGameStatus();
	DataBaseInterface::ItemData data;
	data.idItem = -1;
	data.gfxId = -1;
	data.effect = -1;
	data.power = -1;
	DataBaseInterface::ToolData tdata;
	if (rand()%2 == 0)
	{
		tries = 100;
		valid = false;
		while (tries > 0 && !valid)
		{
			tdata = dbi->getToolData(dbi->getToolAtPosition(rand()%dbi->getToolNumber()));
			valid = ((tdata.gfxAmmo != -1) && (status->isToolAvailable(tdata.idTool)));
			tries--;
		}
		if (valid)
		{
			data.gfxId = tdata.gfxAmmo;
			data.name = "Ammo";
			data.effect = GameItem::ieTOOLAMMO;
		}
	}
	else
	{
		while (tries > 0 && !valid)
		{
			data = dbi->getItemData(dbi->getItemAtPosition(rand()%dbi->getItemNumber()));
			valid |= ((data.effect == GameItem::ieHP) || (data.effect == GameItem::ieMONEY));
			tries--;
		}
	}

	return data;
}