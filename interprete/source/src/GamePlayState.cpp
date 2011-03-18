#include "GamePlayState.h"

GamePlayState::GamePlayState(int w, int h, Game* g) : GameState(g, w, h)
{
	// Se instancia el Controlador, que instancia todo
	// Quizás yo tengo que guardar punteros?
	controller = new Controller(NULL, g, this);
	// Se añade a la lista de auto-manejo
	_add(controller);

	// Se prepara la lista de entidades a eliminar bajo una transición
	deathRow.clear();
};

GamePlayState::~GamePlayState()
{
	// eliminar datos que tenga, controller & such
	delete controller;
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
	return GameState::remove(e /*, isCondemned(e) */);
};

bool GamePlayState::isCondemned(Entity* e)
{
	// No se puede borrar una entidad nula
	if (e == NULL) return false;
	else
	{
		// Se recorre la lista buscando la entidad
		list<Entity*>::iterator it = deathRow.begin();
		while (it != deathRow.end())
		{
			// Si la encontramos en el deathRow, se debe borrar
			if ((*it) != NULL)
				if ((*it) == e)
					return true;
		};
		// Si no está en el deathRow, es que no se debe borrar
		return false;
	};
};

void GamePlayState::renderBG()
{
	// Se dibuja un rectángulo para pruebas de gráficos de forma temporal
	game->getGfxEngine()->renderRectangle(1, 1, roomw-2, roomh-2, Color::Black, true);
};