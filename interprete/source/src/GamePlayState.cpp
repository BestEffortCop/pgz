#include "GamePlayState.h"

GamePlayState::GamePlayState(int w, int h, Game* g) : GameState(g, w, h)
{
	// Se instancia el Controlador, que instancia todo
	// Quizás yo tengo que guardar punteros?

	// Se prepara la lista de entidades a eliminar bajo una transición
	deathRow.clear();
};

GamePlayState::~GamePlayState()
{
	// eliminar datos que tenga, controller & such
	// limpiar deathRow y borrarlo
};

// Sobrecarga del método del padre para utilizar la lista de eliminables
bool GamePlayState::add(Entity* e, bool condemned)
{
	// Se añade primero la entidad a las listas de automanejo del GameState
	if (GameState::add(e))
	{
		
		if (condemned)
			// Si además hay que guardarla e añade al deathRow
			return GameState::add_single(&deathRow, e);
		else
			// Si no, todo ha ido bien
			return true;
	}
	// Si no se ha podido añadir al GameState, es que ya estaba
	return false;
};

// Sobrecarga del método del padre para utilizar la lista de eliminables
bool GamePlayState::remove(Entity* e, bool deleteAlso)
{
	// (Work in Progress)

	// En principio esto se llama ya sabiendo si la entidad pertenece 
	// o no al deathRow, activando o no el flag deleteAlso en consecuencia.
	// Pasos: (Suponiendo un GameState::remove(entity) que no la borre siempre y permita parámetro de borrado o no)
	// 1. return GameState::remove(e, deleteAlso)

	// [  Nota! Esto podría checkear si e pertenece al deathRow  ]
	
	// Por ahora se borra y punto
	return GameState::remove(e);
};

void GamePlayState::renderBG()
{
	// Se dibuja un rectángulo para pruebas de gráficos de forma temporal
	game->getGfxEngine()->renderRectangle(1, 1, roomw-2, roomh-2, Color::Black, true);
};