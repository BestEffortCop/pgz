#pragma once
#ifndef __INSTANTIATOR_H__
#define __INSTANTIATOR_H__

#include "GamePlayState.h"
#include "Entity.h"
#include "GamePuzzleListener.h"

class Instantiator : public Entity, public GamePuzzleListener
{
protected:
	std::list<Entity*> toSpawn;
public:
	Instantiator(Game* g, GameState* gs) : Entity(-1, -1, g, gs), GamePuzzleListener()
	{
		toSpawn.clear();
		collidable = false;
	};

	~Instantiator()
	{
		// Se eliminan todas las entidades que no se hayan llegado a spawnear
		std::list<Entity*>::iterator it = toSpawn.begin();
		while (it != toSpawn.end())
			delete (*it), it++;

		toSpawn.clear();
	};

	void addEntity(Entity* e)
	{
		if (isPuzzleSolved())
			((GamePlayState*)world)->add(e);
		else
			toSpawn.push_back(e);
	};

	void removeEntity(Entity* e)
	{
		int oldsize = toSpawn.size();
		toSpawn.remove(e);
		// Si estaba en la lista, la borramos
		if (e != NULL)
			if (oldsize > toSpawn.size())
				delete e;
	};

	void onSolve()
	{
		// Se añaden todas las entidades
		std::list<Entity*>::iterator it = toSpawn.begin();
		while (it != toSpawn.end())
		{
			if ((*it) != NULL)
				((GamePlayState*)world)->add((*it));
			toSpawn.remove((*it));
			it = toSpawn.begin();
		}

		instance_destroy();
	};
};

#endif