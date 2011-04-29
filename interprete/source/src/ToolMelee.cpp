#include "ToolMelee.h"

ToolMelee::ToolMelee(int x, int y, Game* game, GameState* world) : Tool(x, y, game, world)
{
}

ToolMelee::~ToolMelee(){};

void ToolMelee::init(bool passive, Player* p, int idTool, int damage, short damageType, std::string graphicpath)
{
	Tool::init(passive, p, idTool, damage, damageType);

	// cargamos las diferentes animaciones de la herramienta
	loadAnimations(graphicpath, getConfigurationFileName(graphicpath));
}

void ToolMelee::onInit()
{
	if (player->changeState(Player::Attack))
		activate();
	else
		// hay que avisar a toolController de que no se puede atacar
		player->getController()->getToolController()->toolFinished(idTool);
}

void ToolMelee::activate()
{
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
}

void ToolMelee::onInitStep()
{
	// Si la herramienta a acabado, se lo indicamos a ToolController
	if (((SpriteMap*)graphic)->animFinished())
	{
		player->changeState(Player::PlayerState::Normal);
		player->getController()->getToolController()->toolFinished(idTool);
	}
}


void ToolMelee::onEndStep()
{
	placeTool();
}

void ToolMelee::onCollision(CollisionPair other, Entity* e)
{
	if (other.b == "player") return;	// no queremos hacer daño al player
	
	// si es cualquier otra cosa, hacemos el daño estipulado del tipo estipulado
	iDamageable* aux;
	if (aux = dynamic_cast<iDamageable*>(e))
	{
		// si es un enemigo le informamos de la dirección desde la que le pegamos
		if (other.b == "enemy")
			((Enemy*) e)->setLastDmgDirection(player->getDir());

		aux ->onDamage(damage, damageType);
	}
}
