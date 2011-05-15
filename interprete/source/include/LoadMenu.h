#pragma once
#ifndef __LOADMENU_H__
#define __LOADMENU_H__

#include "GameMenuController.h"
#include "GameMenuTextItemS.h"
#include "DataBaseInterface.h"

#include "Stamp.h"
#include "PGZGame.h"
#include "LoadBlock.h"
#include <vector>

class LoadMenu : public GameMenuController {
	private:
		vector<LoadBlock*>* loadBlocks; // Vector con lo bloques de carga
		TileFont* menuFont;				// Fuente
		int numSaves;					// Número de partidas
		GameMenuTextItemS* cancel;		// Botón cancelar

	public:
		LoadMenu(int x, int y, Game* game, GameState* gstate, DataBaseInterface* dbi);
		~LoadMenu();

		void launch();

		void onStep();
		void onChosen(iSelectable* selectable);
};

#endif