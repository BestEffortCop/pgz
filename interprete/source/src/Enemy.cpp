#include "Enemy.h"


Enemy::Enemy(int x, int y, Game* game, GameState* world, vector<Component*>* components):GameEntity(x,y,game,world)
{
	this->components = components;
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
}

void Enemy::init(std::string gfxPath, int hpMax, int mpMax, int strength, int defense){
	this->gfxPath = gfxPath;
	this->hpMax = hpMax;
	this->mpMax = mpMax;
	this->strength = strength;
	this->defence = defence;
	this->inAnim = false;
}

void Enemy::onInit()
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCInit(this);
	}
}

void Enemy::onStep()
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCStep(this);
	}
}

void Enemy::onRender()
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCRender(this);
	}
}

void Enemy::onTimer(int timer)
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCTimer(this, timer);
	}
}

void Enemy::onCollision(CollisionPair other, Entity* e)
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCCollision(this, other, e);
	}
}

void Enemy::onDestroy()
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCDestroy(this);
	}
}

void Enemy::onCustomEvent(int event)
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCCustomEvent(this, event);
	}
}

void Enemy::onInitStep()
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCInitStep(this);
	}
}

void Enemy::onEndStep()
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCEndStep(this);
	}
}

void Enemy::onEndWorld()
{
	for (vector<Component*>::iterator it = components->begin(); it != components->end(); ++it) 
	{
		(*it)->onCEndWorld(this);
	}
}