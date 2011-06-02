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

#include "Door.h"
#include "PGZGame.h"

Door::Door(int x, int y, Direction dir, Game* game, GameState* world) : Entity(x, y, game, world)
{
	// Para que el player reproduzca su animación de empujar
	mask = new MaskBox(x, y, 32, 32, "pushable");

	collidable = true;
	solid = true;
	this->dir = dir;
	closed = true;
	transition = false;

	doorType = NORMAL;
}

Door::~Door()
{
}

void Door::prepareGraphic(std::string path)
{
	graphic = new SpriteMap(path, 3, 4, game->getGfxEngine());

	vector<int>* fopenup = new vector<int>();
	fopenup->push_back(5);
	((SpriteMap*) graphic)->addAnim("open-up",fopenup, 0, false);

	vector<int>* fopendown = new vector<int>();
	fopendown->push_back(2);
	((SpriteMap*) graphic)->addAnim("open-dw",fopendown, 0, false);

	vector<int>* fopenright = new vector<int>();
	fopenright->push_back(11);
	((SpriteMap*) graphic)->addAnim("open-rg",fopenright, 0, false);

	vector<int>* fopenleft = new vector<int>();
	fopenleft->push_back(8);
	((SpriteMap*) graphic)->addAnim("open-lf",fopenleft, 0, false);



	vector<int>* fcloseup = new vector<int>();
	fcloseup->push_back(3);
	((SpriteMap*) graphic)->addAnim("close-up",fcloseup, 0, false);

	vector<int>* fclosedown = new vector<int>();
	fclosedown->push_back(0);
	((SpriteMap*) graphic)->addAnim("close-dw",fclosedown, 0, false);

	vector<int>* fcloseright = new vector<int>();
	fcloseright->push_back(9);
	((SpriteMap*) graphic)->addAnim("close-rg",fcloseright, 0, false);

	vector<int>* fcloseleft = new vector<int>();
	fcloseleft->push_back(6);
	((SpriteMap*) graphic)->addAnim("close-lf",fcloseleft, 0, false);



	vector<int>* fopeningup = new vector<int>();
	fopeningup->push_back(3);
	fopeningup->push_back(4);
	fopeningup->push_back(5);
	((SpriteMap*) graphic)->addAnim("opening-up",fopeningup, 4, false);

	vector<int>* fopeningdown = new vector<int>();
	fopeningdown->push_back(0);
	fopeningdown->push_back(1);
	fopeningup->push_back(2);
	((SpriteMap*) graphic)->addAnim("opening-dw",fopeningdown, 4, false);

	vector<int>* fopeningright = new vector<int>();
	fopeningright->push_back(9);
	fopeningright->push_back(10);
	fopeningright->push_back(11);
	((SpriteMap*) graphic)->addAnim("opening-rg",fopeningright, 4, false);

	vector<int>* fopeningleft = new vector<int>();
	fopeningleft->push_back(6);
	fopeningleft->push_back(7);
	fopeningleft->push_back(8);
	((SpriteMap*) graphic)->addAnim("opening-lf",fopeningleft, 4, false);



	vector<int>* closingup = new vector<int>();
	closingup->push_back(5);
	closingup->push_back(4);
	closingup->push_back(3);
	((SpriteMap*) graphic)->addAnim("closing-up",closingup, 4, false);

	vector<int>* closingdown = new vector<int>();
	closingdown->push_back(2);
	closingdown->push_back(1);
	closingdown->push_back(0);
	((SpriteMap*) graphic)->addAnim("closing-dw",closingdown, 4, false);

	vector<int>* closingright = new vector<int>();
	closingright->push_back(11);
	closingright->push_back(10);
	closingright->push_back(9);
	((SpriteMap*) graphic)->addAnim("closing-rg",closingright, 4, false);

	vector<int>* closingleft = new vector<int>();
	closingleft->push_back(8);
	closingleft->push_back(7);
	closingleft->push_back(6);
	((SpriteMap*) graphic)->addAnim("closing-lf",closingleft, 4, false);
}

void Door::init(int id, MapStatus* status, std::string gfxPath)
{
	this->myMapStatus = status;
	idDoor = id;

	prepareGraphic(gfxPath);

	if (id != -1 && status != NULL)
	{
		if (status->getDoorStatus(id))
			open();
		else
			close();
	}

	if (!closed)
	{	
		setCollidable(false);
		solid = false;
		playAnimation("open");
	}
	else
	{
		setCollidable(true);
		solid = true;
		playAnimation("close");
	}
};

void Door::playAnimation(std::string s)
{
	switch(dir)
	{
		case UP:
			s.append("-up");
			break;
		case DOWN:
			s.append("-dw");
			break;
		case LEFT:
			s.append("-lf");
			break;
		case RIGHT:
			s.append("-rg");
			break;
	}

	((SpriteMap*) graphic)->playAnim(s);
}

void Door::onStep()
{
	if (transition)
	{
		if (((SpriteMap*) graphic)->animFinished())
		{
			if (closed)
			{
				setCollidable(true);
				solid = true;
				playAnimation("close");
			}
			else
			{
				setCollidable(false);
				solid = false;
				playAnimation("open");
			}
			transition = false;
		}
	}
}

void Door::open()
{
	if (closed)
	{
		closed = false;
		transition = true;
		if (myMapStatus != NULL && idDoor >= 0)
			myMapStatus->setDoorStatus(idDoor, true);
		playAnimation("opening");
	}
}

void Door::close()
{
	if (!closed)
	{
		closed = true;
		transition = true;
		if (myMapStatus != NULL && idDoor >= 0)
			myMapStatus->setDoorStatus(idDoor, false);
		playAnimation("closing");
	}
}

bool Door::isOpen()
{
	return !(closed || (closed && transition));
}

void Door::setDoorType(DoorType doorType)
{
	this->doorType = doorType;
	if (doorType == FINALDOOR)
	{
		//depth = 2000;
		if (((PGZGame*) game)->controller->getData()->getGameData()->getGameStatus()->getNumKeyItems() >=
			((PGZGame*) game)->controller->getData()->getGameData()->getMaxKeyItems())
			visible = false,
			instance_destroy();
	}
	else if (doorType == BOSSDOOR) {
		graphic->setColor(Color::Red);
	}
}

Door::DoorType Door::getDoorType()
{
	return doorType;
}