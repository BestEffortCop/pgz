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

#include "ComponentBatMovement.h"

ComponentBatMovement::ComponentBatMovement(Game* game, Controller* cont): Component() {
	this->cont = cont;
	this->game = game;
}

ComponentBatMovement::~ComponentBatMovement() {

}

void ComponentBatMovement::onCInit(Enemy* e) 
{
	// Comenzamos en una direccion random y estado Normal
	e->dir = (Direction) ((rand() % 4) +1);
	state = Standing;
	resting = false;

	// Cambiamos la configuración por defecto de los flags que nos interesan
	e->solid = false;
}

void ComponentBatMovement::onCStep(Enemy* e) {
	int xtemp, ytemp;
	Player* player;
	int chasePlayerId = 0;
	int chaseDirX, chaseDirY;
	int collDist;

	int tmpx, tmpy;
	bool out;

	switch (state) {
		/* ********************** Standing ************************* */
		case Standing:
			if(!resting){
				e->setTimer(5, rand()%15 + 15);
				resting = true;
			}
			break;

		/* ********************** Walking ************************* */
		case Walking:
			if (rand()%100 < turnRatio){
				e->dir = getDifDir(e->dir);
			}
			moveInDir(e, moveSpeed);

			// Miramos en nuestra direccion a ver si vemos el player y cambiar al estado Chasing
			for (int i= 0; i<cont->getNumPlayers(); i++){
				player = cont->getPlayer(i);
				if (checkPlayerNear(player, e, searchDist)){
					state = Chasing;
					e->setTimer(4, chaseTime); // Ponemos un timer para el tiempo que busca
					chasePlayerId = i;
				}
			}
			break;

		/* ********************** Damaged ************************* */
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
				e->y = ytemp; 
				e->x = xtemp;
			}

			break;

		/* ********************** Chasing ************************* */
		case Chasing:
			player = cont->getPlayer(chasePlayerId);
			
			if (rand()%100 < turnRatio*6){

				chaseDirX = player->x - e->x;
				chaseDirY = player->y - e->y;
			
				if (abs(chaseDirX) - abs(chaseDirY) >= 0)
					// Tiene prioridad movimiento horizontal
					chaseDirX > 0 ? e->dir = RIGHT : e->dir = LEFT;
				else 
					// Tiene prioridad movimiento vertical
					chaseDirY > 0 ? e->dir = DOWN : e->dir = UP;
			}
			// Nos movemos en esa direccion
			moveInDir(e, moveSpeed);
	}
	
	e->graphic->setColor(Color::White);
	e->graphic->setAlpha(1);

	// Graphic settings
	switch (state) 	{
		case Standing:
			e->currentAnim = STAND;
			break;
		case Walking:
			e->currentAnim = WALK;
			break;
		case ReceivingDamage:
			e->currentAnim = DAMAGED;
			break;
		case Chasing:
			e->currentAnim = WALK;
			break;
		}
}

void ComponentBatMovement::onCCollision(Enemy* enemy, CollisionPair other, Entity* e)
{
	if (other.b == "player") 
	{
		enemy->damagePlayer((Player*) e, enemy->strength, 255);
	}

	else if (other.b == "tool")	{
		if (state != ReceivingDamage) {
			// Este daño lo hará el arma que nos pega
			state = ReceivingDamage;
			enemy->setTimer(1, 10);
		}
	}
	else if (other.b == "enemy") {
		switch(enemy->dir) {
			case UP:
				enemy->y += moveSpeed;
				break;
			case DOWN:
				enemy->y -= moveSpeed;
				break;
			case LEFT:
				enemy->x += moveSpeed;
				break;
			case RIGHT:
				enemy->x -= moveSpeed;
				break;
		}
	}
}

void ComponentBatMovement::onCTimer(Enemy* e, int timer) {
	// timer de bounce al ser damageado
	if (timer == 1)	{
		if (state == ReceivingDamage)
			if (!e->dead)
				state = Standing;
	}

	// timer de desaparecer
	if (timer == 2)
		e->instance_destroy();

	// timer de la animacion al colisionar con player
	if (timer == 3)
		state = Standing;

	// timer de estar persiguiendo
	if (timer == 4)
		if (state == Chasing)
			state = Standing;

	// timer de estar walking
	if (timer == 5){
		state = Walking;
		e->setTimer(6, rand()%25 + 15);		
	}

	// timer de estar standing
	if (timer == 6){
		state = Standing;
		resting = false;
	}
}

bool ComponentBatMovement::checkPlayerNear(Player* p, Enemy* e, int dist) {
	// Solo comprobamos si estamos mirando hacia el player nos ahorramos sqrt
	switch (e->dir) {
		// Le sumo mask height|width para el ancho y el alto del player
		case UP: 
			if (p->y - p->mask->height <= e->y)
				return getDistance(e->x, e->y, p->x, p->y) < dist;
			break;
		case DOWN:
			if (p->y + p->mask->height >= e->y)
				return getDistance(e->x, e->y, p->x, p->y) < dist;
			break;
		case LEFT:
			if (p->x - p->mask->width <= e->x)
				return getDistance(e->x, e->y, p->x, p->y) < dist;
			break;
		case RIGHT:
			if (p->x + p->mask->height >= e->x)
				return getDistance(e->x, e->y, p->x, p->y) < dist;
			break;
	}
	return false;
};

int ComponentBatMovement::getDistance(int x1, int y1, int x2, int y2) {
	int sqr1, sqr2;
	sqr1 = (x2-x1)*(x2-x1);
	sqr2 = (y2-y1)*(y2-y1);
	return (int)sqrt((double)(sqr1+sqr2));
}

// Mueve al enemigo en la direccion en la que este mirando, devuelve si se chocó con algo
bool ComponentBatMovement::moveInDir(Enemy* e, int speed){
	int xtemp = e->x;
	int ytemp = e->y;
	bool collided = false;

	bool outOfScreen = true;
	// Miramos a ver si seguimos en territorio pantallil
	Direction dir = cont->getScreenMap()->relative_position(e,outOfScreen);
        
    // Y corregimos apropiadamente
	if (outOfScreen)
		if (dir == RIGHT){
			e->x -= speed;
			e->dir = LEFT;
		}
		else if(dir == LEFT){
			e->x += speed;
			e->dir = RIGHT;
		}
		else if(dir == UP){
			e->y += speed;
			e->dir = DOWN;
		}
		else if(dir == DOWN){
			e->y -= speed;
			e->dir = UP;
		}
	
	// Coord donde intentaremos movernos
	if (e->dir == RIGHT) xtemp += speed;
	if (e->dir == LEFT) xtemp -= speed;
	if (e->dir == UP) ytemp -= speed;
	if (e->dir == DOWN) ytemp += speed;

	e->y = ytemp;
	e->x = xtemp;
	
	return collided;
}

Direction ComponentBatMovement::getDifDir(Direction direc){
	Direction newDir = (Direction) ((rand() % 4) +1);
	while (direc == newDir)
		newDir = (Direction) ((rand() % 4) +1);
	return newDir;
}