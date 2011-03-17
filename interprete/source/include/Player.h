#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Stamp.h"

class Player : public Entity 
{
public:
    Player(int x, int y, Game* game, GameState* world); // crea el objeto Player, puede haber más parámetros
    ~Player();

    // Métodos virtuales de la clase padre
    void onStep(); // Realiza el movimiento del player en función del input

	/* Los métodos vacíos no hace falta declararlos */
	// void onRender() {}; // (vacío de momento, ya se ocupa entity)
	// void onCollision() {}; // Acción a realizar en caso de colisión (vacía de momento)
};

#endif