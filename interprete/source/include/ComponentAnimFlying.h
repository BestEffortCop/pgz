#pragma once

#ifndef __COMPONENTANIMFLYING_H__
#define __COMPONENTANIMFLYING_H__


#include "ComponentAnim.h"

class ComponentAnimFlying :	public ComponentAnim
{
protected:

	int height;
	float period;
	int amplitude;
	int phase;

public:
	ComponentAnimFlying(Game* game, Enemy* e, std::string gfxPath);
	~ComponentAnimFlying();

	void init(int height, float period, int amplitude, int phase);

	void onCInit();
	void onCStep();
	void onCRender();
	void onCTimer(int timer);
};

#endif