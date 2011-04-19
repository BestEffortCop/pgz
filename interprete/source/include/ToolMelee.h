#pragma once

#ifndef __TOOLMELEE_H__
#define __TOOLMELEE_H__

#include "Tool.h"
#include "SpriteMap.h"
#include "HelperTypes.h"

class ToolMelee : public Tool
{
private:

	// -------------------------------------- Atributos ---------------------------------------
	Player::PlayerAnim playeranim; // animación que tendrá que ejecutar el player cuando se use la herramienta

	// Carga todas las animaciones de una imagen
	bool loadAnimations(std::string fname);

public:
	ToolMelee(int x, int y, Game* game, GameState* world);
	~ToolMelee();

	// La herramienta actúa en el momento en el que se crea
	void onInit();

	void init(bool passive, Player* p, Player::PlayerAnim playeranim, std::string graphicpath, int ncol, int nrow);
	void activate();

	void onRender();
	void onStep();
	void onCollision();
	
};
#endif