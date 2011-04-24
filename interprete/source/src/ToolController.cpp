#include "ToolController.h"

ToolController::ToolController(Controller* controller)
{
	this->controller = controller;

	// creamos una información de herramienta vacía
	ToolData td = createToolData(-1);

	// metemos herramientas vacías en todas las posibles teclas para equipar
	for (int i=0; i<MAX_TOOLS_EQUIPED; i++)
		equipedTools[i] = td;
}

ToolController::~ToolController()
{
	// borramos las herramientas que no hayan sido borradas todavía
	for (int i=0; i<MAX_TOOLS_EQUIPED; i++)
		if (equipedTools[i].tool != NULL)
			delete equipedTools[i].tool;
}

// de momento preparado sólo para un player (habrá que tener más listas para más players)
// key indica lo mismo que en attack
bool ToolController::equip(int idTool, Player* player, char key){

/*

	1. Modificar la info del player correspondiente a las tools con la nueva.
	2. Instanciar la tool si es necesario (activa de efecto pasivo)

	3. Comprobando siempre el estado de la misma (si está usándose por otro player no se podrá equipar).

*/

	// Cuando esté lista la base datos, interactuar con ella para conseguir los datos de la herramienta
	// De momento no se consideran herramientas pasivas

	// cogemos la información de la base de datos
	ToolData td = createToolData(idTool);
	int pos;

	// la metemos en el array de armas equipadas
	switch (key)
	{
	case 'a':	// posición 0 en el array
		pos = 0;
		break;
	case 'b':	// posición 1 en el array
		pos = 1;
		break;
	default:
		return false;	// la tecla donde se quiere equipar no existe
	}
	if (equipedTools[pos].inUse) return false;	// si la herramienta está en uso no se puede equipar
	
	equipedTools[pos] = td;	// equipamos la herramienta
	return true;
}


void ToolController::attack(int idtool, Player* player, char key){
	
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
        switch (key)
		{
		case 'a':	// posición 0 en el array
			toolAttack(0, player);
			break;
		case 'b': // posición 1 del array
			toolAttack(1, player);
			break;
		default:
			return; // no hay inguna herramienta para dicha tecla
		}
	}
}

ToolController::ToolData ToolController::createToolData(int idTool)
{
	// De momento creamos una información de herramienta vacía
	ToolData td;
	td.gfxPath = "";
	td.idTool = -1;
	td.inUse = false;
	td.pAnim = Player::PlayerAnim::Stand;
	td.tool = NULL;
	td.type = ToolType::none;
	td.usable = false;

	// Si no existe el identificador lo devolvemos vacío
	if (idTool == -1) return td;
	else	// Devolvemos la información dada por la base de datos
	{
		// td = DameDatosDBi(idTool)!!!!; return td; (cuando la base de datos esté lista)
		// mientras tanto....
		if (idTool == 1)	// Espada slash
		{
			td.gfxPath = "data/graphics/weapon-slashsword.png"; // habrá que cogerlo de la base de datos
			td.idTool = idTool;
			td.pAnim = Player::PlayerAnim::Slash;
			td.usable = true;
			td.type = ToolType::tool_Melee;
		}
		else // Espada Thurst
		{
			td.gfxPath = "data/graphics/weapon-sword.png";	// habrá que cogerlo de la base de datos
			td.idTool = idTool;
			td.pAnim = Player::PlayerAnim::Thrust;
			td.usable = true;
			td.type = ToolType::tool_Melee;
		}
		return td;
	}
}

void ToolController::toolAttack(int pos, Player* player)
{
	// realizamos la acción correspondiente dependiendo del tipo del arma
	switch(equipedTools[pos].type)
	{
	case tool_Melee:
		if (equipedTools[pos].usable) // si la podemos usar
		{
			// creamos la herramienta correspondiente y la iniciamos
			ToolMelee* meleeTool;
			meleeTool = new ToolMelee(player->x, player->y, controller->game, controller->game->getGameState());
			meleeTool->init(false, player, equipedTools[pos].pAnim, equipedTools[pos].idTool, equipedTools[pos].gfxPath);
			// Añadimos la entidad al gameState
			controller->game->getGameState()->add(meleeTool);
			// cambiamos los datos de la herramienta
			equipedTools[pos].inUse = true;
			equipedTools[pos].usable = false;
			equipedTools[pos].tool = meleeTool;
		}
		break;
	default: // si no existe el tipo, salimos
		return;
	}
}

int ToolController::findEquipedTool(int idTool)
{
	int pos = 0;
	
	// buscamos en el array de armas equipadas
	while (equipedTools[pos].idTool != idTool && pos < MAX_TOOLS_EQUIPED)
		pos++;

	if (pos == MAX_TOOLS_EQUIPED)
		return -1;	// no lo hemos encontrado
	else
		return pos;	// devolvemos la posición en la que se encuentra	
}

void ToolController::toolFinished(int idTool)
{
	int pos = findEquipedTool(idTool);	// buscamos la herramienta que ha finalizado

	// dependiendo del tipo de herramienta habrá que realizar una acción distinta
	switch(equipedTools[pos].type)
	{
	case ToolType::tool_Melee:
		equipedTools[pos].inUse = false;
		controller->gamePlayState->remove(equipedTools[pos].tool); // eliminamos la herramienta
		equipedTools[pos].tool = NULL;
		equipedTools[pos].usable = true;
		break;
	default:
		break;
	}
}


/*
void ToolController::clearTools()
{
	Tool* t;
	int idtool;

	// Eliminamos las herramientas (a mejorar, ya que se salta una herramienta cuando la borra)
	for (int i = 0; i < toolsToDelete.size(); i++)
	{
		idtool = toolsToDelete[i];
#ifdef _VS2008_
		// Se busca la herramienta
		std::map<int, Tool*>::iterator it = createdTools.find(idtool);
		if (it == createdTools.end())
			return;
		t = (*it).second;
#endif
#ifdef _VS2010_
		t = createdTools.at(idtool);
#endif
		if (t->animFinished()) // si la animación ha terminado, hay que eliminarla
		{
			toolsToDelete.erase(toolsToDelete.begin() + i); // eliminamos la herramienta de la lista de herramientas a eliminar
			controller->game->getGameState()->remove(t); // la eliminamos del gamestate
			createdTools.erase(idtool); // la eliminamos del mapa de herramientas creadas
		}
	}
	

}*/