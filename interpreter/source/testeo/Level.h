#pragma once
#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "GameState.h"
#include "objTest.h"
#include "player2.hpp"
#include "objLight.h"
#include "objBad.h"
#include "objStar.h"
#include "TileMap.h"
#include "Stamp.h"
#include "Map.h"
#include "Sound1.h"
#include "Music1.h"

#include "Canvas.h"

#include <iostream>
#include <stdio.h>

class objBad;
class objStar;

class Level : public GameState
{
	public:

		Graphic* bg;
		TileMap* tm;

		Stamp* cursor;

		objLight* light;
		objTest* player;
		Player2* p2;

		Map* aMap;
		Canvas* canvas;
		int counter;

		int mx, my;

		Sound1* sound1; //new
		Music1* music1;
		Sound1* sound2; //new
		Music1* music2;

		Level(Game* g);

		void renderBG()
		{
            bg->render(0, 0);
			aMap->render(0, 0);
			canvas->render(100, 100);
		}

		void renderFG()
		{
			cursor->render(mx, my);
		}

		void on()
		{
			light->setVisible(true);
		}

		void off()
		{
			light->setVisible(false);
		}

		void onStep();
};

#endif
