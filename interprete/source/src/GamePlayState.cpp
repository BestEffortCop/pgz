#include "GamePlayState.h"
#include "CollisionTester.h"
#include "PushableTester.h"
#include "GameItem.h"
#include "TiledEntity.h"

GamePlayState::GamePlayState(int w, int h, Game* g) : GameState(g, w, h)
{
	localEntities = new list<Entity*>();
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

	return NULL;
};

// Sobrecarga del método del padre para utilizar la lista de eliminables
bool GamePlayState::removeLocals()
{

	list<Entity*>::iterator it = localEntities->begin();
	while (it != localEntities->end())
	{
        if ((*it) != NULL)
        {
			_remove(*it);
			localEntities->remove(*it);
        }
		it = localEntities->begin();
	}

	return (localEntities->size() == 0);
};

void GamePlayState::renderBG()
{
	// Se dibuja un rectángulo para pruebas de gráficos de forma temporal
	//game->getGfxEngine()->renderRectangle(1, 1, roomw-2, roomh-2, Color::Blue, true);
};

void GamePlayState::onStep()
{
	if (game->getInput()->keyPressed(Input::kN))
		add(new CollisionTester(14*16, rand()%12*16, game, this));

	if (game->getInput()->keyPressed(Input::kT))
		add(new PushableTester(64, 64, game, this));

	if (game->getInput()->keyPressed(Input::kI))
	{
		GameItem* it = new GameItem(16*(2+rand()%10), 16*(2+rand()%8), game, this);
		int n = rand()%4;
		if (n == 0)
			it->init("data/graphics/heart.png", GameItem::ieHP, 4);
		else if (n == 1)
		{
			it->init("data/graphics/heart.png", GameItem::ieMP, 7);
			it->graphic->setColor(Color::Blue);
		}
		else if (n == 2)
			it->init("data/graphics/rupee.png", GameItem::ieMONEY, 5);
		else
			it->init("data/graphics/key.png", GameItem::ieKEY, 1);

		add(it);
	}

	if (game->getInput()->keyPressed(Input::kP))
	{
		int xx = (2+rand()%10)*16, yy = (2+rand()%8)*16;
		TiledEntity* te = new TiledEntity(xx, yy, game, this);
		te->init(map->getTileset(), 2);
		add(te);
		te = new TiledEntity(xx, yy-16, game, this);
		te->init(map->getTileset(), 3, true);
		add(te);
	}
	
	if (game->getInput()->keyPressed(Input::kB)) {
		NPC* npc = new NPC(16*(2+rand()%10), 16*(2+rand()%8), game, this);
		npc->init("data/graphics/npc.png", 3, 4);
		add(npc);
	}
};