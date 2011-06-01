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

#include "ToolController.h"

#include "ToolMelee.h"
#include "ToolShoot.h"
#include "ToolAmmo.h"
#include "ToolBoomerang.h"

ToolController::ToolController(Controller* controller)
{
	this->controller = controller;

	// creamos una información de herramienta vacía
	ToolData td = createToolData(-1);

	// metemos herramientas vacías en todas las posibles teclas para equipar
	for (int i=0; i<MAX_EQUIPPED_TOOLS; i++)
		equippedTools[i] = -1;
}

ToolController::~ToolController()
{
	std::map<int, ToolData>::iterator it;
	// borramos las herramientas que no hayan sido borradas todavía
	for (it = tools.begin(); it != tools.end(); it++)
		if (it->second.tool != NULL)
			it->second.tool->instance_destroy();
}

void ToolController::init(std::vector<int> tools)
{
	// añadimos las herramientas del vector como parámetro, de momento las ponemos como no equipables
	ToolData td;
	for (int i = 0; i < (int) tools.size(); i++)
	{
		td = createToolData(tools[i]);
		this->tools.insert(make_pair(tools[i], td));
	}
}

// de momento preparado sólo para un player (habrá que tener más listas para más players)
// key indica lo mismo que en attack
bool ToolController::equip(int idTool, Player* player, short slot){

/*

	1. Modificar la info del player correspondiente a las tools con la nueva.
	2. Instanciar la tool si es necesario (activa de efecto pasivo)

	3. Comprobando siempre el estado de la misma (si está usándose por otro player no se podrá equipar).

*/
	// De momento no se consideran herramientas pasivas

	// comprobamos que se puede equipar la herramienta en el slot solicitado
	if (slot < 0 || slot >= MAX_EQUIPPED_TOOLS) return false;

	// comprobamos que se pueda equipar la herramienta pedida
	map<int, ToolData>::iterator it = tools.find(idTool);
	if (it == tools.end())	// no existe la herramienta
		return false;
	else
		if (!it->second.equippable)	// existe pero no es equipable
			return false;

	if (equippedTools[slot] != -1) // hay algo equipado ya en ese slot
	{
		// si la herramienta actual está en uso no se puede equipar
		if (tools.at(equippedTools[slot]).inUse) return false;
	
		// Desequipamos la actual
		if (tools.at(equippedTools[slot]).tool != NULL) tools.at(equippedTools[slot]).tool->instance_destroy();
	}
	
	// si no hay nada equipado lo equipamos directamente
	equippedTools[slot] = idTool;	// equipamos la herramienta nueva
	return true;
}


void ToolController::attack(Player* player, short slot){
	
/* ---------------------------------------------------------------------
	1. Interactuar si es necesario:
		1.1. obtener la posición frente al player
--------------------------------------------------------------------- */
			
	// Coordenadas del objeto frente al player
	int nx, ny;
	int up, left;
	up = left = 0;

	switch (player->getDir()) 
	{
		case UP: up = -1; break;
		case DOWN: up = 1; break;
		case LEFT:  left = -1; break;
		case RIGHT:  left = 1; break;
	}

	nx = (player->x) + left * D_INTERACT;
	ny = (player->y) + up * D_INTERACT;

/* ---------------------------------------------------------------------
		1.2. Si el objeto es interactable, interactuar con él
--------------------------------------------------------------------- */
			
	// Objeto frente al player
	Entity* e = player->world->place_meeting(nx, ny, player, "npc");
				
	if (e != NULL)
	{
		// si es un objeto con el se puede interactuar, se hará lo propio
		if (iInteractable* i = dynamic_cast<iInteractable*>(e))
			i->onInteract(player);
	}
				
/* ---------------------------------------------------------------------
	2. Si no tiene con quién interactuar, efectúa la acción 
	de la herramienta.
---------------------------------------------------------------------*/
		
	else
	{
        // comprobamos que existe el slot soloicitado
		if (slot >= 0 && slot < MAX_EQUIPPED_TOOLS)
			toolAttack(slot, player);	// atacamos con la herramienta seleccionada
	}
}

