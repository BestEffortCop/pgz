#include "GameMenuTextItem.h"


GameMenuTextItem::GameMenuTextItem(std::string text, TileFont* font, int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate)
{
	this->text = text;
	//font = new TileFont("data/graphics/sprFont_strip94.png", game->getGfxEngine());
	this->font = font;
	graphic = new TileTextLabel(text,font,game->getGfxEngine());
	textLabel = (TileTextLabel*) graphic;
}

GameMenuTextItem::~GameMenuTextItem()
{
}

void GameMenuTextItem::setPos(int x, int y)
{
	GameMenuItem::setPos(x, y);
}

void GameMenuTextItem::setText(std::string s)
{
	this->text = s;
	textLabel->setText(s);
}

TileTextLabel* GameMenuTextItem::getText()
{
	return textLabel;
}

void GameMenuTextItem::setFont(TileFont* font)
{
	if (graphic != NULL)
		delete graphic;

	this->font = font;
	graphic = new TileTextLabel(text,font,game->getGfxEngine());
	textLabel = (TileTextLabel*) graphic;
}