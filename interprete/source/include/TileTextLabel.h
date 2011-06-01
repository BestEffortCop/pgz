/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef __TILETEXTLABEL_H__
#define __TILETEXTLABEL_H__


#include "TextLabel.h"
#include "TileFont.h"
#include "FriendlyTileMap.h"

using namespace std;


class TileTextLabel:public TextLabel
{
private:

	FriendlyTileMap* tileMap;
	GfxEngine* gfxEngine;
	TileFont* tileFont;
	bool sizeSetted;

public:
	//Constructoras y destructora
	TileTextLabel(string texto, Font* font, GfxEngine* gfxEngine,int columns = 0, int rows = 0);
	TileTextLabel(Font* font, GfxEngine* gfxEngine,int columns = 0, int rows = 0);
	~TileTextLabel();

	//Setters && getters
	void setScale(float scale);
	void setColor(Color c);
	void setRotation(float angle);
	void setAlpha(float alpha);

	void setSize(int rows, int columns);
	int getTileH();
	int getTileW();
	int getColumns();
	int getRows();
	int getWidth();
	int getHeight();

	//Escribe un caracter del color que quieras al final del texto actual siempre y cuando le quepa, 
	//Devuelve si ha podido escribirlo o no
	bool addCharacter(char c, Color color = Color::White);

	//Escribe un etxto completo que puede escribir por completo o añadirlo al final del mismo
	//Si nunca se han configurado las filas y columnas las gestiona el solo y si no cabe hace que quepa
	//si no simplemente deja de escribir, en cualquier caso devuelve cuantos caracteres ha escrito
	int setText(string myText, TextMode m = REWRITE);

	//Pinta el texto por pantalla
	void render(int x, int y);

};
#endif __TILETEXTLABEL_H__