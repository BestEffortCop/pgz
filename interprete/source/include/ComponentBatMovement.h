#pragma once
#ifndef __COMPONENTBATMOVEMENT_H__

#include "Enemy.h"
#include "Stamp.h"
#include "HelperTypes.h"
#include "iDamageable.h"

class ComponentBatMovement : public Component{
	private:
		enum EnemyState { Standing, Walking, Chasing, ReceivingDamage, Dying };
		EnemyState state, savedState;

		void playAnim(StandardEnemyAnimation anim, int speed, Direction dir);
		bool checkPlayerNear(Player* p, Enemy* e, int dist);
		int getDistance(int x1, int y1, int x2, int y2);
		bool moveInDir(Enemy* e, int speed);
		Direction getDifDir(Direction direc);

		bool resting;

		//TODO Estos podremos cambiarlos en el CInit en funcion de la dificultad del enemigo
		static const int turnRatio = 4;
		static const int searchDist = 50;
		static const int chaseTime = 30;
		static const int moveSpeed = 2; //ovejita que te pillo

		//HP PROVISIONAL
		static const int hpProv = 5;

	public:

		ComponentBatMovement(Game* game, Controller* cont);
		~ComponentBatMovement();

		void onCInit(Enemy* e);
		void onCStep(Enemy* e);
		void onCRender(Enemy* e){};
		virtual void onCTimer(Enemy* e, int timer);
		virtual void onCCollision(Enemy* enemy, CollisionPair other, Entity* e);
		virtual void onCDestroy(Enemy* e){};
		virtual void onCCustomEvent(Enemy* e, int event){};
		virtual void onCInitStep(Enemy* e){};
		virtual void onCEndStep(Enemy* e){};
		virtual void onCEndWorld(Enemy* e){};
};
#endif