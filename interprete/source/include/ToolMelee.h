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
//	ToolController* toolcontroller;

	// Carga todas las animaciones de una imagen
	/*	graphicpath: ruta de la imagen
		fname: fichero de configuración de la imagen */
	bool loadAnimations(std::string graphicpath, std::string fname);

public:
	ToolMelee(int x, int y, Game* game, GameState* world);
	~ToolMelee();

	void activate();

	// La herramienta actúa en el momento en el que se crea
	void onInit();

	void init(bool passive, Player* p, Player::PlayerAnim playeranim, int idTool, std::string graphicpath);

	void onInitStep();
	void onRender();
	void onEndStep();
	void onCollision();
	
};
#endif