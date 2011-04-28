#include "ArenaEntity.h"

ArenaEntity::ArenaEntity()
{
	enemies = new list<Enemy*>();
}

ArenaEntity::~ArenaEntity()
{
	enemies->clear();
	delete enemies;
	enemies = NULL;
}

void ArenaEntity::addEnemy(Enemy* e)
{
	enemies->push_back(e);
}

void ArenaEntity::removeEnemy(Enemy* e)
{
	std::list<Enemy*>::iterator it = enemies->begin();
	while (*it != e)
		it++;
	enemies->erase(it);
}

void ArenaEntity::onNotified(Entity* e)
{
	removeEnemy((Enemy*) e);
}

void ArenaEntity::init(GamePuzzle* puzzle)
{
	GamePuzzleElement::init(puzzle);
}

void ArenaEntity::solvePuzzle()
{
	if (!enemies->empty())
		puzzle->solve();
}