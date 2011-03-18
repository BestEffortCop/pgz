#pragma once

#ifndef __BUILDER_H__
#define __BUILDER_H__

#include "Player.h"
#include "Enemy.h"
#include "Tool.h"
#include "Item.h"
#include "KeyItem.h"
#include "PowerUp.h"
#include "Pidgeon.h"
#include "DataBaseInterface.h"

class Builder:
{
public:

	Builder();

	Player* createPlayer(DataBaseInterface::HeroData h);
	Enemy* createEnemy(DataBaseInterface::EnemyData e);
	Tool* createTool(DataBaseInterface::ToolData t);
	Item* createItem(DataBaseInterface::ItemData i);
	TileSet* createTset(DataBaseInterface::TsetData t);
	KeyItem* createKeyItem(DataBaseInterface::KeyItemData k);
	PowerUp* createPowerUp(DataBaseInterface::PowerUpData p);
	Pidgeon* createPidgeon(DataBaseInterface::PigeonData p);
	void createExcangeItem(DataBaseInterface::ExchangeItemData e);
	void createBoss(DataBaseInterface::BossData b);
}

#endif __BUILDER_H__