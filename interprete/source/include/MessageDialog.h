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
	FriendlyTileMap* marco;
	TileTextLabel* texto;
	GfxEngine* gfxEngine;
	int nextFrame;
	int step;
	bool restart;
	bool waiting;
	bool finish;
	vector<int>* charMap;
	bool paused;
	Color color;

	int speed;
	FriendlyTileMap* tiledContinue;
	short contFrame;

public:
	
	MessageDialog(Font* font, int col, int row, TileSet* tileSetBackground, GfxEngine* gfxEngine,int x, int y, GameState* gamestate, Game* game);
	~MessageDialog();

	bool setText(string texto);	

	void onStep();
	void onTimer(int n);
	void onRender();

	void initBackgrount(int row, int col);
	void setBackgroundTileSet(TileSet* background);
	void setFont(Font* font);
	void setScale(int scale);
	bool isFinished();
	
};
#endif __MESSAGEDIALOG_H__