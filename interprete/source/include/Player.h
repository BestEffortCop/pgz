#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameEntity.h"
#include "Stamp.h"
#include "HelperTypes.h"

class Player : public GameEntity 
{

private:

	// info correspondiente a las tools equipdas ( <idtool, idtool>, de forma abstracta ).
	// 

public:
	// crea el objeto Player, puede haber más parámetros
	Player(int x, int y, Game* game, GameState* world, std::string gfxpath, int hp, int mp); 
    ~Player();

    // Métodos virtuales de la clase padre
    void onStep(); // Realiza el movimiento del player en función del input


    // Métodos propios
	Dir getDir();

};

#endif