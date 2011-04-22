#pragma once
#ifndef __TOOLCONTROLLER_H__
#define __TOOLCONTROLLER_H__

#include "Player.h"
#include "iInteractable.h"

#include "Controller.h"
#include "ToolMelee.h"

// Distancia (en píxeles) mínima necesaria entre el player y una entidad interactuable
// para que el player interactúe con ella al pulsar un botón
const int D_INTERACT = 3;

class ToolController
{

private:

	Controller* controller;			// puntero a Controller
	std::vector<int> toolsToDelete;	// lista de herramientas que habrá que eliminar cuando finalice su acción

	public:

		// CONSTRUCORES Y DESTRUCTORES
		ToolController(Controller* controller);
		~ToolController();

		// debe guardar listas de todas las armas disponibles y su estado actual (usable, no, etc)
		map<int, Tool*> createdTools;

		// equipa la too correspondiente al player dado
		bool equip(int idTool, Player* player);

		// ejecuta la acción de la tool dada del player
		void attack(int idtool, Player* player, Player::PlayerAnim playeranim);

		// borra las herramientas que hayan finalizado su ejecuión
		void clearTools();
};


#endif
