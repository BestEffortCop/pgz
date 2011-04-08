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


bool addCharacter(char c, Color color = Color::White){return true;}    //TileTextLabel y TtfTextLabel la implementan
void TextLabel::setText(string myText, TextMode m){}                            //TileTextLabel y TtfTextLabel la implementan a su manera
void TextLabel::onRender(int x, int y){}     
