#pragma once
#ifndef __INTROSTATE_H__
#define __INTROSTATE_H__

#include "Gamestate.h"
#include "PGZGame.h"
#include "TileTextLabel.h"

class MessageDialog;

class IntroState : public GameState
{

private:
	TileFont* font;
	TileSet* bg;

	list<TileTextLabel*> textlist;
	MessageDialog* m;

public:
	IntroState(int w, int h, Game* g);
	~IntroState();

	void onStep();
	void renderBG();

	bool remove(Entity* e);

	void loadText(std::string path);
};

#endif