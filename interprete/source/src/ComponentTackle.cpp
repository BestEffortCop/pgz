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

			// Actualizamos posición
			if (e->world->place_free(e->x, ytemp, e))
				e->y = ytemp; 
			else
				e->world->moveToContact(e->x,ytemp, e);

			if (e->world->place_free(xtemp, e->y, e))
				e->x = xtemp; 
			else
				e->world->moveToContact(xtemp,e->y, e);

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
		enemy->damagePlayer(dynamic_cast<Player*>(e), 5, 0x1);
		enemy->setLastHitDirection(enemy->computeHitDirection(e, enemy));
	}
	else if (other.b == "enemy")
	{
		tiledMov->goBack();
	};
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
				e->collidable = false;
				tackle(e);
				e->collidable = true;
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