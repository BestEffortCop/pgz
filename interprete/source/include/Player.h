#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "SpriteMap.h"
#include "GameEntity.h"
#include "iDamageable.h"
#include "HelperTypes.h"
#include "TileTextLabel.h"
#include "Door.h"

class Controller;

class Player : public GameEntity, public iDamageable
{
public:

	enum PlayerAnim { Stand, Walk, Slash, Thrust, Hit, Grab, Pull, Push, Pick, Picked, Throw, Drop, Get };
	enum PlayerState { Normal, Attack, Damaged, Cutscene, Dead, Animation };
	enum PlayerAction { aStand, aWalk, aSlash, aThrust, aHit, aGrab, aPull, aPush, aPick, aPicked, aThrow, aDrop };

	// Hp viene dado por iDamageable
	int mp;

	// crea el objeto Player, puede haber más parámetros
	Player(int x, int y, Game* game, GameState* world); 
    ~Player();

	Direction dir;

	bool init(std::string gfxpath, int ncol, int nrow, int hp, int mp, Controller* c);

    // Métodos virtuales de la clase padre
    void onStep(); // Realiza el movimiento del player en función del input

    // Métodos propios
	Direction getDir();

	// Hace al player reproducir la animación indicada
	// Cuando termine volverá al estado anterior al comienzo
	// Devuelve true si el player acepta ser manipulado
	bool playAnim(PlayerAnim anim, int speed = -1, Direction dir = NONE);

	// Intenta cambiar al player al estado que sea
	bool changeState(PlayerState next, bool forced = false);

	// Obtiene el estado actual del player
	PlayerState getState();

	void onDamage(int damage, short damageType);

	void onTimer(int n);

	void onDeath();

	void toLastPosition();

	void setLastEnemyDirection(Direction dir);

	std::pair<int, int> getCurrentHotSpot();

	void onRender();

	Controller* getController();

	void onCollision(CollisionPair pair, Entity* other);

	void parseInput();

	InputConfig getInputConfig();
	void setInputConfig(InputConfig config);

	void playGetItem(Graphic* item, int steps);
	void endGetItem();

private:

	// info correspondiente a las tools equipdas ( <idtool, idtool>, de forma abstracta ).
	Controller* controller;

	// Animation translator from PlayerAnim to anim name
	std::map<std::pair<PlayerAnim, Direction>, std::string> animList;
	std::string getAnimName(PlayerAnim anim, Direction dir);

	struct PlayerMask
	{
		int offsetX; int offsetY;
		int width; int height;
	};

	struct PlayerFrameData
	{
		int frameId;
		int speed;
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
	std::map<std::pair<PlayerAnim, Direction>, PlayerAnimData> animDataList;
	PlayerAnimData getAnimationData(PlayerAnim anim, Direction dir = NONE);

	// Carga las animaciones a partir del archivo de cfg
	bool loadAnimations(std::string fname);
	bool loadAnimation(PlayerAnim anim, Direction direction, std::string name, FILE* from);
	PlayerFrameData loadAnimationFrame(FILE* from);
	std::string getConfigurationFileName(std::string fname);

	bool getNewPos(int& xtemp, int& ytemp, int sp);

	// Estado
	// Estado actual y salvado
	PlayerState state, savedState; 
	// Acción actual
	PlayerAction currentAction;
	PlayerAnim currentAnim;
	Direction facing;

	// Última posición del player
	int lastX, lastY;
	// Dirección de colisión con enemigo
	Direction lastEnemyDirection;

	// Está muerto?
	bool dead;

	struct PlayerInput 
	{
		float xAxis, yAxis;
		ButtonState buttonA, buttonB, buttonSTART, buttonSELECT;
	};

	InputConfig inputConfig;

	PlayerInput currentInput;

	void doAttack(int hand);

	Graphic* holdItem;
	int holdItemX;
	int holdItemY;
};

#endif