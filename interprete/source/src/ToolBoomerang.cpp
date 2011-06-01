/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "ToolBoomerang.h"

ToolBoomerang::ToolBoomerang(int x, int y, Game* game, GameState* world) : Tool(x, y, game, world) {}

ToolBoomerang::~ToolBoomerang() 
{
	// Si esta volando por ahi nos lo cargamos, si no ya lo hace ToolController
	if(launched)
		player->getController()->getToolController()->toolFinished(idTool, false);
}

void ToolBoomerang::init(bool passive, Player* p, int idTool, int damage, short damageType, std::string graphicpath)
{
	Tool::init(passive, p, idTool, damage, damageType);		// init del padre

	range = 15;
	launched = false;
	type = "tool";
	player = p;

	// Cargar imagen del boomerang
	graphic = new Stamp(graphicpath, game->getGfxEngine());

	loadConfig(graphicpath, getConfigurationFileName(graphicpath));

	// Colocarla munición en función del arma que nos ha creado (acordarse de ajustar profundidad)
	depth = y;
}

bool ToolBoomerang::loadConfig(std::string graphicpath, std::string fname)
{
	// Carga el archivo de config y lee
	FILE* f = fopen(fname.c_str(), "rb");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	// 1. velocidad de la munición
	if (fscanf(f, "%d", &speed) < 1)
		return false;

	// 2. Ancho y alto de imagen
	int nCols, nRows;
	if (fscanf(f, "%d %d", &nCols, &nRows) < 2)
		return false;

	// creamos el gráfico del boomerang
	graphic = new SpriteMap(graphicpath, nCols, nRows, game->getGfxEngine());

	// 2. Leer las animaciones
	loadAnimation(UP, "up", f);
	loadAnimation(DOWN, "down", f);
	loadAnimation(LEFT, "left", f);
	loadAnimation(RIGHT, "right", f);

	fclose(f);

	return true;
}



void ToolBoomerang::onInit()
{
	if (player->changeState(Player::Attack))
		activate();

	else 
		// hay que avisar a toolController de que no se puede atacar
		player->getController()->getToolController()->toolFinished(idTool);
}

void ToolBoomerang::activate()
{
	if (!launched)
	{
		dir = player->dir;
		std::string name;
		ToolAnimData data;

		// Ejecutamos la animación correspondiente en función de la dirección a la que nos lanzan
		switch(dir){
		case UP:
			name = "up";
			break;
		case DOWN:
			name = "down";
			break;
		case LEFT:
			name = "left";
			break;
		case UPLEFT:
			name = "left";
			break;
		case DOWNLEFT:
			name = "left";
			break;
		case RIGHT:
			name = "right";
			break;
		case UPRIGHT:
			name = "right";
			break;
		case DOWNRIGHT:
			name = "right";
			break;
		}

		data = animList.at(name);						// cogemos los datos de la animación
		if(graphic != NULL) ((SpriteMap*) graphic)->playAnim(name, data.animSpeed, true, false);	// ejecutamos la animación

		if (mask != NULL) delete mask; // borramos la antigua
		mask = new MaskBox(x, y, data.frameData[0].width, data.frameData[0].height, type, 0, 0); // creamos la nueva en la posición actual
		
		setTimer(1, range); // Inicializamos el timer de la distancia que recorrerá
		launched = true;
	}
}

void ToolBoomerang::onStep()
{
	if(launched){
		move();
		player->changeState(Player::Normal);
	}
	/*
	// Comprobamos que no se sale de la pantalla
	if (player->getController()->getScreenMap()->isInBounds(this))
	{
		x = xtmp; y = ytmp;

		// Actualizamos la máscara
		if (mask != NULL) delete mask; // borramos la antigua
		mask = new MaskBox(x, y, data.frameData[0].width, data.frameData[0].height, type, 0, 0); // creamos la nueva en la posición actual

		// Actualizamos la profundidad del gráfico
		depth = y;
	}
	else	// si se sale del borde matamos la munición
		instance_destroy();
	*/
}

void ToolBoomerang::move()
{
	int xtmp = x;
	int ytmp = y;
	ToolAnimData data;

	// Si aun no estamos volviendo al player
	if (getTimer(1) > 0)
	{
		// Movimiento de la munición en función de la dirección y de la velocidad
		switch (dir)
		{
		case UP:
			ytmp -= speed;
			data = animList.at("up");
			break;
		case DOWN:
			ytmp += speed;
			data = animList.at("down");
			break;
		case LEFT:
			xtmp -= speed;
			data = animList.at("left");
			break;
		case RIGHT:
			xtmp += speed;
			data = animList.at("right");
			break;
		}

		x = xtmp; y = ytmp;

		// Actualizamos la máscara
		if (mask != NULL) delete mask; // borramos la antigua
		mask = new MaskBox(x, y, data.frameData[0].width, data.frameData[0].height, type, 0, 0); // creamos la nueva en la posición actual

		// Actualizamos la profundidad del gráfico
		depth = y;
	}
	// volviendo a player
	else
	{
		xtmp = player->x;
		ytmp = player->y;

		// Si hemos vuelto al player
		if (abs(x - xtmp)<10 && abs(y - ytmp)<10) // Estaria mejor coger player->mask/2, pero lo dejo asi por ahora
		{
			launched = false;
			player->getController()->getToolController()->toolFinished(idTool);

		}
		// Si no, volvemos al player
		else 
		{
			if (x != xtmp)
				(x > xtmp) ? x -= 3 : x += 3;
			if (y != ytmp)
				(y > ytmp) ? y -= 3 : y += 3;
		}
	}
}

void ToolBoomerang::onCollision(CollisionPair other, Entity* e)
{
	if (other.b == "tool") return;

	if (Tool::doDamage(other, e, dir))		// hacemos daño
	{
		Tool::animOnCollision(other, e);	// Animación a realizar al golpear con algo
		//instance_destroy();					// una vez hecho daño nos destruimos
	}
};

void ToolBoomerang::onDestroy()
{
	// Si esta volando por ahi nos lo cargamos, si no ya lo hace ToolController
	if(launched)
		player->getController()->getToolController()->toolFinished(idTool, false);
};