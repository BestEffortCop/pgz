#include "Controller.h"

Controller::Controller()
{
}
	
Controller::~Controller()
{
}
	
void Controller::onStep()
{

	switch (state) 
	{
		// NORMAL: check player in bounds map
		TRANSITION:
			// TO BE DONE
			break;
	}

}

void Controller::change_screen(Dir dir){

	/* ---------------------------------------------------------------------
	1. Preguntar a Data por la pantalla destino. Recibe lista de propiedades
		1.1. Preguntar si la pantalla destino existe
	--------------------------------------------------------------------- */
	
			// Obtenemos la pantalla destino del cambio
			up = left = 0;
			switch (dir) 
			{
				UP: up = -1; break;
				DOWN: up = 1; break;
				LEFT:  left = -1; break;
				RIGTH:  left = 1; break;
			}
			mapId m = GameStatus->getMapId();
			m.mapX += left;
			m.mapY += up;            
			// Preguntamos si la pantalla existe

			if (Data->hasScreen(m))
			{
			
	/* ---------------------------------------------------------------------
	   1.2. Obtenemos las propiedades de la pantalla destino.
	--------------------------------------------------------------------- */
	
			   // Ya están en m, lala(8)
			   
	/* ---------------------------------------------------------------------
	2. Desvisivilizar player y hud
		2.1. Desvisibilizar player
	--------------------------------------------------------------------- */

			for (int i = 0; i < numPlayers; i++)
				players[i]->setVisible(false);
				
	/* ---------------------------------------------------------------------
		2.2. Desvisibilizar hud
	--------------------------------------------------------------------- */

				hud->setVisible(false);       

	/* ---------------------------------------------------------------------
	3. Hace foto y la guarda
	--------------------------------------------------------------------- */

			int w = game->getGameConfig()->gameWidth;
			int h = game->getGameConfig()->gameHeigh;
			Image* snap1 = new Image(w, h, game->getGfxEngine(), false, true);
			
			game->getGfxEngine()->setRenderTarget(snap1);
			world->OnRender();
			game->getGfxEngine()->resetRenderTarget();
		   
	/* ---------------------------------------------------------------------
	4. Mapa, cárgame los datos del nuevo mapa y borra los anteriores ( o buffer ). 
	El nuevo mapa sustituirá al actual, contendrá a los players y el hud y además
	las entidades cargadas deberán estar disabled (de eso me ocupo yo, Controller).
	--------------------------------------------------------------------- */
	
			// naive code: rethink

			// suponemos que se ocupa de pasar el antiguo mapa al buffer
			if  (!map->loadScreen(m))
				return false;
				
	/* ---------------------------------------------------------------------
	5. Hazle foto al nuevo mapa.
	--------------------------------------------------------------------- */

			Image* snap2 = new Image(w, h, game->getGfxEngine(), false, true);
			game->getGfxEngine()->setRenderTarget(snap2);
			world->onRender();
			game->getGfxEngine()->resetRenderTarget();

	/* ---------------------------------------------------------------------
	6. Junta fotos.
	--------------------------------------------------------------------- */
		
		// Estupidez. Need to generalizar a todas las pos (fácil pero hay sueño)
	
	/*
			Image* snap = new Image(2*w, h, game->getGfxEngine(), false, true);
	
			// Falta tener en cuenta el offset del mapa, si tiene
			game->getGfxEngine()->render(snap1, 0, 0, snap);
			game->getGfxEngine()->render(snap1, w, 0, snap);
	*/
	
	/* ---------------------------------------------------------------------
	7. Activa player y hud
		7.1 Hace visible el player. Será necesario además disablearlo para 
		que no pueda moverse durante la transición
	--------------------------------------------------------------------- */
	
			for (int i = 0; i < numPlayers; i++)
			{
				players[i]->setVisible(false);
				players[i]->disable();
			}
	
	/* ---------------------------------------------------------------------
		7.2. Hace visible el Hud y lo disablea por el mismo motivo.
	--------------------------------------------------------------------- */
	
				hud->setVisible(true);
				hud->disable();

	/* ---------------------------------------------------------------------
	8. Actualiza los datos con la nueva pos del player en el mapa.
	--------------------------------------------------------------------- */

				Data->setMapId(m);
				
	/* ---------------------------------------------------------------------
	9. Colocación del player + preparación para la transición
		9.1. Colocación del player
	--------------------------------------------------------------------- */
	
				// Stupid code test
				int x, y;
				switch (dir) 
				{
					UP: x = w / 2; y = h; break;
					DOWN: x = w / 2; y = 0; break;
					LEFT: x = w; y = h / 2; break;
					RIGTH:  x = 0; y = h / 2; break;
				};

	/* ---------------------------------------------------------------------
		9.2. Aplicación de efectos y preparación de la transición.
	--------------------------------------------------------------------- */
	
			setStatus(TRANSITION);
			setTransitionEffect(SCROLL);

	/* ---------------------------------------------------------------------
	10. Finalización
	--------------------------------------------------------------------- */
			return true;
		}
		else
			return false;
}


void Controller::setStatus(State st)
{
	state = st;
}

void Controller::setTransitionEffect(TransEffect te)
{
	transtitionEffect = te;
}
	
void Controller::change_map()
{
}
	
void Controller::attack(int idtool, objPlayer* player){
	
	/* ---------------------------------------------------------------------
		1. Interactuar si es necesario:
			1.1. obtener la posición frente al player
	--------------------------------------------------------------------- */
			
				// Coordenadas del objeto frente al player
				int nx, ny;
				int up, left;
				up = left = 0;

				switch (player->dir) 
				{
					UP: up = -1; break;
					DOWN: up = 1; break;
					LEFT:  left = -1; break;
					RIGTH:  left = 1; break;
				}

				nx = player->x + D_INTERACT * left;
				ny = player->y + D_INTERACT * up;

	/* ---------------------------------------------------------------------
			1.2. Si el objeto es interactable, interactuar con él
	--------------------------------------------------------------------- */
			
				// Objeto frente al player
				Entity* e = place_meeting(nx, ny, e);
				
				if (e != NULL)
				{
					// si es un objeto con el se puede interactuar, se hará lo propio
					if (dynamic_cast<iInteractable*>(e))
						e->onInteract(player);
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
	
}





#endif