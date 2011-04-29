#include "GenPuzzle.h"

GenPuzzle::GenPuzzle(short type) {
	puzzle = new puzzle_t;

	puzzle->type = type;
};

GenPuzzle::~GenPuzzle() {
	delete puzzle;
};

void GenPuzzle::generate(DunScreen* ds, short id) {
	
	puzzle->id = id;

	switch(puzzle->type){
		case(0):
			enemyArena(ds);
			break;
	}

	// Añade al vector de puzzles tipo e identificación tal vez debería ser lista enlazada en vez de vector?
	ds->setPuzzle(puzzle);
}

void GenPuzzle::enemyArena(DunScreen* ds) {
	// Coloca enemigosds->setEnemies(); blabla
	// Añadir entidad resultante al generar puzzle puzzle->setEntity();
}

