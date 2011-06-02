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

#ifndef __TILEFONT_H__
#define __TILEFONT_H__

#define NUM_CHAR 94

#include <map>

#include "Font.h"
#include "TileSet.h"


using namespace std;


class TileFont: public Font
{

private:
	map<int, int>* posicion;
	TileSet* tileSet;
public:

	TileFont(string path, GfxEngine* gfxEngine); 
	~TileFont();

	int getGlyphId(char c);
	TileSet* getTileSet();
	int getTileH();
	int getTileW();

};
#endif __TILEFONT_H__