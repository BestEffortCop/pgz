#include "ComponentDivide.h"

// Esto tendra que recibirlo de algun lado
#define IMG_WIDTH 16    // ancho de la imagen
#define IMG_HEIGHT 16   // alto de la imagen
//#define HP 10			//Vida del enemigo
//#define ST 5			//Fuerza del enemigo	

ComponentDivide::ComponentDivide(Game* game, Controller* cont) : Component()
{
	this->cont = cont;
	this->game = game;
	this->mov = NULL;
};

ComponentDivide::~ComponentDivide()
{
};

void ComponentDivide::onCInit(Enemy* e)
{
	// Creamos la máscara
	//e->mask = new MaskBox(e->x, e->y, 16, 16, "enemy", 0, 0);

	// Cambiamos la configuración por defecto de los flags que nos interesan
	e->solid = false;
	e->graphic->setScale(0.9f, 0.9f);
	e->graphic->setOriginX(7);
	e->graphic->setOriginY(6);

	// Sombra
	e->initShadow(GameEntity::sMedium);

	//e->hp = HP;
	//e->maxHp = HP;
	//e->strength = ST;

		std::vector<Component*>* comps = e->getComponents();
	if (comps != NULL)
	{
		std::vector<Component*>::iterator it = comps->begin();
		while (it != comps->end() && mov == NULL)
		{
			mov = dynamic_cast<ComponentTiledMovement*>(*it);
			it++;
		};
	};

	if (mov != NULL)
		mov->initSettings(16, 16, 1);

	state = Act;
	e->dir = DOWN;
};

void ComponentDivide::onCStep(Enemy* e)
{	
	Player* p = NULL;
	int nx = 0;
	int ny = 0;
	float d = 0;
	switch(state)
	{
		case(Act):
			for (int i = 0; i < cont->getNumPlayers(); i++)
			{
				p = cont->getPlayer(i);

				// Distancia euclídea
				nx = p->mask->x + p->mask->xoffset - e->x;
				ny = p->mask->y + p->mask->yoffset - e->y;
				d = sqrt(pow((double) nx, (int) 2) + pow((double) ny, (int) 2));

				if (d < 75)
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
					state = Chase;
						mov->move(e->dir,e);
				}//if
			}//for
			if(!mov->isLocked() && state != Chase)
			{
				e->dir = (Direction) (rand()%4 + 1);
					mov->move(e->dir,e);
				e->setTimer(0,15+rand()%15);
				state = Stand;
			}
			break;

		case(Stand):
			break;

		case(Hit):
			if (e->hp <= 0)
			{
				e->setTimer(0,5);
				state = Divide;
			}
			else
			{
				int xtemp = e->x;
				int ytemp = e->y;

				e->setLastHitDirection(e->computeHitDirection(e, p));
				e->onDamage(5, 0xFF);

				// Bounce del player
				if (e->getLastHitDirection() == UP) ytemp += e->getTimer(0)/2;
				else if (e->getLastHitDirection() == DOWN) ytemp -= e->getTimer(0)/2;
				else if (e->getLastHitDirection() == LEFT) xtemp += e->getTimer(0)/2;
				else if (e->getLastHitDirection() == RIGHT) xtemp -= e->getTimer(0)/2;
				else if (e->getLastHitDirection() == UPLEFT) ytemp += e->getTimer(0)/2, xtemp += e->getTimer(0)/2;
				else if (e->getLastHitDirection() == UPRIGHT) ytemp += e->getTimer(0)/2, xtemp -= e->getTimer(0)/2;
				else if (e->getLastHitDirection() == DOWNLEFT) ytemp -= e->getTimer(0)/2, xtemp += e->getTimer(0)/2;
				else if (e->getLastHitDirection() == DOWNRIGHT) ytemp -= e->getTimer(0)/2, xtemp -= e->getTimer(0)/2;

				// Actualizamos posición
				if (e->world->place_free(e->x, ytemp,e))
				{    
					e->y = ytemp; 
				}
				else
				{   
					e->world->moveToContact(e->x,ytemp, e);
				}

				if (e->world->place_free(xtemp, e->y,e))
				{    
					e->x = xtemp; 
				}
				else
				{   
					e->world->moveToContact(xtemp,e->y, e); 
				}
			}
			break;

		case(Chase):
			if (!mov->isLocked())
			{
				state = Act;
			}
			break;

		case(Divide):
			break;

		case(Dead):
			break;
	}

	// Animation
	e->graphic->setColor(Color::White);
	switch (state)
	{
	case Stand:
		e->currentAnim = STAND;
		break;
	case Act:
		e->currentAnim = WALK;
		break;
	case Chase:
		e->currentAnim = WALK;
		break;
	case Hit:
		e->currentAnim = DAMAGED;
		break;
	case Dead:
		e->currentAnim = DEAD;
		break;
	}
};


void ComponentDivide::onCRender(Enemy* e)
{
	//e->graphic->setScale(0.2, 0.2);
}

void ComponentDivide::onCCollision(Enemy* enemy, CollisionPair other, Entity* e)
{
	if(state != Dead)
	{
		//Esto es solo una chorrada de cara al testeo de colisiones, QUITAR en versión definitiva
		if (other.b == "coltest")
		{
			enemy->instance_destroy();
		}

		else if (other.b == "player")
		{
			((Player*) e)->setLastHitDirection(((Player*) e)->computeHitDirection(enemy, e));
			((Player*) e)->onDamage(5, 0xFF);
		
			//Paramos al bicho para que no siga abasallandonos
			enemy->setTimer(0, 15+rand()%15);
			state = Stand;
		}

		else if (other.b == "tool")
		{
			if (state != Hit)
			{
				// Este daño lo hará el arma que nos pega
				state = Hit;
				enemy->setTimer(0, 10);
			}
		}
		else if (other.b == "enemy")
		{
			mov->goBack();
			state = Stand;
		}
	}
};

void ComponentDivide::onCTimer(Enemy* e, int timer)
{
	if (timer == 0)
	{
		switch (state)
		{
			case Act:
				break;
			case Stand:
				if (rand()%20 < 2)
					e->setTimer(0, rand()%30);
				else
				{
					state = Act;
				}
				break;
			case Chase:
				break;
			case Hit:
				state = Act;
				break;
			case Divide: 
				state = Dead;
				break;
		}
	}
};
