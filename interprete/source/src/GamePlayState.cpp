#include "GamePlayState.h"
#include "CollisionTester.h"
#include "TiledPushable.h"
#include "GameItem.h"
#include "TiledEntity.h"
#include "NPC.h"
#include "FireBall.h"

GamePlayState::GamePlayState(int w, int h, Game* g) : GameState(g, w, h)
{
	localEntities = new list<Entity*>();

	offsetX = 0;
	offsetY = 16;

	hudController = NULL;
};

GamePlayState::~GamePlayState()
{
	// Ya se ocupa la destructora padre de borrarlas
	delete localEntities;
};

// Sobrecarga del método padre para notificar al mapa de cambios
bool GamePlayState::_add(Entity* e)
{
	((ScreenMap*) map)->notify(ScreenMap::eCREATE, e);

	return GameState::_add(e);
}

// Sobrecarga del método padre para notificar al mapa de cambios
bool GamePlayState::_remove(Entity* e)
{
	((ScreenMap*) map)->notify(ScreenMap::eDESTROY, e);
	localEntities->remove(e);

	return GameState::_remove(e);
}

// Sobrecarga del método del padre para utilizar la lista de entidades locales
bool GamePlayState::add(Entity* e, bool local)
{
	if (e != NULL)
	{
		if (local)
			add_single(localEntities, e);

		return GameState::add(e);
	}

	return false;
};

bool GamePlayState::addLocal(Entity* e)
{
	return add_single(localEntities, e);
};

bool GamePlayState::add(Entity* e)
{
	return GamePlayState::add(e, true);
};

bool GamePlayState::remove(Entity* e)
{
	if (e != NULL)
	{
		int oldsize = localEntities->size();
		localEntities->remove(e);
		GameState::remove(e);
		return oldsize > localEntities->size();
	}
	return false;
};

// Sobrecarga del método del padre para utilizar la lista de eliminables
bool GamePlayState::removeLocals()
{
	list<Entity*>::iterator it = localEntities->begin();
	while (it != localEntities->end())
	{
        if ((*it) != NULL)
        {
			remove(*it);
        }
		it = localEntities->begin();
	}

	return (localEntities->size() == 0);
};

// Sobrecarga del método del padre para utilizar la lista de eliminables
void GamePlayState::hideLocals()
{
	for(list<Entity*>::iterator it = localEntities->begin();  it != localEntities->end(); it++)
	{
        if ((*it) != NULL)
        {
			(*it)->setVisible(false);
        }
	}
};

void GamePlayState::renderBG()
{
	// Se dibuja un rectángulo para pruebas de gráficos de forma temporal
//	game->getGfxEngine()->renderRectangle(0, 0, roomw, roomh, Color(255, 20, 20));
};

void GamePlayState::renderFG()
{
	// Huds y tal
	if (offsetX == 0 && offsetY == 16)
	{
		game->getGfxEngine()->renderRectangle(0, 0, roomw, 16, Color(50, 50, 50));
		game->getGfxEngine()->renderRectangle(0, roomh-16, roomw, 16, Color(50, 50, 50));

		if (hudController != NULL)
			hudController->onRender();
	}
};

void GamePlayState::onStep()
{
	if (hudController != NULL)
		hudController->onStep();
};

void GamePlayState::onRender()
{
    // Si se desea, se pintarán elementos por debajo de los demás
    renderBG();

    // Si hay mapa, se pinta
    if (map != NULL)
        map->render(offsetX,offsetY);

    list<Entity*>::iterator i;
    // Pintamos todas las entidades visibles
	if (renderable->size() > 0)
		for(i = renderable->begin(); i != renderable->end(); i++)
			if ((*i) != NULL)
			{
				(*i)->x += offsetX;
				(*i)->y += offsetY;
				(*i)->onRender();
				(*i)->x -= offsetX;
				(*i)->y -= offsetY;
			}

    // Si se desea, se pintarán elementos por encima de los demás
    renderFG();
};

void GamePlayState::setOffset(int x, int y)
{
	offsetX = x;
	offsetY = y;
};

std::pair<int, int> GamePlayState::getOffset()
{
	return make_pair(offsetX, offsetY);
}

void GamePlayState::pauseGameEntities()
{
	GameEntity* ent;
	std::list<Entity*>::iterator it = entities->begin();
	while (it != entities->end())
	{
		if (ent = dynamic_cast<GameEntity*>((*it)))
			ent->pause();
		it++;
	}
};

void GamePlayState::unpauseGameEntities()
{
	GameEntity* ent;
	std::list<Entity*>::iterator it = entities->begin();
	while (it != entities->end())
	{
		if (ent = dynamic_cast<GameEntity*>((*it)))
			ent->unpause();
		it++;
	}
};

Map* GamePlayState::getMap()
{
	return map;
}