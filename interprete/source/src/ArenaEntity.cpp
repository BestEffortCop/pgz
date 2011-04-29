#include "ArenaEntity.h"

ArenaEntity::ArenaEntity(int x, int y, Game* g, GameState* gs) : Entity(x,y,g,gs)
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

void ArenaEntity::onNotified(Entity* e)
{
	enemies->remove((Enemy*) e);
}

void ArenaEntity::init(GamePuzzle* puzzle)
{
	GamePuzzleElement::init(puzzle);
}

void ArenaEntity::onStep()
{
	if (!isPuzzleSolved())
		if(enemies->empty())
			puzzle->solve();
}