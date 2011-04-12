#include "Tool.h"

// Inicialización por defecto
Tool::Tool(int x, int y, Game* game, GameState* world) : GameEntity(x, y, game, world)
{
	passive = true;
	player = NULL;
	
}

Tool::~Tool()
{
}

void Tool::init(bool passive, Player* p)
{
	this->passive = passive;
	player = p;
}