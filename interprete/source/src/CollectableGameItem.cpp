#include "CollectableGameItem.h"

#include "Player.h"

CollectableGameItem::CollectableGameItem(int x, int y, Game* g, GameState* gs) : GameItem(x, y, g, gs)
{
};

void CollectableGameItem::init(int idCollectable, MapStatus* mapstatus, std::string gfxPath, ItemType t, int power)
{
	myMapStatus = mapstatus;
	this->idCollectable = idCollectable;
	GameItem::init(gfxPath, t, power);
};

void CollectableGameItem::onInit()
{
	if (myMapStatus->getCollectableStatus(idCollectable))
		setVisible(false), instance_destroy();
};

void CollectableGameItem::applyEffect(Entity* target)
{
	// Una vez actuado, ya nunca más
	if (idCollectable >= 0)
		myMapStatus->setCollectableStatus(idCollectable, true);
	// Se hace al player reproducir animación de oh yeah!
	((Player*) target)->playAnim(Player::Slash, DOWN);
	// Y se aplica el efecto
	GameItem::applyEffect(target);
};