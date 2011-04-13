#pragma once
#ifndef __TOOLCONTROLLER_H__
#define __TOOLCONTROLLER_H__

#include "Player.h"
#include "iInteractable.h"

#include "Controller.h"
#include "ToolSword.h"

// Distancia (en píxeles) mínima necesaria entre el player y una entidad interactuable
// para que el player interactúe con ella al pulsar un botón
const int D_INTERACT = 3;

class ToolController {

private:

	Controller* controller;

	public:

		// CONSTRUCORES Y DESTRUCTORES
		ToolController(Controller* controller);
		~ToolController();

		// debe guardar listas de todas las armas disponibles y su estado actual (usable, no, etc)
		map<int, Tool*> createdTools;

		// equipa la too correspondiente al player dado
		bool equip(int idTool, Player* player);

		// ejecuta la acción de la tool dada del player
		void attack(int idtool, Player* player);
};


#endif