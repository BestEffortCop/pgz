#pragma once

#ifndef _DUNGEONINFO_H_
#define _DUNGEONINFO_H_

//using namespace std;

class DungeonInfo{
	private:
		// Herramienta que contiene la mazmorra.
		int toolId;
		// Número de orden de mazmorra, relacionado con su dificultad
		int order;	
		// Habria que ver que más quiere el genDungeon: bool boss, objetoClave ... ?

	public:
		// Constructora
		DungeonInfo(int tooldId, int order);
		// Destructora
		~DungeonInfo();
};

#endif
