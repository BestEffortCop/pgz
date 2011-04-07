#pragma once

#ifndef __TEXTLABEL_H__
#define __TEXTLABEL_H__

#include <string>
#include "Font.h"

using namespace std;


class TextLabel
{

private:
	Font* font;
	float scale;
	string myText;
public:

	TextLabel(string myText);   //Pone myText al texto de entrada puede poner la escala a uno

	void setScale(float scale);                                               //Se podria implementar aqui directamente
	/*bool addCharacter(char c, color c= Color::White);    //TileTextLabel y TtfTextLabel la implementan
	void setText(string myText, Mode m);                            //TileTextLabel y TtfTextLabel la implementan a su manera
	int onRender(int x, int y);     
	*/
};
#endif __TEXTLABEL_H__