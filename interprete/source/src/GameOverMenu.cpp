/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "GameOverMenu.h"


GameOverMenu::GameOverMenu(int x, int y, Game* game, GameState* gstate, DataBaseInterface* dbi) : GameMenuController(x, y, game, gstate)
{
	//((GamePlayState*) world)->pauseGameEntities();

	bgImage = new Image(game->getGfxEngine()->getGameScreenWidth(),game->getGfxEngine()->getGameScreenHeight(),game->getGfxEngine());
	game->getGfxEngine()->renderRectangle(0,0, game->getGfxEngine()->getGameScreenWidth(), 
											game->getGfxEngine()->getGameScreenHeight(), Color::Black,false,bgImage);

	setGraphic(new Stamp(bgImage,game->getGfxEngine()));
	setCursorImage(new Stamp(dbi->getCursor(), game->getGfxEngine()));

	menuFont = new TileFont(dbi->getFont(), game->getGfxEngine());

	iLoad = new GameMenuTextItemS("Continue", menuFont, 85, 75, game, gstate);
	iLoad->setCursorLocation(LEFT);

	iQuit = new GameMenuTextItemS("Quit", menuFont, 85, 85, game, gstate);
	iQuit->setCursorLocation(LEFT);
}

GameOverMenu::~GameOverMenu()
{
	delete menuFont;
	delete bgImage;
}

void GameOverMenu::launch()
{
	addMenuItem(iLoad);
	addMenuItem(iQuit);
	GameMenuController::launch();
	setSelected(iLoad);
}

void GameOverMenu::onRender()
{
	if (visible)
	{
		Entity::onRender();
		if (cursorImage)
			cursorImage->render(cursorPosX + ((GamePlayState*) world)->getOffset().first, cursorPosY + ((GamePlayState*) world)->getOffset().second);
	}
}

void GameOverMenu::onChosen(iSelectable* selectable)
{
	if (selectable == iQuit)
	{
		((PGZGame*)game)->controller->changeGameStateTo(Controller::TITLE);
	}
	if (selectable == iLoad)
	{
		for ( int i = 0; i < ((PGZGame*) game)->controller->getNumPlayers(); i++)
			((PGZGame*) game)->controller->getPlayer(i)->revive();
		quit();
	}
}