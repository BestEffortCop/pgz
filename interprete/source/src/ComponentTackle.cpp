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

#include "ComponentTackle.h"


ComponentTackle::ComponentTackle(Game* game, Controller* cont) : Component()
{
	this->game = game;
	this->cont = cont;
	tiledMov = NULL;
}

ComponentTackle::~ComponentTackle()
{
}

void ComponentTackle::onCInit(Enemy* e)
{
	// Creamos la máscara

	// Cambiamos la configuración por defecto de los flags que nos interesan
	e->solid = false;

	std::vector<Component*>* comps = e->getComponents();
	if (comps != NULL)
	{
		std::vector<Component*>::iterator it = comps->begin();
		while (it != comps->end() && tiledMov == NULL)
		{
			tiledMov = dynamic_cast<ComponentTiledMovement*>(*it);
			it++;
		};
	};

	if (tiledMov != NULL)
		tiledMov->initSettings(16, 16, 1);

	state = Stand;
	e->dir = DOWN;
	e->setTimer(0, rand()%30);
}

void ComponentTackle::onCStep(Enemy* e)
{
	if (tiledMov != NULL)
		if (!tiledMov->isLocked() && (state == Move || state == Tackle) )
		{
			if (state == Tackle)
			{
				state = Rest;
				e->setTimer(0, 20);
			}
			else
			{
				e->setTimer(0, 0);
				state = Stand;
			}
			
			tiledMov->setSpeed(1);
		}

	int xtemp, ytemp;
	Player* p;
	int nx;
	int ny;
	float d;

	int tmpx, tmpy;
	bool out;

	switch (state) {
		case Stand:
			p = NULL;
			nx = 0;
			ny = 0;
			d = 0;
			for (int i = 0; i < cont->getNumPlayers(); i++)
			{
				p = cont->getPlayer(i);

				// Distancia euclídea
				nx = p->mask->x + p->mask->xoffset - e->x;
				ny = p->mask->y + p->mask->yoffset - e->y;
				d = (float) sqrt(pow((double) nx, (int) 2) + pow((double) ny, (int) 2));
				
				if (d < 32)
				{
					if (p->mask->x + p->mask->xoffset > e->x)
						e->dir = RIGHT;
					else
						e->dir = LEFT;


					if (p->mask->y + p->mask->yoffset > e->y)
					{
						if (abs((int) p->mask->x + p->mask->xoffset - e->x) < abs(p->mask->y + p->mask->yoffset - e->y))
							e->dir = DOWN;
					}
					else
					{
						if (abs((int) p->mask->x + p->mask->xoffset - e->x) < abs(p->mask->y + p->mask->yoffset - e->y))
							e->dir = UP;
					}
					state = Charge;
					e->setTimer(0, 15);
				}
			}
		break;
		case ReceivingDamage:
			xtemp = e->x; 
			ytemp = e->y;

			// Bounce del enemy 
			if (e->getLastHitDirection() == UP) ytemp += e->getTimer(1)/2;
			else if (e->getLastHitDirection() == DOWN) ytemp -= e->getTimer(1)/2;
			else if (e->getLastHitDirection() == LEFT) xtemp += e->getTimer(1)/2;
			else if (e->getLastHitDirection() == RIGHT) xtemp -= e->getTimer(1)/2;
			else if (e->getLastHitDirection() == UPLEFT) ytemp += e->getTimer(1)/2, xtemp += e->getTimer(1)/2;
			else if (e->getLastHitDirection() == UPRIGHT) ytemp += e->getTimer(1)/2, xtemp -= e->getTimer(1)/2;
			else if (e->getLastHitDirection() == DOWNLEFT) ytemp -= e->getTimer(1)/2, xtemp += e->getTimer(1)/2;
			else if (e->getLastHitDirection() == DOWNRIGHT) ytemp -= e->getTimer(1)/2, xtemp -= e->getTimer(1)/2;
			
			out = true;
			tmpx = e->mask->x; 
			tmpy = e->mask->y;

			e->mask->y = ytemp; 
			e->mask->x = xtemp;

			// Miramos a ver si seguimos en territorio pantallil
			cont->getScreenMap()->relative_position(e,out);
        
			e->mask->x = tmpx; 
			e->mask->y = tmpy;

			// Y corregimos apropiadamente
			if (out)
			{
				e->setTimer(1,0);
			}
			else
			{
				// Actualizamos posición
				if (e->world->place_free(e->x, ytemp, e))
					e->y = ytemp; 
				else
					e->world->moveToContact(e->x,ytemp, e);

				if (e->world->place_free(xtemp, e->y, e))
					e->x = xtemp; 
				else
					e->world->moveToContact(xtemp,e->y, e);
			}


			break;
	}
	// Animation
	e->graphic->setColor(Color::White);
	int i;
	Color c;
	switch (state)
	{
	case Stand:
		e->currentAnim = STAND;
		break;
	case Rest:
		e->currentAnim = STAND;
		break;
	case Move:
		e->currentAnim = WALK;
		break;
	case Tackle:
		e->currentAnim = WALK;
		break;
	case Charge:
		i = e->getTimer(0);
		c = Color (255, 255 - (150 - i*10), 255 - (150 - i*10));
		e->currentAnim = ATKMELEE;
		e->graphic->setColor(c);
		break;
	case ReceivingDamage:
		e->currentAnim = DAMAGED;
		break;
	};
};

void ComponentTackle::onCCollision(Enemy* enemy, CollisionPair other, Entity* e)
{
	if (other.b == "player")
	{
		enemy->damagePlayer(dynamic_cast<Player*>(e), 5, 255);
	}
	else if (other.b == "enemy")
	{
		tiledMov->goBack();
	}
	else if (other.b == "tool")
	{
		if (state != ReceivingDamage)
		{
			// Este daño lo hará el arma que nos pega
			state = ReceivingDamage;
			enemy->setTimer(1, 10);
		}
	}
}

//void ComponentTackle::onCRender(Enemy* e){};
void ComponentTackle::onCTimer(Enemy* e, int timer)
{
	if (timer == 0)
	{
		// Time to make a decission!
		switch (state)
		{
			case Stand:
			{
				if (rand()%20 < 2)
					// Quietecito
					e->setTimer(0, rand()%30);
				else
				{
					state = Move;
					e->dir = (Direction) (1+rand()%4);
					if (tiledMov != NULL)
						tiledMov->move(e->dir, e);
					else
						e->setTimer(0, rand()%30);
				}
				break;
			}
			case Tackle:
				state = Rest;
				e->setTimer(0, 1);
				break;
			case Charge:
				//e->collidable = false;
				tackle(e);
				//e->collidable = true;
				break;
			case Rest:
				state = Stand;
				e->setTimer(0, 10);
		}
	}

	// timer de bounce al ser damageado
	if (timer == 1)
	{
		if (state == ReceivingDamage)
			if (!e->dead)
			{
				state = Stand;
				e->setTimer(0, 25+rand()%30);
			}
	}
}

void ComponentTackle::onCDestroy(Enemy* e){}
void ComponentTackle::onCCustomEvent(Enemy* e, int event){};
void ComponentTackle::onCInitStep(Enemy* e){};
void ComponentTackle::onCEndStep(Enemy* e){};
void ComponentTackle::onCEndWorld(Enemy* e){};

void ComponentTackle::tackle(Enemy* e)
{
	tiledMov->setSpeed(4);

	if (tiledMov != NULL)
		tiledMov->move(e->dir, e);
	else
		e->setTimer(0, rand()%30);

	state = Tackle;
}