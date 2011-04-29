#pragma once

#ifndef _GENPUZZLE_H_
#define _GENPUZZLE_H_

#include "Screen.h"
#include "DunScreen.h"

class GenPuzzle{
	private:
		puzzle_t* puzzle;

	public:
		GenPuzzle(short type);
		~GenPuzzle();

		void generate(DunScreen* ds, short id);

		// genera el puzzle arena sobre ds
		void enemyArena(DunScreen* ds); 
};

#endif