ToolController::ToolData ToolController::createToolData(int idTool)
{
	// De momento creamos una información de herramienta vacía
	ToolController::ToolData td;
	td.ammo = -1;
	td.ammoGfxpath = "";
	td.damageType = 1;
	td.equippable = false;
	td.gfxPath = "";
	td.idTool = -1;
	td.inUse = false;
	td.maxAmmo = -1;
	td.strength = -1;
	td.tool = NULL;
	td.type = none;
	td.usable = false;

	// Si no existe el identificador lo devolvemos vacío
	if (idTool == -1) return td;
	else	// Devolvemos la información dada por la base de datos
	{
		// td = DameDatosDBi(idTool)!!!!; return td; (cuando la base de datos esté lista)
		// mientras tanto....
		/*if (idTool == 1)	// Espada slash
		{
			td.damageType = PHYSICAL;
			td.gfxPath = "data/graphics/weapon-slashsword.png"; // habrá que cogerlo de la base de datos
			td.idTool = idTool;
			td.name = "Slash Sword";
			td.strength = 3;
			td.usable = true;
			td.type = tool_Melee;
		}
		else if (idTool == 2) // Boomerang
		{
			td.damageType = PHYSICAL;
			td.gfxPath = "data/graphics/weapon-boomerang.png";	// habrá que cogerlo de la base de datos
			td.idTool = idTool;
			td.name = "Boomerang";
			td.strength = 3;
			td.usable = true;
			td.type = tool_Boomerang;
		}
		else if (idTool == 3)	// arco
		{
			td.ammo = 100;
			td.maxAmmo = 100;

			td.ammoGfxpath =  "data/graphics/arrow.png";
			td.gfxPath = "data/graphics/weapon-arc.png";	// habrá que cogerlo de la base de datos
			td.idTool = idTool;
			td.name = "Bow";
			td.strength = 3;
			td.usable = true;
			td.type = tool_Shoot;
		}
		else if (idTool == 4){ // bastón mágico

			td.ammo = 100;
			td.maxAmmo = 100;

			td.ammoGfxpath =  "data/graphics/fireBall.png";
			td.gfxPath = "data/graphics/magicStick.png";	// habrá que cogerlo de la base de datos
			td.idTool = idTool;
			td.name = "Wand";
			td.strength = 3;
			td.usable = true;
			td.type = tool_Shoot;
			td.damageType = MAGIC;
		}*/

		// POR FIN COGEMOS LAS COSAS DE LA BASE DE DATOSSSSSSSS
		DataBaseInterface::ToolData database_td;
		database_td = controller->getDataBaseInterface()->getToolData(idTool); // si existe en la base de datos
		td.type = (ToolType) database_td.type;
		td.damageType = database_td.dmgType;
		td.strength = database_td.strength;
		td.idTool = idTool;
		td.name = database_td.nombre;
		td.gfxPath = controller->getDataBaseInterface()->getImagePath(database_td.gfxId);
		if (database_td.dmgType != -1)
		{
			td.ammoGfxpath = controller->getDataBaseInterface()->getImagePath(database_td.gfxAmmo);
			td.ammo = database_td.gfxAmmo;
			td.maxAmmo = database_td.maxAmmo;
		}
		return td;
	}
}

void ToolController::toolAttack(short slot, Player* player)
{
	Tool* t = NULL;
	if (equippedTools[slot] < 0)
		return;
	// realizamos la acción correspondiente dependiendo del tipo del arma
	switch(tools.at(equippedTools[slot]).type)
	{
	case tool_Melee:
		if (tools.at(equippedTools[slot]).usable) // si la podemos usar
		{
			// creamos la herramienta correspondiente y la iniciamos
			t = new ToolMelee(player->x, player->y, controller->game, controller->game->getGameState());
			((ToolMelee*) t)->init(false, player, tools.at(equippedTools[slot]).idTool, tools.at(equippedTools[slot]).strength,
				tools.at(equippedTools[slot]).damageType, tools.at(equippedTools[slot]).gfxPath);
		}
		break;
	case tool_Shoot:
	{
		// buscamos la herramienta en el mapa (para modificar su munición)
		std::map<int, ToolData>::iterator it = tools.find(equippedTools[slot]);
		if (tools.at(equippedTools[slot]).usable && it->second.ammo > 0)
		{
			// decrementamos la munición del arma
			it->second.ammo--;

			// creamos la herramienta y la iniciamos
			t = new ToolShoot(player->x, player->y, controller->game, controller->game->getGameState());
			((ToolShoot*) t)->init(false, player, tools.at(equippedTools[slot]).idTool, tools.at(equippedTools[slot]).strength,
				tools.at(equippedTools[slot]).damageType, tools.at(equippedTools[slot]).gfxPath, tools.at(equippedTools[slot]).ammoGfxpath);
		}
		break;
	}
	case tool_Boomerang:
		if (tools.at(equippedTools[slot]).usable) // si la podemos usar
		{
			// creamos la herramienta correspondiente y la iniciamos
			t = new ToolBoomerang(player->x, player->y, controller->game, controller->game->getGameState());
			((ToolBoomerang*) t)->init(false, player, tools.at(equippedTools[slot]).idTool, tools.at(equippedTools[slot]).strength,
				tools.at(equippedTools[slot]).damageType, tools.at(equippedTools[slot]).gfxPath);
		}
		break;
	default: // si no existe el tipo, salimos
		return;
	}

	if (t != NULL)	// si todo ha salido bien
	{
		// Añadimos la entidad al gameState
		controller->game->getGameState()->add(t);
		// cambiamos los datos de la herramienta
		tools.at(equippedTools[slot]).inUse = true;
		tools.at(equippedTools[slot]).usable = false;
		tools.at(equippedTools[slot]).tool = t;
	}
}

