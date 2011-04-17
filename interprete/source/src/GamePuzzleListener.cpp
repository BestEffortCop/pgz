#include "GamePuzzleListener.h"

GamePuzzleListener::GamePuzzleListener()
{
	puzzle = NULL;
	listenerId = -1;
};

GamePuzzleListener::~GamePuzzleListener()
{
	if (puzzle != NULL && listenerId >= 0)
		puzzle->removeListener(this);
	listenerId = -1;
	puzzle = NULL;
};

void GamePuzzleListener::init(GamePuzzle* puzzle, int id)
{
	this->puzzle = puzzle;

	if (puzzle == NULL)
		return;

	// Si id < 0 se autosuscribe
	if (id < 0)
		listenerId = puzzle->addListener(this);
	else
		// Si no, ya nos han suscrito
		listenerId = id;

	if (isPuzzleSolved())
		onSolve();
	else
		onUnsolve();
};

GamePuzzle* GamePuzzleListener::getPuzzle()
{
	return puzzle;
};

int GamePuzzleListener::getListenerId()
{
	return listenerId;
};

void GamePuzzleListener::onSolve()
{
	// To be overriden
};

void GamePuzzleListener::onUnsolve()
{
	// To be overriden
};

bool GamePuzzleListener::isPuzzleSolved()
{
	return puzzle->isSolved();
};