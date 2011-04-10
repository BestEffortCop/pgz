#include "GamePlayState.h"

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
	return true;
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