#pragma once

#ifndef __TOOLAMMO_H__
#define __TOOLAMMO_H__

#include "Tool.h"

class ToolAmmo : public Tool
{
private:
	// ------------------------------- Atributos ------------------------------------
	int speed;	// velocidad de la munición
	Direction dir;	// dirección en la que ha sido lanzada la munición
	int width;		// ancho de la munición (máscara)
	int height;		// alto de la munición (máscara)

	// ---------------------------- Métodos auxiliares ----------------------------------
	bool loadConfig(std::string graphicpath, std::string fname);

public:
	ToolAmmo(int x, int y, Game* game, GameState* world);
	~ToolAmmo();

	void activate();

	// La herramienta actúa en el momento en el que se crea
	void onInit();

	void init(bool passive, Player* p, int idTool, std::string graphicpath, Direction dir);

	// realizmos el movimiento de la munición
	void onStep();

	// Hará daño (o no) y se destruirá en el momento en que colisione con algo
	void onCollision(){};

};

#endif