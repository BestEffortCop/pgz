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

#include "MainMenu.h"

MainMenu::MainMenu(int x, int y, Game* game, GameState* gstate, DataBaseInterface* dbi) : GameMenuController(x, y, game, gstate)
{
	setGraphic(new Stamp(dbi->getMainMenu(), game->getGfxEngine()));
	setCursorImage(new Stamp(dbi->getCursor(), game->getGfxEngine()));

	Color colorEnabled = Color(38,38,38);
	Color colorDisabled = Color(138,138,138);

	menuFont = new TileFont(dbi->getFont(), game->getGfxEngine());

	iNewGame = new GameMenuTextItemS("New Game", menuFont, 85, 75, game, gstate);
	iNewGame->setCursorLocation(LEFT);
	iNewGame->getText()->setColor(colorEnabled);

	iLoadGame = new GameMenuTextItemS("Load Game", menuFont, 85, 95, game, gstate);
	iLoadGame->setCursorLocation(LEFT);


	iOptions = new GameMenuTextItemS("Options", menuFont, 85, 115, game, gstate);
	iOptions->setCursorLocation(LEFT);
	iOptions->getText()->setColor(colorDisabled);

	iQuit = new GameMenuTextItemS("Quit", menuFont, 85, 135, game, gstate);
	iQuit->setCursorLocation(LEFT);
	iQuit->getText()->setColor(colorEnabled);


	FILE * f = NULL;
	noSaveFiles = true;
	int i = 0;
	char str[80];
	char buffer[33];
	while (noSaveFiles && i < 3)
	{
		strcpy(str,"data/save");
		strcat(str,itoa(i,buffer,10));
		f = fopen(str, "rb");
		if (f != NULL)
		{
			fclose(f);
			noSaveFiles = false;
		}
		else
		{
			i++;
		}
	}

	if (!noSaveFiles)
		iLoadGame->getText()->setColor(colorEnabled);
	else
		iLoadGame->getText()->setColor(colorDisabled);
}

MainMenu::~MainMenu()
{
	delete menuFont;
}

void MainMenu::launch()
{
	addMenuItem(iNewGame);
	addMenuItem(iLoadGame);
	addMenuItem(iOptions);
	addMenuItem(iQuit);
	GameMenuController::launch();
}

void MainMenu::onStep()
{
	GameMenuController::onStep();
}

void MainMenu::onChosen(iSelectable* selectable)
{
	if (selectable == iQuit)
	{
		game->setFinished(true);
	}
	if (selectable == iNewGame)
	{
		quit();
		//((PGZGame*) game)->startNewgame();


		((PGZGame*) game)->showPrologue();
	}
	if (selectable == iLoadGame){
		if (!noSaveFiles)
		{
		((PGZGame*) game)->changeMenu();
		}
	}
}