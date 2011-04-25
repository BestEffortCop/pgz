#include "GameMenuTextItemS.h"


GameMenuTextItemS::GameMenuTextItemS(std::string text, TileFont* font, int x, int y, Game* game, GameState* gstate) : GameMenuTextItem(text, font, x, y, game, gstate), iSelectable(x, y, textLabel->getTileW()*textLabel->getColumns(), textLabel->getTileH()*textLabel->getRows()) 
{
}


GameMenuTextItemS::~GameMenuTextItemS()
{
}
