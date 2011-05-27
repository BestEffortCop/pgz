#include "ComponentDivide.h"

ComponentDivide::ComponentDivide(Game* game, Controller* cont, bool father) : Component()
{
	this->cont = cont;
	this->game = game;
	this->mov = NULL;

	this->father = father;

	chaseDistance = standTime = speed = -1;
	offspringScale = -1;

	minions = 2;
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
		if (offspringScale == -1)
			offspringScale = 0.8f;

		e->graphic->setScale(offspringScale,offspringScale);
		e->graphic->setOriginX(e->graphic->getOriginX() + (1-offspringScale)*e->graphic->getWidth()/2);
		e->graphic->setOriginY(e->graphic->getOriginY() + (1-offspringScale)*e->graphic->getWidth()/2);

		e->mask->xoffset = e->mask->xoffset + (1-offspringScale)*e->mask->width/2;
		e->mask->yoffset = e->mask->yoffset + (1-offspringScale)*e->mask->height/2;
		e->mask->width = offspringScale*e->mask->width;
		e->mask->height = offspringScale*e->mask->height;

		if (chaseDistance == -1)
			chaseDistance = 20;
		if (mov != NULL)
			if (speed == -1);
				speed = 1;
		if (standTime == -1)
			standTime = 70;
	}

	e->cAnim->setShadow(e->mask->width);

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
		vector<Component*>* components;
		ComponentDivide* c; 
		Enemy* offspring;
		ComponentAnim* cAnim;
		EnemySpawnData spw;
		spw.id = e->spawnData.id;
		spw.x = e->x;
		spw.y = e->y;

		Direction d;

		for (int i = 0; i < minions ; i++)
		{
			// Hijo i
			components = new vector<Component*>();
			components->push_back(new ComponentTiledMovement(game, ((PGZGame*) game)->controller));
			c = new ComponentDivide(game,((PGZGame*) game)->controller, false);
			components->push_back(c);
			offspring = new Enemy(game, e->world);
			cAnim = new ComponentAnim(game, offspring, e->cAnim->getGfxPath());
			offspring->init(spw, components, cAnim, 15, 5, 8, 1);
		
			c->state = ReceivingDamage;
			offspring->setTimer(1, 10);
			
			switch (i) {
				case 0: d = LEFT; break;
				case 1: d = RIGHT; break;
				case 2: d = UP; break;
				case 3: d = DOWN; break;
			}

			offspring->setLastHitDirection(d);
			e->world->add(offspring);

			if (e->arena != NULL)
			{
				e->arena->addEnemy(offspring);
			}
		}	
	}
}

void ComponentDivide::onCStep(Enemy* e)
{	
	Player* p = NULL;
	int nx = 0;
	int ny = 0;
	float d = 0;
	int xtemp = e->x;
	int ytemp = e->y;
		int tmpx, tmpy;
	bool out;
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

			// Bounce del player
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
		if (other.b == "player")
		{
			enemy->damagePlayer((Player*) e, enemy->strength, 255);
		
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
				enemy->setTimer(1, 10);
			}
		}
		else if (other.b == "enemy")
		{
			if (state != ReceivingDamage)
			{
				mov->goBack();
				state = Stand;
				enemy->setTimer(0, 15+rand()%15);
			}
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

void ComponentDivide::setMinions(int n)
{
	if (n > 4)
		n = 4;
	if (n < 2)
		n = 2;

	minions = n;
}