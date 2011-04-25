#pragma once
#ifndef __GAME_MENUTEXTITEM_S_H__
#define __GAME_MENUTEXTITEM_S_H__

#include "GameMenuTextItem.h"
#include "iSelectable.h"

class GameMenuTextItemS : public GameMenuTextItem, public iSelectable
{
public:
	GameMenuTextItemS(std::string text, TileFont* font, int x, int y, Game* game, GameState* gstate);
	~GameMenuTextItemS();
};


#endif