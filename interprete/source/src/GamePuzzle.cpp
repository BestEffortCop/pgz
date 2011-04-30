#include "GamePuzzle.h"

GamePuzzle::GamePuzzle(int id, MapStatus* mapStatus, Game* g, GameState* gs) : Entity(-1, -1, g, gs)
{
	collidable = false;

	puzzleId = id;
	myMap = mapStatus;

	subscribers.clear();
};

GamePuzzle::~GamePuzzle()
{
	// Se elimina la suscripción de los listeners
	std::list<GamePuzzleListener*>::iterator it = subscribers.begin();
	while (it != subscribers.end())
	{
		(*it)->init(NULL, -1);
		it++;
	}
};

int GamePuzzle::addListener(GamePuzzleListener* listener)
{
	subscribers.push_back(listener);
	return subscribers.size()-1;
};

bool GamePuzzle::removeListener(GamePuzzleListener* listener)
{
	unsigned int oldsize = subscribers.size();
	subscribers.remove(listener);
	return oldsize > subscribers.size();
};

void GamePuzzle::solve()
{
	if (puzzleId >= 0)
		// Se resuelve el puzzle
		myMap->setPuzzleStatus(puzzleId, true);

	// y se avisa a los listeners aun si no hay puzzleId
	std::list<GamePuzzleListener*>::iterator it = subscribers.begin();
	while (it != subscribers.end())
	{
		(*it)->onSolve();
		it++;
	}
};

void GamePuzzle::unsolve()
{
	if (puzzleId >= 0)
		// Se desresuelve el puzzle
		myMap->setPuzzleStatus(puzzleId, false);

	// y se avisa a los listeners aun si no hay puzzleId
	std::list<GamePuzzleListener*>::iterator it = subscribers.begin();
	while (it != subscribers.end())
	{
		(*it)->onUnsolve();
		it++;
	}
};

bool GamePuzzle::isSolved()
{
	return myMap->getPuzzleStatus(puzzleId);
};

int GamePuzzle::getPuzzleId()
{
	return puzzleId;
};