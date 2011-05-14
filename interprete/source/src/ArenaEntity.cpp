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
	if (isPuzzleSolved())
		e->setVisible(false);
	enemies.push_back(e);
	e->arena = this;
}

void ArenaEntity::onNotified(Entity* e)
{
//	enemies.remove((Enemy*) e);
}

void ArenaEntity::init(GamePuzzle* puzzle)
{
	/*// Siempre que se crea un arenaEntity, debe
	// desresolverse el puzzle, o eliminar a los malos
	puzzle->unsolve();*/
	GamePuzzleElement::init(puzzle);
}

void ArenaEntity::onStep()
{
	if (!isPuzzleSolved())
	{
		if(enemies.empty())
			puzzle->solve(), instance_destroy();
	}
	else
	{
		// Puzzle Resuelto
		list<Enemy*>::iterator it = enemies.begin();
		while (it != enemies.end())
		{
			if ((*it) != NULL)
				(*it)->instance_destroy();
			it++;
		}
		enemies.clear();
	}
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