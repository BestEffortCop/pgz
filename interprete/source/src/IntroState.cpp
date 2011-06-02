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

#include "IntroState.h"
#include <iostream>
#include <fstream>

IntroState::IntroState(int w, int h, Game* g) : GameState(g, w, h)
{
	font = new TileFont(((PGZGame*) game)->controller->getDataBaseInterface()->getFont(), game->getGfxEngine());
	bg = new TileSet(((PGZGame*) game)->controller->getDataBaseInterface()->getSystemDummy(),8,8,game->getGfxEngine());

	textlist.clear();
	loadText("./data/prologue.txt");
}


IntroState::~IntroState()
{
	if (font != NULL)
		delete font;
	if (bg != NULL)
		delete bg;
	if (m != NULL)
		delete m;
}


void IntroState::onStep()
{
	if (game->getInput()->keyPressed(((PGZGame*) game)->controller->mainInputConfig.keySTART))
		((PGZGame*) game)->startNewgame();
};

bool IntroState::remove(Entity* e)
{
	if (e == m)
	{
		m = NULL;
		((PGZGame*) game)->startNewgame();
	}

	return GameState::remove(e);

}
void IntroState::renderBG()
{
	game->getGfxEngine()->renderRectangle(0, 0, roomw, roomh, Color::Black);
}

void IntroState::loadText(std::string path)
{
	ifstream file (path);

	TileTextLabel* label;
	std::string line;
	std::string tmp;

	while ( file.good() )
	{
		getline(file,tmp);
		if (file.good())
		{
			tmp.append("\n");
			tmp.append("\n");
		}
		line.append(tmp);
	}

	m = new MessageDialog(font,27,30,bg,game->getGfxEngine(),0,0,this,game);
	m->setText(line);
	add(m);

	file.close();
}