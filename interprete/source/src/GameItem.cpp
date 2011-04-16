#include "GameItem.h"
#include "Player.h"
#include "Controller.h"

GameItem::GameItem(int x, int y, Game* g, GameState* gs) : Entity(x, y, g, gs)
{
	mask = NULL;
	graphic = NULL;
};

void GameItem::init(std::string gfxPath, ItemType t, int pow)
{
	graphic = new Stamp(gfxPath, game->getGfxEngine());
	effect = t;
	power = pow;

	mask = new MaskBox(x, y, ((Stamp*)graphic)->getWidth(), ((Stamp*)graphic)->getHeight(), "item");
	type = "item";
	depth = y;
};

void GameItem::onStep()
{
	depth = y;
};

void GameItem::onCollision(CollisionPair pair, Entity* other)
{
	// Sólo pueden colisionar con players en principio
	if (pair.b == "player")
	{
		applyEffect(other);
		instance_destroy();
	}
};

void GameItem::applyEffect(Entity* target)
{
	if (target != NULL)
	{
		DataPersistence* dp;
		// Player en ppio
		switch (effect)
		{
		case ieNONE:
			break;
		case ieHP:
			((Player*) target)->onHeal(power);
			break;
		case ieMP:
			// No hay interfaz as of yet
			((Player*) target)->mp += power;
			break;
		case ieKEY:
			// Esto requiere currar con Controller...
			dp = ((Player*) target)->getController()->getData();
			dp->getMapData(dp->getGameData()->getGameStatus()->getCurrentMapLocation().id)->getMapStatus()->addKeys(power);
			break;
		case ieMONEY:
			dp = ((Player*) target)->getController()->getData();
			dp->getGameData()->getGameStatus()->setCurrentMoney(dp->getGameData()->getGameStatus()->getCurrentMoney()+power);
			break;
		case ieMAXHP:
			((Player*) target)->maxHp += power;
			break;
		default:
			break;
		}
		
	}
};