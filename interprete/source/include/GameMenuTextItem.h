#pragma once
#ifndef __GAME_MENUTEXTITEM_H__
#define __GAME_MENUTEXTITEM_H__

#include "GameMenuItem.h"
#include "TextLabel.h"

class GameMenuTextItem : public GameMenuItem
{
public:
	GameMenuTextItem(TextLabel* text, int x, int y, Game* game, GameState* gstate);
	~GameMenuTextItem();

	void setPos(int x, int y);
	void setText(TextLabel* s);
};

#endif