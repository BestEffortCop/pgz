#include "GameFinalItem.h"


GameFinalItem::GameFinalItem(int x, int y, Game* game, GameState* world) : GameEntity(x, y, game, world), iInteractable()
{
	solid = true;
	type = "finalItem";
}

GameFinalItem::~GameFinalItem() 
{

}

void GameFinalItem::init(string graphicpath, Controller* c) {
	controller = c;

	graphic = new Stamp(graphicpath, game->getGfxEngine());
	mask = new MaskBox(x, y, graphic->getWidth(), graphic->getHeight(), "finalItem", 0, 0); 
}

void GameFinalItem::onEndInteract(){
	controller->changeGameStateTo(Controller::TITLE);
}

void GameFinalItem::onInteract(Player* p) {
	this->controller->getMessageController()->showMessage("Congratulations! Peace is restored!");
}
