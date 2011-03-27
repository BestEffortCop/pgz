#include "EventController.h"



EventController::EventController(Game* g, GameState* gs, Controller* controller) : Entity(0, 0, g, gs)
{
	this->controller = controller;
	visible = false;
	collidable = false;
}


void EventController::onStep()
{

	switch (controller->getState()) 
	{
		case Controller::NORMAL: 
			{
				// check player in bounds map
				int i = 0;
				bool inside = true;
				// Calculamos si algún player se sale del mapa
				while ((i < controller->getNumPlayers()) && inside)
				{ 
					inside = controller->getScreenMap()->isInBounds(controller->getPlayer(i));
					i++;
				}

				// Si ocurre, realizamos la transición
				if (!inside)
				{
					// Calculamos por donde se ha salido
					Dir dir = controller->getScreenMap()->relative_position(controller->getPlayer(i - 1));
					// Cambiamos de pantalla
					controller->move_screen(dir);
				}
				break;
			}
		case Controller::TRANSITION:
			{
				if (controller->getTransitionEffect() == Controller::SCROLL)
				{
					// Si no hemos acabado de desplazar la pantalla, continuamos
					if ((controller->mx + controller->speed*controller->xdir) < controller->tx)
						controller->mx += controller->speed*controller->xdir;
					else if ((controller->my + controller->speed*controller->ydir) < controller->ty)
						controller->my += controller->speed*controller->ydir;
					// Si hemos acabado, pasamos a estado normal
					else{
				
						// Activamos al player
						for (int i = 0; i < controller->getNumPlayers(); i++)
						{
							controller->getPlayer(i)->setVisible(false);
							controller->getPlayer(i)->enable();
						}
				
						controller->getHUDController()->enableHUDs();
					
						// Activamos el resto de entidades
						// TO BE DONE
				
						controller->setState(Controller::NORMAL);
					}
				}
				break;
			}

		default:
			break;
	}
}

void EventController::onRender()
{
	switch (controller->getState()) 
	{
	case Controller::TRANSITION:
			if (controller->getTransitionEffect() == Controller::SCROLL)
			{
				// Durante la transición, pintamos el mapa en desplazamiento en la correspondiente posición
				controller->game->getGfxEngine()->render(controller->currentRoom, controller->mx, controller->my);
				controller->game->getGfxEngine()->render(controller->nextRoom, controller->mx + controller->xdir*controller->width, controller->my + controller->ydir*controller->height);
			}
			break;

		default:
			break;
	}
}


void EventController::onTimer(int timer){

	switch (timer) {

		// multiplayer-warp timer
		case 0:
			/* resolver conflicto de cambio de mapas

			PortInfo winner;

			// get portal with most players in them

			// realiza el cambio de mapa de forma forzada sobre el jugador p
			change_map(winner.MapLocation, winner.p, winner.te, true);*/

			break;
	}
}