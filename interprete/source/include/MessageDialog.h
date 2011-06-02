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

#pragma once

#ifndef __MESSAGEDIALOG_H__
#define __MESSAGEDIALOG_H__

#include <vector>

#include "TileTextLabel.h"
#include "Entity.h"
#include "PGZGame.h"

using namespace std;


class MessageDialog:public Entity
{

private:
	FriendlyTileMap* marco;
	TileTextLabel* texto;
	GfxEngine* gfxEngine;
	int nextFrame;
	int step;
	bool restart;
	bool waiting;
	bool finish;
	vector<int>* charMap;
	bool paused;
	Color color;

	int speed;
	FriendlyTileMap* tiledContinue;
	short contFrame;

public:
	
	MessageDialog(Font* font, int col, int row, TileSet* tileSetBackground, GfxEngine* gfxEngine,int x, int y, GameState* gamestate, Game* game);
	~MessageDialog();

	bool setText(string texto);	

	void onStep();
	void onTimer(int n);
	void onRender();

	void initBackgrount(int row, int col);
	void setBackgroundTileSet(TileSet* background);
	void setFont(Font* font);
	void setScale(int scale);
	bool isFinished();
	
};
#endif __MESSAGEDIALOG_H__