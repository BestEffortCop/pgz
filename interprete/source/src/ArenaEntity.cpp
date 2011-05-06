#include "ArenaEntity.h"

ArenaEntity::ArenaEntity(int x, int y, Game* g, GameState* gs) : Entity(x,y,g,gs)
{
	solid = false;
	collidable = false;
	enemies.clear();
}

ArenaEntity::~ArenaEntity()
{
	
	/*Enemy* tmp = NULL;
	list<Enemy*>::iterator it = enemies.begin();
	while (it != enemies.end())
	{
		delete (*it);
		list<Enemy*>::iterator it = enemies.begin();
	}*/
	enemies.clear();

}

void ArenaEntity::addEnemy(Enemy* e)
{
	enemies.push_back(e);
	e->persistent = true;
}

void ArenaEntity::onNotified(Entity* e)
{
	enemies.remove((Enemy*) e);
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
	/*
	Enemy* tmp = NULL;
	for (list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
	{
		if ((*it)->dead)
		{
			tmp = (*it);
			enemies.remove((*it));
			if (tmp != NULL)
				delete tmp;
		}
	}*/
}