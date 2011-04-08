#include "Tool.h"

// Inicialización por defecto
Tool::Tool(int x, int y, Game* game, GameState* world, string graphicPath) : GameEntity(x, y, game, world)
{
	passive = true;
	player = NULL;
	// hay que crear el gráfico a partir del graphicPath
	
}

Tool::~Tool()
{
}

void Tool::init(bool passive, Player* p)
{
	this->passive = passive;
	player = p;
}