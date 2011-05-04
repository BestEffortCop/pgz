#include "ToolController.h"

#include "ToolMelee.h"
#include "ToolShoot.h"
#include "ToolAmmo.h"

ToolController::ToolController(Controller* controller)
{
	this->controller = controller;

	// creamos una información de herramienta vacía
	ToolData td = createToolData(-1);

	// metemos herramientas vacías en todas las posibles teclas para equipar
	for (int i=0; i<MAX_EQUIPPED_TOOLS; i++)
		equippedTools[i] = td;
}

ToolController::~ToolController()
{
	// borramos las herramientas que no hayan sido borradas todavía
	for (int i = 0; i < MAX_EQUIPPED_TOOLS; i++)
		if (equippedTools[i].tool != NULL)
			equippedTools[i].tool->instance_destroy();
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
	map<int, bool>::iterator it = equippableTools.find(idTool);
	if (it == equippableTools.end())	// no existe la herramienta
		return false;
	else
		if (!it->second)	// existe pero no es equipable
			return false;

	// si la herramienta actual está en uso no se puede equipar
	if (equippedTools[slot].inUse) return false;
	
	// Desequipamos la actual
	if (equippedTools[slot].tool != NULL) equippedTools[slot].tool->instance_destroy();

	// equipamos la herramienta nueva
	ToolData td = createToolData(idTool);
	equippedTools[slot] = td;
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
	ToolData td;
	td.ammoGfxpath = "";
	td.damageType = -1;
	td.gfxPath = "";
	td.idTool = -1;
	td.inUse = false;
	td.strength = -1;
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
			td.damageType = PHYSICAL;
			td.gfxPath = "data/graphics/weapon-slashsword.png"; // habrá que cogerlo de la base de datos
			td.idTool = idTool;
			td.strength = 3;
			td.usable = true;
			td.type = ToolType::tool_Melee;
		}
		else if (idTool == 2) // Espada Thurst
		{
			td.damageType = PHYSICAL;
			td.gfxPath = "data/graphics/weapon-sword.png";	// habrá que cogerlo de la base de datos
			td.idTool = idTool;
			td.strength = 3;
			td.usable = true;
			td.type = ToolType::tool_Melee;
		}
		else if (idTool == 3)	// arco
		{
			td.ammoGfxpath =  "data/graphics/arrow.png";
			td.gfxPath = "data/graphics/weapon-arc.png";	// habrá que cogerlo de la base de datos
			td.idTool = idTool;
			td.usable = true;
			td.type = ToolType::tool_Shoot;
		}
		else if (idTool == 4){ // bastón mágico
			td.ammoGfxpath =  "data/graphics/fireBall.png";
			td.gfxPath = "data/graphics/magicStick.png";	// habrá que cogerlo de la base de datos
			td.idTool = idTool;
			td.usable = true;
			td.type = ToolType::tool_Shoot;			
		}
		return td;
	}
}

void ToolController::toolAttack(short slot, Player* player)
{
	// realizamos la acción correspondiente dependiendo del tipo del arma
	switch(equippedTools[slot].type)
	{
	case tool_Melee:
		if (equippedTools[slot].usable) // si la podemos usar
		{
			// creamos la herramienta correspondiente y la iniciamos
			ToolMelee* meleeTool;
			meleeTool = new ToolMelee(player->x, player->y, controller->game, controller->game->getGameState());
			meleeTool->init(false, player, equippedTools[slot].idTool, equippedTools[slot].strength, equippedTools[slot].damageType, equippedTools[slot].gfxPath);
			// Añadimos la entidad al gameState
			controller->game->getGameState()->add(meleeTool);
			// cambiamos los datos de la herramienta
			equippedTools[slot].inUse = true;
			equippedTools[slot].usable = false;
			equippedTools[slot].tool = meleeTool;
		}
		break;
	case tool_Shoot:
		if (equippedTools[slot].usable)
		{
			ToolShoot* shootingTool;
			shootingTool = new ToolShoot(player->x, player->y, controller->game, controller->game->getGameState());
			shootingTool->init(false, player, equippedTools[slot].idTool, equippedTools[slot].strength, equippedTools[slot].damageType, equippedTools[slot].gfxPath, equippedTools[slot].ammoGfxpath);
			controller->game->getGameState()->add(shootingTool);
			equippedTools[slot].inUse = true;
			equippedTools[slot].usable = false;
			equippedTools[slot].tool = shootingTool;
		}
		break;
	default: // si no existe el tipo, salimos
		return;
	}
}

short ToolController::findEquippedTool(int idTool)
{
	short slot = 0;
	
	// buscamos en el array de armas equipadas
	while (equippedTools[slot].idTool != idTool && slot < MAX_EQUIPPED_TOOLS)
		slot++;

	if (slot == MAX_EQUIPPED_TOOLS)
		return -1;	// no lo hemos encontrado
	else
		return slot;	// devolvemos la posición en la que se encuentra	
}

int ToolController::equippedToolAt(short slot)
{
	if (slot < 0 || slot > MAX_EQUIPPED_TOOLS)
		return equippedTools[slot].idTool;
	else
		return -1;
}

void ToolController::toolFinished(int idTool)
{
	short slot = findEquippedTool(idTool);	// buscamos la herramienta que ha finalizado

	// dependiendo del tipo de herramienta habrá que realizar una acción distinta
	switch(equippedTools[slot].type)
	{
	case ToolType::tool_Melee:
		equippedTools[slot].inUse = false;
		equippedTools[slot].tool->instance_destroy(); // eliminamos la herramienta
		equippedTools[slot].tool = NULL;
		equippedTools[slot].usable = true;
		break;
	case ToolType::tool_Shoot:
		equippedTools[slot].inUse = false;
		equippedTools[slot].tool->instance_destroy(); // eliminamos la herramienta
		equippedTools[slot].tool = NULL;
		equippedTools[slot].usable = true;
		break;
	default:
		break;
	}
}

void ToolController::init(std::vector<int> tools)
{
	// añadimos las herramientas del vector como parámetro, de momento las ponemos como no equipables
	for (int i = 0; i < tools.size(); i++)
		equippableTools.insert(make_pair(tools[i], false));
}

void ToolController::setEquippable(int idTool, bool equippable)
{
	map<int, bool>::iterator it = equippableTools.find(idTool);	// buscamos la herramienta
	if (it != equippableTools.end())	// si existe
		(*it).second = equippable;		// hacemos el set
}

std::vector<int> ToolController::getEquippableTools()
{
	std::vector<int> v;
	std::map<int, bool>::iterator it;

	// vamos metiendo todas las armas equipables en el vector
	for (it = equippableTools.begin(); it != equippableTools.end(); it++)
		if (it->second)	// si es equipable
			v.push_back((*it).first);	// lo metemos en el vector

	return v;
}