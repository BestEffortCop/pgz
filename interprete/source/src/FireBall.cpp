/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "FireBall.h"
#include "PGZGame.h"

FireBall::FireBall(Direction dir, int x, int y, Game* game, GameState* world) : Entity(x, y, game, world) {
	mask = new MaskBox(x, y, 8, 10, "fireball", 0, 0); 
	solid = true;
	type = "fireball";
	this->dir = dir;
	this->init("data/graphics/fireSheet.png", 7, 1);
};

void FireBall::init(string graphicpath, int ncol, int nrow){
	/*---------Inicialización de gráficos----------------*/
	graphic = new SpriteMap(graphicpath, ncol, nrow, game->getGfxEngine());

	vector<int>* frames = new vector<int>();
	frames->push_back(0);
	frames->push_back(1);
	frames->push_back(2);
	frames->push_back(3);
	frames->push_back(4);
	frames->push_back(5);
	frames->push_back(6);
	((SpriteMap*) graphic)->addAnim("shake", frames, 4, true);

	sp = 2;
}

FireBall::~FireBall() {
		
}; 

void FireBall::onStep() {
	switch (dir) {
		case UPLEFT:
			y -= sp; x -= sp;
			break;
		case DOWNRIGHT:
			y += sp; x += sp;
			break;
		case DOWNLEFT:
			y += sp; x -= sp;
			break;
		case UPRIGHT:
			y -= sp; x += sp;
			break;
	}
	((SpriteMap*) graphic)->playAnim("shake");

	if (!place_free(x, y)) instance_destroy();

	depth = y;
};

void FireBall::onCollision(Entity* e) {
	if (e->type != "boss") {
		this->instance_destroy();
	}		
};