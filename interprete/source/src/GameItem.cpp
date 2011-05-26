#include "GameItem.h"
#include "Player.h"
#include "Controller.h"
#include "ToolAmmo.h"

GameItem::GameItem(int x, int y, Game* g, GameState* gs) : GameEntity(x, y, g, gs)
{
	ammoAmmount = 5;
	mask = NULL;
	graphic = NULL;
};

void GameItem::init(std::string gfxPath, ItemType t, int pow)
{
	effect = t;
	power = pow;

	if (effect == ieTOOLAMMO)
	{
		// Hay que hacer movidorras!
		ToolAmmo* ammo = new ToolAmmo(-1, -1, game, world);
		ammo->init(false, NULL, power, -1, -1, gfxPath, UP);
		graphic = ammo->graphic;
		ammo->graphic = NULL;
		delete ammo;

		((SpriteMap*) graphic)->playAnim("up", 1, true);
	}
	else
		graphic = new Stamp(gfxPath, game->getGfxEngine());

	mask = new MaskBox(x, y, graphic->getWidth(), graphic->getHeight(), "item");
	type = "item";
	depth = y;

	initShadow(GameEntity::sSmall);
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
			((Player*) target)->hp = ((Player*) target)->maxHp;
			break;
		case ieMAXMP:
			// No hace nada por ahora
			break;
		case ieBOSSKEY:
			{
				dp = ((Player*) target)->getController()->getData();
				MapData* md = dp->getMapData(dp->getGameData()->getGameStatus()->getCurrentMapLocation().id);
				switch (md->getType())
				{
				case 0: // OWorld
					// En el OWorld no hay BossKey
					break;
				case 1: // Dungeon
					((DungeonMapStatus*) md->getMapStatus())->setBossKeyGot(true);
					break;
				}
			}
			break;
		case ieKEYITEM:
			dp = ((Player*) target)->getController()->getData();
			dp->getGameData()->getGameStatus()->setNumKeyItems(dp->getGameData()->getGameStatus()->getNumKeyItems() + power);
			break;
		case ieTOOL:
			{
				// La tool es un poco peliaguda: el pow es el id de la tool
				ToolController* tc = ((Player*) target)->getController()->getToolController();
				tc->setEquippable(power, true);
				dp = ((Player*) target)->getController()->getData();
				dp->getGameData()->getGameStatus()->setToolAvailable(power, true);
			}
		case iePIGEON:
			dp = ((Player*) target)->getController()->getData();
			dp->getGameData()->getGameStatus()->setNumPigeons(dp->getGameData()->getGameStatus()->getNumPigeons() + power);
			break;
		case ieTOOLAMMO:
			// Añadimos ammo!
			dp = ((Player*) target)->getController()->getData();
			dp->getGameData()->getGameStatus()->setToolAmmoQuantity(power, dp->getGameData()->getGameStatus()->getToolAmmoQuantity(power)+ammoAmmount);
			((Player*) target)->getController()->getToolController()->increaseAmmo(power, ammoAmmount);
			break;
		default:
			break;
		}
		
	}
};