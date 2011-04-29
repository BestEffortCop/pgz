#pragma once

#ifndef __TOOLMELEE_H__
#define __TOOLMELEE_H__

#include "Tool.h"
#include "SpriteMap.h"
#include "HelperTypes.h"

#include "ToolController.h"

class ToolMelee : public Tool
{
private:

	// ------------------------------- ATRIBUTOS -----------------------------------


public:
	ToolMelee(int x, int y, Game* game, GameState* world);
	~ToolMelee();

	void activate();

	// La herramienta actúa en el momento en el que se crea
	void onInit();

	void init(bool passive, Player* p, int idTool, int damage, short damageType, std::string graphicpath);

	void onInitStep();
	void onEndStep();
	void onCollision(CollisionPair other, Entity* e);
	
};
#endif