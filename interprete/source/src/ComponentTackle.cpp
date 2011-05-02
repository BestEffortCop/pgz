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
			state = Stand;
			e->setTimer(0, 20+rand()%15);
			tiledMov->setSpeed(2);
		}

	// Al ataquerl!
	if (state == Stand)
	{
		int nx = e->x, ny = e->y;
		if (e->dir == LEFT) nx -= 16;
		else if (e->dir == RIGHT) nx += 16;
		else if (e->dir == UP) ny -= 16;
		else if (e->dir == DOWN) ny += 16;

		Player* p = NULL;

		if (p = dynamic_cast<Player*>(e->world->place_meeting(nx, ny, e, "player")))
		{
			e->collidable = false;
			tackle(e, p);
			e->collidable = true;
			//hitPlayer(e,p);
			e->setTimer(0, 25+rand()%15);
		}
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
	case Tackle:
		e->graphic->setColor(Color::Red);
		//e->currentAnim = ATKMELEE;
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
				state = Move;
				e->setTimer(0, 1);
				break;
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

		state = Tackle;
};

void ComponentTackle::tackle(Enemy* e, Player* p)
{
	tiledMov->setSpeed(5);

	if (tiledMov != NULL)
		tiledMov->move(e->dir, e);
	else
		e->setTimer(0, rand()%30);

	state = Tackle;
}