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

#include "TextLabel.h"


TextLabel::TextLabel(string myText)
{
	//Pongo la escala a uno de manera predeterminada
	scale = 1;
	//Pongo el texto que luego tendré que pintar
	this->myText = myText;
}  

//setter del atributo scale
void TextLabel::setScale(float scale) {this->scale = scale;} 


bool TextLabel::addCharacter(char c, Color color){return true;}    //TileTextLabel y TtfTextLabel la implementan
int TextLabel::setText(string myText, TextMode m) {return 0;}                            //TileTextLabel y TtfTextLabel la implementan a su manera
void TextLabel::render(int x, int y) {}
