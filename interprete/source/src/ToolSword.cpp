#include "ToolSword.h"

ToolSword::ToolSword(int x, int y, Game* game, GameState* world) : Tool(x, y, game, world)
{
}

void ToolSword::init(bool passive, Player* p, string graphicpath, int ncol, int nrow)
{
	Tool::init(passive, p);

	// creamos el gráfico de la espada
	graphic = new SpriteMap();
}