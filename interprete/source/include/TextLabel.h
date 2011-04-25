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