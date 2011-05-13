#include "ComponentDivide.h"

ComponentDivide::ComponentDivide(Game* game, Controller* cont, bool father) : Component()
{
	this->cont = cont;
	this->game = game;
	this->mov = NULL;

	this->father = father;

	chaseDistance = standTime = speed = -1;
};

ComponentDivide::~ComponentDivide()
{
};

void ComponentDivide::onCInit(Enemy* e)
{
	// Cambiamos la configuración por defecto de los flags que nos interesan
	e->solid = false;

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


	if (father)
	{
		e->graphic->setScale(1.f, 1.f);
		e->graphic->setOriginX(e->mask->width / 2);
		e->graphic->setOriginY(e->mask->height / 2);

		if (chaseDistance == -1)
			chaseDistance = 40;
		if (mov != NULL)
			if (speed == -1);
				speed = 1;
		if (standTime == -1)
			standTime = 50;
	}
	else
	{
		e->graphic->setScale(0.8f, 0.8f);
		e->graphic->setOriginX(e->mask->width / 2);
		e->graphic->setOriginY(e->mask->height / 2);

		if (chaseDistance == -1)
			chaseDistance = 20;
		if (mov != NULL)
			if (speed == -1);
				speed = 2;
		if (standTime == -1)
			standTime = 70;
	}

	if (mov != NULL)
		mov->initSettings(16, 16, speed);

	if (state != ReceivingDamage)
	{
		state = Stand;
		e->setTimer(0, rand()%30);
	}

	chasing = false;
	e->dir = DOWN;
	
};


void ComponentDivide::onCDestroy(Enemy* e)
{
	if (father)
	{
		// Hijo 1
		vector<Component*>* components2 = new vector<Component*>();
		components2->push_back(new ComponentTiledMovement(game, ((PGZGame*) game)->controller));
		ComponentDivide* c1 = new ComponentDivide(game,((PGZGame*) game)->controller, false);
		components2->push_back(c1);
		Enemy* offspring1 = new Enemy(game, e->world);
		EnemySpawnData spw1;
		spw1.id = 0;
		spw1.x = e->x;
		spw1.y = e->y;
		ComponentAnim* cAnim1 = new ComponentAnim(game, offspring1, e->cAnim->getGfxPath());
		offspring1->init(spw1, components2, cAnim1, 15, 5, 8, 1);
		offspring1->cAnim->setShadow(offspring1->mask->width);
		/*c1->state = ReceivingDamage;
		offspring1->setLastHitDirection(LEFT);*/
		e->world->add(offspring1);

		// Hijo 2
		vector<Component*>* components1 = new vector<Component*>();
		components1->push_back(new ComponentTiledMovement(game, ((PGZGame*) game)->controller));
		ComponentDivide* c2 = new ComponentDivide(game,((PGZGame*) game)->controller, false);
		components1->push_back(c2);
		Enemy* offspring2 = new Enemy(game, e->world);
		EnemySpawnData spw2;
		spw2.id = 0;
		spw2.x = e->x + 8;
		spw2.y = e->y;
		ComponentAnim* cAnim2 = new ComponentAnim(game, offspring2, e->cAnim->getGfxPath());
		offspring2->init(spw2, components1, cAnim2, 15, 5, 8, 1);
		offspring2->cAnim->setShadow(offspring2->mask->width);

		e->world->add(offspring2);
		
	}
}

void ComponentDivide::onCStep(Enemy* e)
{	
	if (father)
	if  (rand()%50 == 1)
	{
		e->instance_destroy();
	}


	Player* p = NULL;
	int nx = 0;
	int ny = 0;
	float d = 0;

	if (mov != NULL)
		if (!mov->isLocked() && state == Move)
		{
			state = Stand;
			e->setTimer(0, 25+rand()%standTime);
		}

	switch(state)
	{
		case(Stand):

			for (int i = 0; i < cont->getNumPlayers(); i++)
			{
				p = cont->getPlayer(i);

				// Distancia euclídea
				nx = p->mask->x + p->mask->xoffset - e->x;
				ny = p->mask->y + p->mask->yoffset - e->y;
				d = sqrt(pow((double) nx, (int) 2) + pow((double) ny, (int) 2));

				if (d < 75)
				{
					chasing = true;

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
					state = Move;
					// Para que golpee
					if (chasing)
						e->collidable = false;

					mov->move(e->dir,e);
					e->collidable = true;
				}//if
				else
				{
					chasing = false;
				}
			}//for
			break;

		case(ReceivingDamage):
			if (e->hp <= 0)
			{
				/*e->setTimer(0,5);
				state = Divide;*/
			}
			else
			{
				int xtemp = e->x;
				int ytemp = e->y;

				//e->setLastHitDirection(e->computeHitDirection(e, p));
				//e->setLastHitDirection(LEFT);
				//e->onDamage(5, 0xFF);

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

		case(Divide):
			break;

		case(Dead):
			break;
	}

	// Animation
	e->graphic->setColor(Color::White);

	if (chasing)
		e->graphic->setColor(Color::Yellow);

	switch (state)
	{
	case Stand:
		e->currentAnim = STAND;
		break;
	case Move:
		e->currentAnim = WALK;
		break;
	case ReceivingDamage:
		e->currentAnim = DAMAGED;
		break;
	case Dead:
		e->currentAnim = DEAD;
		break;
	}
};


void ComponentDivide::onCRender(Enemy* e)
{
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
			if (state != ReceivingDamage)
			{
				// Este daño lo hará el arma que nos pega
				state = ReceivingDamage;
				enemy->setTimer(0, 10);
			}
		}
		else if (other.b == "enemy")
		{
			mov->goBack();
			state = Stand;
			enemy->setTimer(0, 15+rand()%15);
		}
	}
};

void ComponentDivide::onCTimer(Enemy* e, int timer)
{
	if (timer == 0)
	{
		switch (state)
		{
			case Stand:
				if (rand()%20 < 2)
					e->setTimer(0, rand()%30);
				else
				{
					state = Move;
					e->dir = (Direction) (1+rand()%4);
					if (mov != NULL)
						mov->move(e->dir, e);
					else
						e->setTimer(0, rand()%30);
				}
				break;
			case Divide: 
				state = Dead;
				break;
		}
	}
	// timer de bounce al ser damageado
	if (timer == 1)
	{
		if (state == ReceivingDamage)
			if (!e->dead)
			{
				state = Stand;
				e->setTimer(0, 25+rand()%standTime);
			}
	}
};
