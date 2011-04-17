#include "GamePuzzleElement.h"

GamePuzzleElement::GamePuzzleElement()
{
	puzzle = NULL;
};

GamePuzzleElement::~GamePuzzleElement()
{
	puzzle = NULL;
};

void GamePuzzleElement::init(GamePuzzle* puzzle)
{
	this->puzzle = puzzle;
};

void GamePuzzleElement::solvePuzzle()
{
	puzzle->solve();
};

void GamePuzzleElement::unsolvePuzzle()
{
	puzzle->unsolve();
};

bool GamePuzzleElement::switchPuzzle()
{
	if (puzzle->isSolved())
	{
		puzzle->unsolve();
		return false;
	}
	else
	{
		puzzle->solve();
		return true;
	}
};

bool GamePuzzleElement::isPuzzleSolved()
{
	return (puzzle->isSolved());
};
