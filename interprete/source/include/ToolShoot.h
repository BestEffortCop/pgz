#pragma once

#ifndef __TOOLSHOOT_H__
#define __TOOLSHOOT_H__

//#include "Tool.h"
#include "ToolController.h"
#include "ToolAmmo.h"

class ToolShoot : public Tool
{
private:
	// Carga todas las animaciones de una imagen
	/*	graphicpath: ruta de la imagen
		fname: fichero de configuración de la imagen */
	bool loadAnimations(std::string graphicpath, std::string fname);

	// Munición de la herramienta de disparo
	ToolAmmo* ammo;

public:
	ToolShoot(int x, int y, Game* game, GameState* world);
	~ToolShoot();

	void activate();

	// La herramienta actúa en el momento en el que se crea
	void onInit();

	void init(bool passive, Player* p, Player::PlayerAnim playeranim, int idTool, std::string graphicpath);

	void onInitStep();
	void onRender(){};
	void onEndStep();

};

#endif