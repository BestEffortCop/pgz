#include "ToolAmmo.h"

ToolAmmo::ToolAmmo(int x, int y, Game* game, GameState* world) : Tool(x, y, game, world) {}

ToolAmmo::~ToolAmmo() {}

void ToolAmmo::onInit()
{
	activate();
}

void ToolAmmo::activate()
{
	
}