#include "ComponentTest.h"

ComponentTester::ComponentTester(Game* g, Controller* c) : Component()
{
	game = g;
	cont = c;
	tiledMov = NULL;
};

ComponentTester::~ComponentTester()
{
};

void ComponentTester::onCInit(Enemy* e)
{
	// Creamos la máscara
	e->mask = new MaskBox(e->x, e->y, 16, 12, "enemy", 0, 0);

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
		tiledMov->initSettings(16, 16, 3);

	state = STAND;
	e->dir = DOWN;
	e->setTimer(0, rand()%90);
};

void ComponentTester::onCTimer(Enemy* e, int timer)
{
	if (timer == 0)
	{
		// Time to make a decission!
		switch (state)
		{
			case STAND:
			{
				if (rand()%10 < 2)
					// Quietecito
					e->setTimer(0, rand()%90);
				else
				{
					state = MOVE;
					e->dir = (Direction) (1+rand()%4);
					if (tiledMov != NULL)
						tiledMov->move(e->dir, e);
					else
						e->setTimer(0, rand()%90);
				}
				break;
			}
			case ATTACK:
				state = MOVE;
				e->setTimer(0, 1);
				break;
		}
	};
};

void ComponentTester::onCStep(Enemy* e)
{
	if (tiledMov != NULL)
		if (!tiledMov->isLocked() && state == MOVE)
		{
			state = STAND;
			e->setTimer(0, 25+rand()%65);
		}

	// Al ataquerl!
	if (state == STAND)
	{
		int nx = e->x, ny = e->y;
		if (e->dir == LEFT) nx -= 4;
		else if (e->dir == RIGHT) nx += 4;
		else if (e->dir == UP) ny -= 4;
		else if (e->dir == DOWN) ny += 4;

		Player* p = NULL;

		if (p = dynamic_cast<Player*>(e->world->place_meeting(nx, ny, e, "player")))
			hitPlayer(e, p), e->setTimer(0, 15+rand()%15);
	}

	// Animation
	e->graphic->setColor(Color::White);
	switch (state)
	{
	case STAND:
		e->currentAnim = Enemy::STAND;
		e->inAnim = true;
		break;
	case MOVE:
		e->currentAnim = Enemy::WALK;
		e->inAnim = true;
		break;
	case ATTACK:
		e->graphic->setColor(Color::Red);
		e->currentAnim = Enemy::ATKMELEE;
		e->inAnim = true;
	};
};

void ComponentTester::onCCollision(Enemy* enemy, CollisionPair other, Entity* e)
{
	if (other.b == "player")
	{
		hitPlayer(enemy, dynamic_cast<Player*>(e));
	}
	else if (other.b == "enemy")
	{
		tiledMov->goBack();
	};
};

void ComponentTester::hitPlayer(Enemy* enemy, Player* p)
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

		state = ATTACK;
};