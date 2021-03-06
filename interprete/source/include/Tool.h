/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef __TOOl_H__
#define __TOOL_H__

#include "Player.h"

#include "ToolController.h"

class Tool: public GameEntity
{
protected:

	//------------------------- Tipos auxiliares -----------------------------------------

	struct FrameData
	{
		int frameId;
		int hotspotX, hotspotY;
		int offsetX, offsetY, width, height; // datos de la m�scara
	};

	struct ToolAnimData
	{
		int animSpeed;
		unsigned char numFrames;
		Direction dir;
		std::vector<FrameData> frameData;
	};

	// --------------------------- Atributos --------------------------------------

	int idTool;		// Identificadr de la herramienta
	bool passive;	// true: herramienta pasiva, false: herramienta activa
	Player* player;		// Puntero al player
	Player::PlayerAnim playeranim; // animaci�n que tendr� que ejecutar el player cuando se use la herramienta
	int damage;			// da�o de la herramienta
	short damageType;	// tipo del da�o de la herramienta
	std::map<std::string, ToolAnimData> animList;  // mapa que guarda la informaci�n de cada animaci�n

	// --------------------- M�todos de auxiliares ----------------------------

	// Carga todas las animaciones de una imagen
	/*	graphicpath: ruta de la imagen
		fname: fichero de configuraci�n de la imagen */
	bool loadAnimations(std::string graphicpath, std::string fname);

	// Carga una animaci�n de la herramienta (si es una herramienta animada)
	bool loadAnimation(Direction dir, std::string name, FILE* from);

	// Coge el identificador de un frame del archivo de configuraci�n
	FrameData loadAnimationFrame(FILE* from);

	// Devuelve el nombre del fichero de configuraci�n de una imagen
	std::string getConfigurationFileName(std::string fname);

	// Realiza la animaci�n seleccionada
	bool playAnim(std::string name);

	/* Coloca la herramienta en el sitio indicado teniendo en cuenta el hotspot actual del player,
	y el frame actual de la animaci�n */
	virtual void placeTool();

	// Realiza da�o al objeto con el que se ha colisionado
	bool doDamage(CollisionPair other, Entity* e, Direction dir);

	// Animaci�n que debe hacer cuando colisione
	virtual void animOnCollision(CollisionPair other, Entity* e){};

public:

	Tool(int x, int y, Game* game, GameState* world);
	~Tool();

	// inicia la herramienta
	void init(bool passive, Player* p, int idTool, int damage, short damageType);

	// getter de si la herramienta es pasiva o no
	bool isPassive();

	// Indica si ha acabado la animaci�n de la herramienta
	bool animFinished();

	// acci�n a realizar cuando se active la herramienta
	virtual void activate() = 0;
	
};
#endif
