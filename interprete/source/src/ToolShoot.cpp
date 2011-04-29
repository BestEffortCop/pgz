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
	// debemos crear una instancia del arma y de la munición que dispara

	ToolAnimData data;
	std::string name;
	Direction dir = player->getDir();

	// Ejecutamos la animación correspondiente en función de la dirección a la que mira el player
	switch(dir){
	case UP:
		name = "up";
		break;
	case DOWN:
		name = "down";
		break;
	case LEFT:
		name = "left";
		break;
	case UPLEFT:
		name = "left";
		break;
	case DOWNLEFT:
		name = "left";
		break;
	case RIGHT:
		name = "right";
		break;
	case UPRIGHT:
		name = "right";
		break;
	case DOWNRIGHT:
		name = "right";
		break;
	}

	data = animList.at(name);						// cogemos los datos de la animación
	playAnim(name);									// ejecutamos la animación
	player->playAnim(playeranim, data.animSpeed);	// Hacemos que el player ejecute la animación

	placeTool();	// Colocamos el arma en función de la animación actual

	// creamos la munición (en pruebas)
	ammo = new ToolAmmo(this->x, this->y, this->game, this->world);
	ammo->init(false, this->player, this->idTool, 0, 1, "data/graphics/arrow.png", dir);
	game->getGameState()->add(ammo);
}

void ToolShoot::init(bool passive, Player* p, int idTool, int damage, short damageType, std::string graphicpath)
{
	Tool::init(passive, p, idTool, damage, damageType);

	this->playeranim = playeranim;

	// cargamos las diferentes animaciones de la herramienta y su munición (quizás haga falta otra ruta para la munición)
	loadAnimations(graphicpath, getConfigurationFileName(graphicpath));
}

void ToolShoot::onInitStep()
{
	// Si la herramienta a acabado, se lo indicamos a ToolController
	if (((SpriteMap*)graphic)->animFinished())
	{
		player->changeState(Player::PlayerState::Normal);
		player->getController()->getToolController()->toolFinished(idTool);
	}
}

void ToolShoot::onEndStep()
{
	placeTool();
}