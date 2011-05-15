#include "LoadBlock.h"

LoadBlock::LoadBlock(int i, Controller* c,FILE* file, TileFont* font, int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate), iSelectable(x, y, 100,100){
	controller = c;
	this->font = font;
	id = i;

	// Hacemos una carga parcial de los datos
	controller->getData()->load(file, true);

	char buffer[33];
	fileDisplay = new TileTextLabel("file " + i, font, game->getGfxEngine(),6, 1);
	itoa(controller->getData()->getCurrentMoney(), buffer, 10);
	moneyDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);
	itoa(controller->getData()->getGameProgress(), buffer, 10);
	progressDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);
	itoa(controller->getData()->getCurrentHeartPieces(), buffer, 10);
	heartPiecesDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 7, 1);
	//itoa(controller->getData()->getCurrentHeartPieces(), buffer, 10);
	//timePlayedDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);

	//dateDisplay = new TileTextLabel(, font, game->getGfxEngine(), 3, 1);
	itoa(controller->getData()->getNumPigeons(), buffer, 10);
	pigeonsDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);

	cancelDisplay = new TileTextLabel("Cancel", font, game->getGfxEngine(),6, 1);

	int yy = y+4, hpx = x+64, mpx = x+128, moneyx = x+168, keyx = x+200;

	/*hpDisplay->render(hpx, yy);
	mpDisplay->render(mpx, yy);
	moneyDisplay->render(moneyx, yy);
	keyDisplay->render(keyx, yy);*/
	fileDisplay->render(x + 4, (y + 4)*i);
	heartPiecesDisplay->render(x + 64, (y + 4)*i);
	//moneyDisplay->render(
}

LoadBlock::~LoadBlock(){
	delete fileDisplay;
	delete hpDisplay;
	delete progressDisplay;
	delete moneyDisplay;
	delete pigeonsDisplay;
	//delete timePlayedDisplay;
	//delete dateDisplay;
	delete heartPiecesDisplay;
}

int LoadBlock::getID(){
	return id;
}