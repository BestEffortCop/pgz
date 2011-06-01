/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef __COMPONENTANIM_H__
#define __COMPONENTANIM_H__

#include "Controller.h"
#include "SpriteMap.h"
#include "HelperTypes.h"

class Enemy;

class ComponentAnim
{
public:
	friend class Component;

	protected:
		std::string gfxPath;
		Game* game;
		
		// Altura del elemento
		int height;

		Enemy* e;

	private:

		struct EnemyMask
		{
			int offsetX; int offsetY;
			int width; int height;
		};

		struct EnemyFrameData
		{
			int frameId;
			EnemyMask collisionMask;
			int hotspotX, hotspotY;
		};

		struct EnemyAnimData
		{
			int animSpeed;
			unsigned char numFrames;
			std::vector<EnemyFrameData> frameData;
		};

		// Animation translator from StandarEnemyAnimation to anim name
		std::map<std::pair<StandardEnemyAnimation, Direction>, std::string> animList;
		std::string getAnimName(StandardEnemyAnimation anim, Direction dir);

		// List of animation data
		std::map<std::pair<StandardEnemyAnimation, Direction>, EnemyAnimData> animDataList;
		EnemyAnimData getAnimationData(StandardEnemyAnimation anim, Direction dir = NONE);

		// Carga las animaciones a partir del archivo de cfg
		bool loadAnimations(std::string fname);
		bool loadAnimation(StandardEnemyAnimation anim, Direction direction, std::string name, FILE* from);
		EnemyFrameData loadAnimationFrame(FILE* from);
		std::string getConfigurationFileName(std::string fname);

	public:
		
		friend class EnemyTool;

		// Hace al enemy reproducir la animación indicada
		// Cuando termine volverá al estado anterior al comienzo
		// Devuelve true si el enemy acepta ser manipulado
		bool playAnim(StandardEnemyAnimation anim, int speed = -1, Direction dir = NONE);
		
		ComponentAnim(Game* game, Enemy* e, std::string gfxPath);
		~ComponentAnim();
		
		virtual void onCInit(){};
		virtual void onCStep();
		virtual void onCRender();
		virtual void onCTimer(int timer){};

		void setHeight(int h);
		int getHeight();
		void setShadow(int width);

		std::string getGfxPath();
};
#endif __COMPONENTANIM_H__