#pragma once

#ifndef __TOOl_H__
#define __TOOL_H__

#include "Player.h"
#include "GameEntity.h"

class Tool: public GameEntity
{
protected:
	bool passive;	// true: herramienta pasiva, false: herramienta activa
	Player* player;		// Puntero al player

public:
	Tool(int x, int y, Game* game, GameState* world);
	~Tool();

	// inicia la herramienta
	void init(bool passive, Player* p);

	// getter de si la herramienta es pasiva o no
	bool isPassive() {return passive;};
	
	// acción a realizar cuando se active la herramienta
	virtual void activate() = 0;
	
};
#endif __TOOL_H__
