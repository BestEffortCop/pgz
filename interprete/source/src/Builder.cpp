#include "Builder.h"


//Constructora por defecto que no hace nada
Builder::Builder(){};

//Contruye un Player con los datos que me dan
Player* Builder::createPlayer(DataBaseInterface::HeroData h)
{
	return new Player(h.nombre,h.gfxPath,h.hpMax,h.mpMax);
}

//Construye un enemigo con los datos que me pasan
Enemy* Builder::createEnemy(DataBaseInterface::EnemyData e)
{
	return new Enemy(e.idEnemy, e.nombre, e.gfxPath, e.hpMax, e.mpMax, e.strength, e.defense);
}

//Construye una Tool con los datos que me pasan
Tool* Builder::createTool(DataBaseInterface::ToolData t)
{
	return new Tool(t.idTool, t.nombre, t.gfxPath);
}

//Construye un item con los datos que me pasan
Item* createItem(DataBaseInterface::ItemData i)
{
	return new Item(i.idItem, i.tipo, i.pow);
}

//Construye un tileSet con los datos que me pasan
TileSet* createTset(DataBaseInterface::TsetData t)
{
	return new TileSet(t.idTset, t.gfxPath);
}

//Construye un keyItem con los datos que me pasan
KeyItem* createKeyItem(DataBaseInterface::KeyItemData k)
{
	return new KeyItem(k.nombre, k.gfxPath);
}

//Construye un powerUp con los datos que me pasan
PowerUp* createPowerUp(DataBaseInterface::PowerUpData p)
{
	return new PowerUp(p.idPowUp, p.gfxPath, p.tipo, p.pow);
}

Pidgeon* createPidgeon(DataBaseInterface::PigeonData p)
{
	return new Pidgeon(p.nombre, p.gfxPath);
}