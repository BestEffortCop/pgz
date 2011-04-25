#pragma once
#ifndef __GAME_MENUITEMTEXTS_H__
#define __GAME_MENUITEMTEXTS_H__

#include "GameMenuItem.h"
#include "iSelectable.h"
#include "TileTextLabel.h"

class GameMenuItemTextS : public GameMenuItem, public iSelectable
{
	protected:
		TileFont* font;
		TileTextLabel* textLabel;
	public:
		GameMenuItemTextS(int x, int y, std::string text, Game* game, GameState* gstate);
		GameMenuItemTextS(int x, int y, std::string text, int w, int h, Game* game, GameState* gstate);
		virtual ~GameMenuItemTextS();

		void setText(std::string s);
		void onRender();
};

#endif