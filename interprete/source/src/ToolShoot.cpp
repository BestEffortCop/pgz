#include "ToolShoot.h"

ToolShoot::ToolShoot(int x, int y, Game* game, GameState* world) : Tool(x, y, game, world)
{
}

ToolShoot::~ToolShoot()
{
}

void ToolShoot::onInit()
{
	if (player->changeState(Player::Attack))
		activate();

	else 
		// hay que avisar a toolController de que no se puede atacar
		player->getController()->getToolController()->toolFinished(idTool);
}

void ToolShoot::activate()
{
}

void ToolShoot::init(bool passive, Player* p, Player::PlayerAnim playeranim, int idTool, std::string graphicpath)
{
}