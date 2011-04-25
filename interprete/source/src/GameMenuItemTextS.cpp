#include "GameMenuItemTextS.h"

GameMenuItemTextS::GameMenuItemTextS(int x, int y, std::string text, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate), iSelectable(x, y, 0, 0)
{
	font = new TileFont("data/graphics/sprFont_strip94.png", game->getGfxEngine());
	textLabel = new TileTextLabel(text,font,game->getGfxEngine());
}

GameMenuItemTextS::GameMenuItemTextS(int x, int y, std::string text, int w, int h, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate), iSelectable(x, y, w, h)
{
	font = new TileFont("data/graphics/sprFont_strip94.png", game->getGfxEngine());
	textLabel = new TileTextLabel(text,font,game->getGfxEngine());
}

GameMenuItemTextS::~GameMenuItemTextS()
{
}

void GameMenuItemTextS::setText(std::string s)
{
	textLabel->setText(s);
}

void GameMenuItemTextS::onRender()
{
	GameMenuItem::onRender();
	textLabel->render(x,y);
}