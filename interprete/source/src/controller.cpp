#include "Controller.h"

Controller::Controller(std::string path, Game* g, GameState* gs): Entity (0, 0, g, gs)
{
	// Almacena los parámetros necesarios
	game = g;
	world = gs;
	width = game->getGameConfig()->gameWidth;
	height = game->getGameConfig()->gameHeight;

	// Crea las imágenes que usará para el cambio de posición del mapa
	currentRoom = new Image(width, height, game->getGfxEngine(), false, true);
	nextRoom = new Image(width, height, game->getGfxEngine(), false, true);
	
	
	init(path);
}
	
Controller::~Controller()
{
}
	
bool Controller::init(std::string path)
{

/* ---------------------------------------------------------------------
1.	Recupera los datos del archivo de config en path y, en el caso de 
	que este sea NULL, saca los valores necesarios de la DBI
--------------------------------------------------------------------- */

	// método de lectura del bicho



/* ---------------------------------------------------------------------
2.	Con los datos recuperados, crea Data y la inicia.
--------------------------------------------------------------------- */

/* ---------------------------------------------------------------------
3.	Apartir de lo recuperado en el archivo de config, carga el layout del
	mapa actual y se lo da a Data (MapState)
--------------------------------------------------------------------- */

/* ---------------------------------------------------------------------
4.	Carga la pantalla actual en su totalidad, y por cada entidad que
	cargue, la envía a GameState al add sobrecargado. Al final
	se llama al init de ScreenMap con todos los datos cargados.
--------------------------------------------------------------------- */

/* ---------------------------------------------------------------------
5.	Crea los players en la posición configurada de la pantalla del
	mapa actual.
--------------------------------------------------------------------- */

/* ---------------------------------------------------------------------
6.	Crea el hud adecuado a la cantidad de players.
--------------------------------------------------------------------- */

/* ---------------------------------------------------------------------
7.	Pausa todos los elementos que ha creado de la nueva pantalla.
--------------------------------------------------------------------- */

/* ---------------------------------------------------------------------
8.	Pausa todos los elementos que ha creado de la nueva pantalla.
--------------------------------------------------------------------- */

	return true;
}

void Controller::onStep()
{

	switch (state) 
	{
		case NORMAL: 
			{
				// check player in bounds map
				int i = 0;
				bool inside = true;
				// Calculamos si algún player se sale del mapa
				while ((i < numPlayers) && inside)
				{ 
					inside = screenMap->isInBounds(players[i]);
					i++;
				}

				// Si ocurre, realizamos la transición
				if (!inside)
				{
					// Calculamos por donde se ha salido
					Dir dir = screenMap->relative_position(players[i - 1]);
					// Cambiamos de pantalla
					change_screen(dir);
				}
				break;
			}
		case TRANSITION:
			{
				if (transitionEffect == SCROLL)
				{
					// Si no hemos acabado de desplazar la pantalla, continuamos
					if ((mx + speed*xdir) < tx)
						mx += speed*xdir;
					else if ((my + speed*ydir) < ty)
						my += speed*ydir;
					// Si hemos acabado, pasamos a estado normal
					else{
				
						// Activamos al player
						for (int i = 0; i < numPlayers; i++)
						{
							players[i]->setVisible(false);
							players[i]->disable();
						}
				
						//  Activamos el hud
						hud->disable();
				
						// Activamos el resto de entidades
						// TO BE DONE
				
						setState(NORMAL);
					}
				}
				break;
			}

		default:
			break;
	}
}


void Controller::onRender()
{
	switch (state) 
	{
		case TRANSITION:
			if (transitionEffect == SCROLL)
			{
				// Durante la transición, pintamos el mapa en desplazamiento en la correspondiente posición
				game->getGfxEngine()->render(currentRoom, mx, my);
				game->getGfxEngine()->render(nextRoom, mx + xdir*width, my + ydir*height);
			}
			break;

		default:
			break;
	}
}

