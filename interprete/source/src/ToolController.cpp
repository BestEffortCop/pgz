#include "ToolController.h"

bool Controller::equip(int idTool, Player* player){

/*

	1. Modificar la info del player correspondiente a las tools con la nueva.
	2. Instanciar la tool si es necesario (activa de efecto pasivo)

	3. Comprobando siempre el estado de la misma (si está usándose por otro player no se podrá equipar).

*/
}


void Controller::attack(int idtool, Player* player){
	
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
			Entity* e = place_meeting(nx, ny, NULL);
				
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
		
			// Por ahora, al crear una Tool se devuelve NULL si la herramienta
			// es activa pasiva y ya ha sido creada al equiparse
			else
			{
                //DBI + Tool_Builder domains
			}
}