#include "Enemy.h"


Enemy::Enemy(int x, int y, Game* game, GameState* world, vector<Component*>* components):GameEntity(x,y,game,world)
{
	this->components = components;
	dead = false;
	currentAnim = NOTHING;
	cAnim = NULL;
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

void Enemy::init(ComponentAnim* cAnim, int hpMax, int mpMax, int strength, int defense, iNotificable* toNoty){
	this->hpMax = hpMax;
	this->mpMax = mpMax;
	this->strength = strength;
	this->defence = defence;
	this->cAnim = cAnim;
	toNotify = toNoty;
};

void Enemy::onInit()
{
	iDamageable::init(hpMax, hpMax, 1, 0xFF);
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

	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCStep(this);
	}
};

void Enemy::onRender()
{


	if (cAnim != NULL)
		cAnim->onCRender();

	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCRender(this);
	}
};

void Enemy::onTimer(int timer)
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCTimer(this, timer);
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
	if (dead && toNotify != NULL)
		toNotify->onNotified(this);
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

void Enemy::setLastDmgDirection(Direction dir)
{
	lastEnemyDirection = dir;
};

Direction Enemy::getLastDmgDirection()
{
	return lastEnemyDirection;
};

void Enemy::onDamage(int damage, short damageType)
{
	iDamageable::onDamage(damage, damageType);
};

void Enemy::onDeath()
{
	dead = true;
};

std::vector<Component*>* Enemy::getComponents()
{
	return components;
};