bool Controller::change_screen(Dir dir){

/* ---------------------------------------------------------------------
1. Preguntar a Data por la pantalla destino. Recibe lista de propiedades
	1.1. Preguntar si la pantalla destino existe
--------------------------------------------------------------------- */
	
	// Obtenemos la pantalla destino del cambio
	int up; int left;
	up = left = 0;
	switch (dir) 
	{
		case UP:	up = -1; break;
		case DOWN:	up = 1; break;
		case LEFT:	left = -1; break;
		case RIGHT:	left = 1; break;
		default:	break;
	}
	GameData::MapId m = data->getMapId();
	m.mapX = m.mapX + left;
	m.mapY = m.mapY + up;       
 
	// Preguntamos si la pantalla existe
	if (data->hasScreen(m))
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

		// Limpiar currentRoom si es necesario
		game->getGfxEngine()->setRenderTarget(currentRoom);
		world->onRender();
		game->getGfxEngine()->resetRenderTarget();
		   
/* ---------------------------------------------------------------------
4. Mapa, cárgame los datos del nuevo mapa y borra los anteriores ( o buffer ). 
El nuevo mapa sustituirá al actual, contendrá a los players y el hud y además
las entidades cargadas deberán estar disabled (de eso me ocupo yo, Controller).
--------------------------------------------------------------------- */
	
		// naive code: rethink <- PERO MAZO

		// suponemos que se ocupa de pasar el antiguo mapa al buffer
		/*if  (!map->loadScreen(m))
			return false;*/
				
/* ---------------------------------------------------------------------
5. Hazle foto al nuevo mapa.
--------------------------------------------------------------------- */

		// Limpiar nextRoom si es necesario
		game->getGfxEngine()->setRenderTarget(nextRoom);
		world->onRender();
		game->getGfxEngine()->resetRenderTarget();

/* ---------------------------------------------------------------------
6. Junta fotos.
--------------------------------------------------------------------- */
		
		// No es necesario si pintamos las 2 directamente en la pantalla de juego
		// Nos ahorramos una pantalla auxiliar

/* ---------------------------------------------------------------------
7. Visibiliza player y hud
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

			// Igual ha de hacerse antes de cargar el nuevo ScreenMap
			data->setMapId(m);
				
/* ---------------------------------------------------------------------
9. Colocación del player + preparación para la transición
	9.1. Colocación del player
--------------------------------------------------------------------- */
	
			// PONER OFFSET A LOS MAPAS

			// Stupid code test
			int x, y;
			switch (dir) 
			{
				case UP: 
					// Mantenemos la x y cambiamos la y
					y = height; 
					break;
				case DOWN:
					// Mantenemos la x y cambiamos la y
					y = 0; 
					break;
				case LEFT:
					// Mantenemos la y y cambiamos la x
					x = width;
					break;
				case RIGHT: 
					// Mantenemos la y y cambiamos la x
					x = 0;
					break;
			};

/* ---------------------------------------------------------------------
	9.2. Aplicación de efectos y preparación de la transición.
--------------------------------------------------------------------- */
	
		setState(TRANSITION);
		setTransitionEffect(SCROLL);
			
		// Dirección explícita de la transición
		int xdir, ydir;
		xdir = ydir = 0;
			
		speed = 4;
		// Origen (mx,my) y destino (tx, ty) de la transición
		int mx, my, tx, ty;
		mx = my = tx = ty = 0;
		switch (dir) 
		{			
			case UP: 
				ydir = 1;
				ty = height;
				break;
			case DOWN: 
				ydir = -1;
				ty = -height;
				break;
			case LEFT:  
				xdir = 1; 
				tx = width;
				break;
			case RIGHT:  
				xdir = -1; 
				tx = -width;
				break;
		}

/* ---------------------------------------------------------------------
10. Finalización
--------------------------------------------------------------------- */
		return true;
	}
	else
		return false;
}


void Controller::setState(State st)
{
	state = st;
}

void Controller::setTransitionEffect(TransitionEffect te)
{
	transitionEffect = te;
}
	
bool Controller::change_map(GameData::MapId m, Player* p, TransitionEffect te)
{
	return true;
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