#include "GamePlayState.h"
#include "CollisionTester.h"
#include "PushableTester.h"
#include "GameItem.h"
#include "TiledEntity.h"

GamePlayState::GamePlayState(int w, int h, Game* g) : GameState(g, w, h)
{/*
	// Se instancia el Controlador, que instancia todo
	// Quizás yo tengo que guardar punteros?*/
};

GamePlayState::~GamePlayState()
{
	// eliminar datos que tenga, controller & such
	//delete controller;
	// limpiar deathRow y borrarlo
};

// Sobrecarga del método del padre para utilizar la lista de eliminables
bool GamePlayState::add(Entity* e, bool condemned)
{
	// pensar
	return GameState::add(e);
};

// Sobrecarga del método del padre para utilizar la lista de eliminables
bool GamePlayState::removeEntity(Entity* e)
{
	// (Work in Progress)

	// En principio esto se llama ya sabiendo si la entidad pertenece 
	// o no al deathRow, activando o no el flag deleteAlso en consecuencia.
	// Pasos: (Suponiendo un GameState::remove(entity) que no la borre siempre y permita parámetro de borrado o no)
	// 1. return GameState::remove(e, deleteAlso)

	// [  Nota! Esto podría checkear si e pertenece al deathRow  ]
	
	// Por ahora se comprueba si ha de borrarse y se avisa al GameState para que lo haga
	// [  Descomentar cuando GameState pueda borrar sin eliminar  ] 
	return GameState::remove(e /*, isCondemned(e) )*/);
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
};