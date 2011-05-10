#pragma once

#ifndef __STATEMENU_H__
#define __STATEMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"
#include "FriendlyTileMap.h"

#include "Stamp.h"
#include "PGZGame.h"



class StateMenu : public GameMenuController
{

protected:
	GameMenuTextItemS* save;
	GameMenuTextItemS* exit;
	GameMenuTextItem* tPidgeons;

	//Porque tenemos que dibujar tantos como maximo de keyitems halla
	vector<GameMenuItem*>* keyItems;

	GameMenuItem* miniMap;
	GameMenuItem* bossKey;
	GameMenuItem* pidgeons;

	TileFont* menuFont;

	FriendlyTileMap* getMiniMap();

public:
	
	StateMenu(int x, int y, Game* game, GameState* gstate);
	~StateMenu();

	void launch();
	
	//void onStep();
	void onRender();
	//void onChosen(iSelectable* selectable);*/
	void onCancelled(iSelectable* selectable);
	/*
	iSelectable* getMandatorySelectable(iSelectable* slc, Direction dir);
	iSelectable* getAlternativeSelectable(iSelectable* slc, Direction dir);
	*/
};

#endif __STATEMENU_H__
