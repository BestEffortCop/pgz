#include "LoadBlock.h"

LoadBlock::LoadBlock(/*int i, Controller* c,FILE* file, TileFont* font, int x, int y, Game* game, GameState* gstate*/){/* : GameMenuItem(x, y, game, gstate), iSelectable(x, y, 100,100){
	controller = c;
	this->font = font;
	id = i;

	// Hacemos una carga parcial de los datos
	controller->getData()->load(file, true);

	char buffer[33];
	fileDisplay = new TileTextLabel("file " + i, font, game->getGfxEngine(),6, 1);

	itoa(controller->getData()->getCurrentMoney(), buffer, 10);
	moneyDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 5, 1);

	iMoney = new Stamp("data/Gfx/rupee.png", game->getGfxEngine());
	itoa(controller->getData()->getCurrentHeartPieces(), buffer, 10);
	heartPiecesDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 7, 1);

	itoa(controller->getData()->getNumPigeons(), buffer, 10);
	pigeonsDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);
	iKey = new Stamp("data/Gfx/key.png", game->getGfxEngine());

	//itoa(controller->getData()->getGameProgress(), buffer, 10);
	//progressDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);
	//itoa(controller->getData()->getCurrentHeartPieces(), buffer, 10);
	//timePlayedDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);

	//dateDisplay = new TileTextLabel(, font, game->getGfxEngine(), 3, 1);


	int yy = y+4, hpx = x+64, mpx = x+128, moneyx = x+168, keyx = x+200;

	moneyDisplay->render(moneyx, yy);
	fileDisplay->render(x + 4, (y + 4)*i);
	heartPiecesDisplay->render(x + 64, (y + 4)*i);
	
	//keyDisplay->render(keyx, yy);*/
}

LoadBlock::~LoadBlock(){
	delete fileDisplay;
	delete moneyDisplay;
	delete pigeonsDisplay;
	delete heartPiecesDisplay;

	//delete timePlayedDisplay;
	//delete dateDisplay;
	//delete progressDisplay;
}

int LoadBlock::getID(){
	return id;
}