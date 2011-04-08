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
public:

	enum PlayerAnim { Stand, Walk, Slash, Thrust, Hit, Grab, Pull, Push, Pick, Picked, Throw, Drop };

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

	// Hace al player reproducir la animación indicada
	// Cuando termine volverá al estado anterior al comienzo
	// Devuelve true si el player acepta ser manipulado
	bool playAnim(PlayerAnim anim, Dir dir = NONE);

private:

	// info correspondiente a las tools equipdas ( <idtool, idtool>, de forma abstracta ).
	Controller* controller;

	// Animation translator from PlayerAnim to anim name
	std::map<PlayerAnim, std::string> animList;
	std::string getAnimName(PlayerAnim anim);

	struct PlayerMask
	{
		int offsetX; int offsetY;
		int width; int height;
	};

	struct PlayerFrameData
	{
		PlayerMask walkMask;
		PlayerMask collisionMask;
		int hotspotX, hotspotY;
	};

	struct PlayerAnimData
	{
		int animSpeed;
		unsigned char numFrames;
		std::vector<PlayerFrameData> frameData;
	};

	// List of animation data
	std::map<PlayerAnim, PlayerAnimData> animData;

	bool getNewPos(int& xtemp, int& ytemp);
};

#endif