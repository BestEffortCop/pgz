#include "LoadBlock.h"
#include "PGZGame.h"

LoadBlock::LoadBlock(int i, FILE* file, TileFont* font, int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate), iSelectable(x, y, 100,100){
	this->font = font;
	id = i;

	setGraphic(new Stamp("data/loadBlock.png"/*dbi->getLoadMenu()*/, game->getGfxEngine()));
	// Hacemos una carga parcial de los datos
	((PGZGame*)game)->controller->getData()->load(file);

	char buffer[33];
	char str[80];
	strcpy (str,"file ");
	strcat (str,itoa(i,buffer,10));
	fileDisplay = new TileTextLabel(str, font, game->getGfxEngine(),6, 1);

	itoa(((PGZGame*)game)->controller->getData()->getCurrentMoney(), buffer, 10);
	moneyDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 5, 1);

	iMoney = new Stamp("data/Gfx/rupee.png", game->getGfxEngine());
	itoa(((PGZGame*)game)->controller->getData()->getCurrentHeartPieces(), buffer, 10);
	heartPiecesDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 7, 1);

	itoa(((PGZGame*)game)->controller->getData()->getNumPigeons(), buffer, 10);
	pigeonsDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);
	iKey = new Stamp("data/Gfx/key.png", game->getGfxEngine());

	//itoa(((PGZGame*)game)->controller->getData()->getGameProgress(), buffer, 10);
	//progressDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);
	//itoa(controller->getData()->getCurrentHeartPieces(), buffer, 10);
	//timePlayedDisplay = new TileTextLabel(buffer, font, game->getGfxEngine(), 3, 1);

	//dateDisplay = new TileTextLabel(, font, game->getGfxEngine(), 3, 1);


	int yy = y+4, hpx = x+64, mpx = x+128, moneyx = x+168, keyx = x+200;

	moneyDisplay->render(moneyx, yy*i);
	fileDisplay->render(x + 4, (y + 4)*i);
	heartPiecesDisplay->render(x + 64, (y + 4)*i);
	pigeonsDisplay->render(moneyx, yy*i + 10);
	iMoney->render(moneyx - 8,yy-1);
	iKey->render(keyx - 8,0);
	//keyDisplay->render(keyx, yy);

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