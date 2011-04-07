#include "TextLabel.h"


TextLabel::TextLabel(string myText)
{
	//Pongo la escala a uno de manera predeterminada
	scale = 1;
	//Pongo el texto que luego tendré que pintar
	this->myText = myText;
}  

void TextLabel::setScale(float scale) {this->scale = scale;} 

/*	SEGUIR POR AQUI
bool TextLabel::addCharacter(char c, color c= Color::White)    //TileTextLabel y TtfTextLabel la implementan
void TextLabel::setText(string myText, Mode m)                            //TileTextLabel y TtfTextLabel la implementan a su manera
int TextLabel::onRender(int x, int y)     
*/