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