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

#ifndef __TEXTLABEL_H__
#define __TEXTLABEL_H__


#include <string>
#include "Font.h"
#include "Graphic.h"

enum TextMode {APPEND, REWRITE};

using namespace std;


class TextLabel:public Graphic
{

protected:
	Font* font;
	float scale;
	string myText;
public:

	TextLabel(string myText);   //Pone myText al texto de entrada puede poner la escala a uno

	virtual void setScale(float scale);                                    
	virtual bool addCharacter(char c, Color color = Color::White);			//TileTextLabel y TtfTextLabel la implementan
	virtual int setText(string myText, TextMode m);                        //TileTextLabel y TtfTextLabel la implementan a su manera
	virtual void render(int x, int y);									//TileTextLabel y TtfTextLabel la implementan
	
};
#endif __TEXTLABEL_H__