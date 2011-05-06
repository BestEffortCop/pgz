#include "ArenaEntity.h"

ArenaEntity::ArenaEntity(int x, int y, Game* g, GameState* gs) : Entity(x,y,g,gs)
{
	solid = false;
	collidable = false;
	enemies.clear();
}

ArenaEntity::~ArenaEntity()
{
	enemies.clear();
}

void ArenaEntity::addEnemy(Enemy* e)
{
	enemies.push_back(e);
}

void ArenaEntity::onNotified(Entity* e)
{
//	enemies.remove((Enemy*) e);
}

void ArenaEntity::init(GamePuzzle* puzzle)
{
	GamePuzzleElement::init(puzzle);
}

void ArenaEntity::onStep()
{
	if (!isPuzzleSolved())
		if(enemies.empty())
			puzzle->solve(), instance_destroy();
}

void ArenaEntity::onEndStep()
{
	list<Enemy*>::iterator it = enemies.begin();
	while(it != enemies.end())
	{
		if ((*it)->dead)
		{
			it = enemies.erase(it);
		}
		else
		{
			it++;
		}
	}
}