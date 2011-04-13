#pragma once

#ifndef __MESSAGEDIALOG_H__
#define __MESSAGEDIALOG_H__

#include <vector>

#include "TileTextLabel.h"
#include "Entity.h"

using namespace std;


class MessageDialog:public Entity
{

private:
	TileMap* marco;
	TileTextLabel* texto;
	int nextframe;
	vector<int>* charMap;
	bool paused;
	int colour;

public:
	/*
	MessageDialog(Font* font, int w, int h, GfxEngine* gfxEngine,int x, int y, GameState* gamestate, Game* game, TileSet* tileSetBackGround);
	~MessageDialog();

	bool setText(string texto);//Debe encargarse tambien de fijar a partir del tamaño que le deja el marco y de la escala el numero de filas y columnas del texto

	void onStep();
	void onRender();

	void setBackgroundTileSet(tileSet* background);
	void setFont(Font* font);
	void setScale(int scale);
	*/
};
#endif __MESSAGEDIALOG_H__