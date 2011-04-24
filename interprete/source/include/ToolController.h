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

const int MAX_TOOLS_EQUIPED = 2;

class ToolController {

	typedef enum ToolType {none, tool_Melee};	// tipos de herramientas disponibles

	struct ToolData
	{
		int idTool;					// Identificador de la herramienta
		ToolType type;				// Tipo de la herramienta
		Player::PlayerAnim pAnim;	// Animación que tendrá que ejecutar el player
		Tool* tool;					// puntero a la herramienta
		bool inUse;					// Indica si se está usando o no
		bool usable;				// Indica si se puede usar o no
		std::string gfxPath;		// Ruta con el gráfico de la herramienta
	};

private:

	Controller* controller;			// puntero a Controller
	std::vector<int> toolsToDelete;	// lista de herramientas que habrá que eliminar cuando finalice su acción
	
	/* debe guardar listas de todas las armas disponibles y su estado actual (usable, no, etc)
	posición 0 -> herramienta equipada en a
	posición 1 -> herramienta equipada en b */
	ToolData equipedTools[MAX_TOOLS_EQUIPED];

	// ------------------------------ MÉTODOS AUXILIARES ------------------------------
	
	// interactúa con la base de datos para conseguir los datos de la herramienta
	ToolData createToolData(int idTool);

	// ataca con la herramienta equipada en pos
	void toolAttack(int pos, Player* player);

	// encuentra la herramienta indicada en el array de herramientas equipadas (si no está devuelve -1)
	int findEquipedTool(int idTool);

	public:

		// CONSTRUCORES Y DESTRUCTORES
		ToolController(Controller* controller);
		~ToolController();

		// equipa la too correspondiente al player dado
		bool equip(int idTool, Player* player, char key);

		// ejecuta la acción de la tool dada del player:
		//	key == 'a' -> arma equipada en a
		//	key == 'b' -> arma equipada en b
		void attack(int idtool, Player* player, char key);

		// La herramienta "idTool" ha finalizado su acción
		void toolFinished(int idTool);

		// borra las herramientas que hayan finalizado su ejecuión
//		void clearTools();
};


#endif