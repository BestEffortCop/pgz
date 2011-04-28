#pragma once

#ifndef __COMPONENTANIM_H__
#define __COMPONENTANIM_H__

#include "SpriteMap.h"
#include "Enemy.h"
#include "Stamp.h"
#include "HelperTypes.h"

class Enemy;

class ComponentAnim : public Component
{
	private:

		struct EnemyMask
		{
			int offsetX; int offsetY;
			int width; int height;
		};

		struct EnemyFrameData
		{
			int frameId;
			int speed;
			EnemyMask walkMask;
			EnemyMask collisionMask;
			int hotspotX, hotspotY;
		};

		struct EnemyAnimData
		{
			int animSpeed;
			unsigned char numFrames;
			std::vector<EnemyFrameData> frameData;
		};

		// Animation translator from PlayerAnim to anim name
		std::map<std::pair<Enemy::StandardEnemyAnimation, Direction>, std::string> animList;
		std::string getAnimName(Enemy::StandardEnemyAnimation anim, Direction dir);

		// List of animation data
		std::map<std::pair<Enemy::StandardEnemyAnimation, Direction>, EnemyAnimData> animDataList;
		EnemyAnimData getAnimationData(Enemy::StandardEnemyAnimation anim, Direction dir = NONE);

		// Carga las animaciones a partir del archivo de cfg
		bool loadAnimations(std::string fname);
		bool loadAnimation(Enemy::StandardEnemyAnimation anim, Direction direction, std::string name, FILE* from);
		EnemyFrameData loadAnimationFrame(FILE* from);
		std::string getConfigurationFileName(std::string fname);

		bool alreadyPlaying;
		Enemy* e;
		
	public:
		friend class EnemyTool;

		// Hace al enemy reproducir la animación indicada
		// Cuando termine volverá al estado anterior al comienzo
		// Devuelve true si el enemy acepta ser manipulado
		bool playAnim(Enemy::StandardEnemyAnimation anim, int speed = -1, Direction dir = NONE);
		
		ComponentAnim(Game* game, Controller* cont );
		~ComponentAnim(){};
		
		void onCInit(Enemy* e);
		void onCStep(Enemy* e);
		void onCRender(Enemy* e);
		virtual void onCTimer(Enemy* e, int timer){};
		virtual void onCCollision(Enemy* enemy, CollisionPair other, Entity* e){};
		virtual void onCDestroy(Enemy* e){};
		virtual void onCCustomEvent(Enemy* e, int event){};
		virtual void onCInitStep(Enemy* e){};
		virtual void onCEndStep(Enemy* e){};
		virtual void onCEndWorld(Enemy* e){};
};
#endif __COMPONENTANIM_H__