#pragma once

#ifndef __COMPONENT_TACKLE_H__
#define __COMPONENT_TACKLE_H__

#include "Component.h"
#include "ComponentTiledMovement.h"

//class Enemy;

class ComponentTackle  :	public Component
{
protected:
	ComponentTiledMovement* tiledMov;
	enum TackleState { Stand, Move, Tackle, Charge, Rest };
	TackleState state;

public:
	ComponentTackle(Game* game, Controller* cont);
	virtual ~ComponentTackle();

	virtual void onCInit(Enemy* e);
	virtual void onCStep(Enemy* e);
	//virtual void onCRender(Enemy* e);
	virtual void onCTimer(Enemy* e, int timer);
	virtual void onCCollision(Enemy* enemy, CollisionPair other, Entity* e);
	virtual void onCDestroy(Enemy* e);
	virtual void onCCustomEvent(Enemy* e, int event);
	virtual void onCInitStep(Enemy* e);
	virtual void onCEndStep(Enemy* e);
	virtual void onCEndWorld(Enemy* e);

	void hitPlayer(Enemy* e, Player* p);

	void tackle(Enemy* e);
};

#endif