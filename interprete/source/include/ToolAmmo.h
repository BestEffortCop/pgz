#pragma once

#ifndef __TOOLAMMO_H__
#define __TOOLAMMO_H__

#include "Tool.h"
#include "SpriteMap.h"

class ToolAmmo : public Tool
{
private:
	// ------------------------------- Atributos ------------------------------------
	int speed;	// velocidad de la munici�n
	Direction dir;	// direcci�n en la que ha sido lanzada la munici�n

	// ---------------------------- M�todos auxiliares ----------------------------------
	bool loadConfig(std::string graphicpath, std::string fname);

public:
	ToolAmmo(int x, int y, Game* game, GameState* world);
	~ToolAmmo();

	void activate();

	// La herramienta act�a en el momento en el que se crea
	void onInit();

	void init(bool passive, Player* p, int idTool, int damage, short damageType, std::string graphicpath, Direction dir);

	// realizmos el movimiento de la munici�n
	void onStep();

	// Har� da�o (o no) y se destruir� en el momento en que colisione con algo
	void onCollision(CollisionPair other, Entity* e);

};

#endif