short ToolController::findEquippedTool(int idTool)
{
	short slot = 0;
	
	// buscamos en el array de armas equipadas
	while (equippedTools[slot] != idTool && slot < MAX_EQUIPPED_TOOLS)
		slot++;

	if (slot == MAX_EQUIPPED_TOOLS)
		return -1;	// no lo hemos encontrado
	else
		return slot;	// devolvemos la posición en la que se encuentra	
}

int ToolController::equippedToolAt(short slot)
{
	if (slot < 0 || slot > MAX_EQUIPPED_TOOLS)
		return -1;
	else
		return equippedTools[slot];
}

void ToolController::toolFinished(int idTool, bool deleteMe)
{
	short slot = findEquippedTool(idTool);	// buscamos la herramienta que ha finalizado

	// Destruimos la herramienta y adiós muy buenas
	tools.at(equippedTools[slot]).inUse = false;
	if (tools.at(equippedTools[slot]).tool != NULL && deleteMe)
	{
		tools.at(equippedTools[slot]).tool->instance_destroy(); // eliminamos la herramienta
		tools.at(equippedTools[slot]).tool = NULL;
	}
	tools.at(equippedTools[slot]).usable = true;
}

void ToolController::setEquippable(int idTool, bool equippable)
{
	std::map<int, ToolData>::iterator it = tools.find(idTool);	// buscamos la herramienta
	if (it != tools.end())	// si existe
	{
		(*it).second.equippable = equippable;	// hacemos el set
		(*it).second.usable = equippable;
	}
}

std::vector<int> ToolController::getEquippableTools()
{
	std::vector<int> v;
	std::map<int, ToolData>::iterator it;

	// vamos metiendo todas las armas equipables en el vector
	for (it = tools.begin(); it != tools.end(); it++)
		if (it->second.equippable)	// si es equipable
			v.push_back((*it).first);	// lo metemos en el vector

	return v;
}

void ToolController::increaseAmmo(int idTool, short ammo)
{
	std::map<int, ToolData>::iterator it = tools.find(idTool); // buscamos la herramienta
	if (it != tools.end())	// si existe aumentamos su munición
	{
		it->second.ammo += ammo;
		if (it->second.ammo > it->second.maxAmmo)	// si excede el máximo posible de al munición
			it->second.ammo = it->second.maxAmmo;	// ponemos el máximo
	}
}

short ToolController::getToolAmmo(int idTool)
{
	std::map<int, ToolData>::iterator it = tools.find(idTool);
	
	if (it == tools.end()) // si no existe la herramienta
		return -1;

	if (it->second.ammo == -1)	// el arma no tenga munición
		return -1;

	// devolvemos la munición disponible del arma
	return it->second.ammo;
}

std::string ToolController::getToolGraphicPath(int idTool)
{
	//ToolData td = tools.at(idTool);
	DataBaseInterface::ToolData tdd = controller->dbi->getToolData(idTool);

	//Se copia el nombre de archivo en un string auxiliar
	string mnuPath = tdd.gfxPath;

	// se busca extensión
    size_t found = mnuPath.find_last_of(".");
        
    //Si la encuentra
    if (found != string::npos){
            //Se descarta 
			mnuPath = mnuPath.substr(0,found);
    }

    // Se concatena la extensión del archivo de imagen estatica de arma
    mnuPath = mnuPath.append(".mnu");

	return mnuPath;
}

Graphic* ToolController::getToolGraphic(int idTool)
{
	Stamp* grafico = new Stamp(getToolGraphicPath(idTool), controller->game->getGfxEngine());
	return grafico;
}

string ToolController::getToolName(int idTool)
{
	ToolData td = tools.at(idTool);
	return td.name;
}

void ToolController::stopTool(Player* player, short slot)
{
//	if (slot == -1)
	{
		// nos las apañamos para parar todas las tools
		std::map<int, ToolData>::iterator it = tools.begin();
		while (it != tools.end())
		{
			
			// Si lo pide player y es el boomerang, nanay
			if ((*it).second.type == 3)
				return;
			if ((*it).second.inUse && !(*it).second.usable)
			{
				(*it).second.inUse = false, (*it).second.usable = true;
				if ((*it).second.tool != NULL)
					(*it).second.tool->instance_destroy(), (*it).second.tool = NULL;
			}
			it++;
		}
	}
};