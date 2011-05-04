#pragma once

#ifndef __TOOLAMMO_H__
#define __TOOLAMMO_H__

#include "SpriteMap.h"
#include "Tool.h"

class Tool;

// ALEJANDROOOOOOOOOOOOOOOOOOOOOOOOOO

// ACUÉRDATE DE HACER LA MASCARA ANTES DE NADAAAAAAAAAA QUE SINO PETA EL IS INBOUNDS!!!!



class ToolAmmo : public Tool
{
private:
	// ------------------------------- Atributos ------------------------------------
	int speed;	// velocidad de la munición
	Direction dir;	// dirección en la que ha sido lanzada la munición

	// ---------------------------- Métodos auxiliares ----------------------------------
	bool loadConfig(std::string graphicpath, std::string fname);

public:
	ToolAmmo(int x, int y, Game* game, GameState* world);
	~ToolAmmo();

	virtual void activate();

	// La herramienta actúa en el momento en el que se crea
	void onInit();

	virtual void init(bool passive, Player* p, int idTool, int damage, short damageType, std::string graphicpath, Direction dir);

	// realizmos el movimiento de la munición
	virtual void onStep();

	// Hará daño (o no) y se destruirá en el momento en que colisione con algo
	virtual void onCollision(CollisionPair other, Entity* e);
};

#endif