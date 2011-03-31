#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "SpriteMap.h"

#include "GameEntity.h"
#include "Controller.h"


#include "HelperTypes.h"

class Controller;

class Player : public GameEntity 
{

private:

	// info correspondiente a las tools equipdas ( <idtool, idtool>, de forma abstracta ).
	Controller* controller;

	bool getNewPos(int& xtemp, int& ytemp);

public:

	int hp, mp;

	float xacc,yacc,zacc;
	float xspeed,yspeed,zspeed;

	// crea el objeto Player, puede haber más parámetros
	Player(int x, int y, Game* game, GameState* world); 
    ~Player();

	Dir dir;

	bool init(std::string gfxpath, int ncol, int nrow, int hp, int mp, Controller* c);

    // Métodos virtuales de la clase padre
    void onStep(); // Realiza el movimiento del player en función del input

    // Métodos propios
	Dir getDir();
};

#endif