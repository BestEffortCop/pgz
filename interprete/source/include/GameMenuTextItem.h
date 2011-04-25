#pragma once
#ifndef __GAME_MENUTEXTITEM_H__
#define __GAME_MENUTEXTITEM_H__

#include "GameMenuItem.h"
#include "TileTextLabel.h"

class GameMenuTextItem : public GameMenuItem
{
protected:

	TileFont* font;
	TileTextLabel* textLabel;

	std::string text;

public:
	// Constructora si el texto es un TileTextLabel
	GameMenuTextItem(std::string text, TileFont* font, int x, int y, Game* game, GameState* gstate);

	~GameMenuTextItem();

	void setPos(int x, int y);
	void setText(std::string s);

	TileTextLabel* getText();

	// Cambia el texto a TileTextLabel con la nueva fuente
	void setFont(TileFont* font);
};

#endif