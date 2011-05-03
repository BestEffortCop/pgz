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
	e->mask = new MaskBox(e->x, e->y, 16, 16, "enemy", 0, 0);

	// Cambiamos la configuración por defecto de los flags que nos interesan
	e->solid = false;

	// Soooombra
	e->initShadow(GameEntity::sMedium);

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
		tiledMov->initSettings(16, 16, 2);

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
				e->setTimer(0, 20+rand()%15);
				state = Stand;
			}
			
			tiledMov->setSpeed(2);
		}

	if (state == Stand)
	{
		Player* p = NULL;
		int nx = 0;
		int ny = 0;
		float d = 0;
		for (int i = 0; i < cont->getNumPlayers(); i++)
		{
			p = cont->getPlayer(i);

			// Distancia euclídea
			nx = p->x - e->x;
			ny = p->y - e->y;
			d = sqrt(pow((double) nx, (int) 2) + pow((double) ny, (int) 2));

			if (d < 32)
			{
				if (p->x > e->x)
					e->dir = RIGHT;
				else
					e->dir = LEFT;


				if (p->y > e->y)
				{
					if (abs((int) p->x - e->x) < abs(p->y - e->y))
						e->dir = DOWN;
				}
				else
				{
					if (abs((int) p->x - e->x) < abs(p->y - e->y))
						e->dir = UP;
				}
				state = Charge;
				e->setTimer(0, 15);
			}
		}
	}

	// Animation
	e->graphic->setColor(Color::White);
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
		e->graphic->setColor(Color::Red);
		e->currentAnim = WALK;
	case Charge:
		int i = e->getTimer(0);
		Color c = Color (255, 255 - (150 - i*10), 255 - (150 - i*10));
		e->currentAnim = ATKMELEE;
		e->graphic->setColor(c);
	};
};

void ComponentTackle::onCCollision(Enemy* enemy, CollisionPair other, Entity* e)
{
	if (other.b == "player")
	{
		hitPlayer(enemy, dynamic_cast<Player*>(e));
	}
	else if (other.b == "enemy")
	{
		tiledMov->goBack();
	};
}

void ComponentTackle::onCRender(Enemy* e){};
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
				//e->setTimer(0, 25+rand()%15);
				break;
			case Rest:
				state = Stand;
				e->setTimer(0, 10);
		}
	};
}

void ComponentTackle::onCDestroy(Enemy* e){}
void ComponentTackle::onCCustomEvent(Enemy* e, int event){};
void ComponentTackle::onCInitStep(Enemy* e){};
void ComponentTackle::onCEndStep(Enemy* e){};
void ComponentTackle::onCEndWorld(Enemy* e){};

void ComponentTackle::hitPlayer(Enemy* enemy, Player* p)
{
			// Mover al player
		Direction d;
		int ocx, ocy, mcx, mcy, vunit, hunit;

		mcx = enemy->x+enemy->mask->xoffset;
		mcy = enemy->y+enemy->mask->yoffset;

		ocx = p->x+p->mask->xoffset+(p->mask->width/2);
		ocy = p->y+p->mask->yoffset+(p->mask->height/2);

		vunit = enemy->mask->height/3;
		hunit = enemy->mask->width/3;

		if (ocx < mcx+hunit)
		{
			if (ocy < mcy+vunit) d = DOWNRIGHT;
			else if (ocy >= mcy+vunit && ocy < mcy+vunit*2) d = RIGHT;
			else d = UPRIGHT;
		}
		else if (ocx >= mcx+hunit && ocx < mcx+hunit*2)
		{
			if (ocy < mcy+vunit) d = DOWN;
			else if (ocy >= mcy+vunit && ocy < mcy+vunit*2) d = NONE;
			else d = UP;
		}
		else
		{
			if (ocy < mcy+vunit) d = DOWNLEFT;
			else if (ocy >= mcy+vunit && ocy < mcy+vunit*2) d = LEFT;
			else d = UPLEFT;
		}

		(p)->setLastEnemyDirection(d);
		(p)->onDamage(5, 0x1);
};

void ComponentTackle::tackle(Enemy* e)
{
	tiledMov->setSpeed(4);

	if (tiledMov != NULL)
		tiledMov->move(e->dir, e);
	else
		e->setTimer(0, rand()%30);

	state = Tackle;
}