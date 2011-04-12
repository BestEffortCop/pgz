#pragma once
#ifndef __TOOLSWORD_H__
#define __TOOLSWORD_H__

#include "Tool.h"
#include "SpriteMap.h"

class ToolSword : public Tool
{
private:
	//------------------------- Tipos auxiliares -----------------------------------------
	struct FrameData
	{
		int frameId;
		int hotspotX, hotspotY;
		int offsetX, offsetY, width, height; // datos de la máscara
	};

	struct SwordAnimData
	{
		int animSpeed;
		unsigned char numFrames;
		Direction dir;
		std::vector<FrameData> frameData;
	};

	//------------------------- Métodos auxiliares ---------------------------------------

	// Devuelve el nombre del fichero de configuración de una imagen
	string getConfigurationFileName(string fname);

	// Carga todas las animaciones de una imagen
	bool loadAnimations(string fname);

	// Carga una animación de la espada
	bool loadAnimation(Direction dir, string name, FILE* from);

	// Coge el identificador de un frame del archivo de configuración
	FrameData loadAnimationFrame(FILE* from);

	// Realiza la animación seleccionada
	bool playAnim(std::string name);

	// ----------------------------- Atributos ------------------------------------
	std::map<std::string, SwordAnimData> animList;

public:
	ToolSword(int x, int y, Game* game, GameState* world);
	~ToolSword();

	void init(bool passive, Player* p, string graphicpath, int ncol, int nrow);
	void activate();
	
};
#endif