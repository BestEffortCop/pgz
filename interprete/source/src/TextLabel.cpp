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
