#pragma once
#ifndef __HUD_H__
#define __HUD_H__

#include "Entity.h"


class HUD : public Entity {

	public:
		// CONSTRUCORES Y DESTRUCTORES
		HUD(int x, int y, Game* g, GameState* gs);
		~HUD();
};


#endif