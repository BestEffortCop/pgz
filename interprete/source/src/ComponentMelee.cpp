#include "ComponentMelee.h"

// Esto tendra que recibirlo de algun lado
#define IMG_WIDTH 16    // ancho de la imagen
#define IMG_HEIGHT 16    // alto de la imagen

ComponentMelee::ComponentMelee(Game* game, Controller* cont) : Component()
{
	this->cont = cont;
	this->game = game;
};

void ComponentMelee::onCInit(Enemy* e)
{
	// Comenzamos en una direccion random y estado Normal
	e->dir = (Direction) ((rand() % 4) +1);
	state = savedState = Walking;
	lastEnemyDirection = UP;  //FIXME ESTO LO ESTABLECERA EL ONDAMAGE

	// Inicializamos damageable
	iDamageable::init(e->hpMax, e->hpMax, 1, 0xFF);

	// Creamos la máscara
	e->mask = new MaskBox(e->x, e->y, IMG_WIDTH, IMG_HEIGHT, "meleeFucker", 0, 0);

	// Cambiamos la configuración por defecto de los flags que nos interesan
	e->solid = false;

};

void ComponentMelee::onCStep(Enemy* e)
{
	int xtemp, ytemp;
	Player* player;
	int chasePlayerId = 0;
	int chaseDirX, chaseDirY;
	int collDist;
	
	switch (state)
	{
		/* ********************** Standing ************************* */
		case Standing:
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
			// FIXME POR AHORA SOLO REBOTA HACIA ABAJO PORQUE LASTENEMYDIRECTION NO LO SETEA EL ONDAMAGE DEL TOOL QUE NOS PEGA
			if (lastEnemyDirection == UP) ytemp += e->getTimer(1)/2;
			else if (lastEnemyDirection == DOWN) ytemp -= e->getTimer(1)/2;
			else if (lastEnemyDirection == LEFT) xtemp += e->getTimer(1)/2;
			else if (lastEnemyDirection == RIGHT) xtemp -= e->getTimer(1)/2;
			else if (lastEnemyDirection == UPLEFT) ytemp += e->getTimer(1)/2, xtemp += e->getTimer(1)/2;
			else if (lastEnemyDirection == UPRIGHT) ytemp += e->getTimer(1)/2, xtemp -= e->getTimer(1)/2;
			else if (lastEnemyDirection == DOWNLEFT) ytemp -= e->getTimer(1)/2, xtemp += e->getTimer(1)/2;
			else if (lastEnemyDirection == DOWNRIGHT) ytemp -= e->getTimer(1)/2, xtemp -= e->getTimer(1)/2;

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

		/* ********************** Attacking ************************* */
		case Attacking:			
			break;

		/* ********************** Chasing ************************* */
		case Chasing:
			player = cont->getPlayer(chasePlayerId);
			chaseDirX = player->x - e->x;
			chaseDirY = player->y - e->y;
			
			if (abs(chaseDirX) - abs(chaseDirY) >= 0)
				// Tiene prioridad movimiento horizontal
				chaseDirX > 0 ? e->dir = RIGHT : e->dir = LEFT;
			else 
				// Tiene prioridad movimiento vertical
				chaseDirY > 0 ? e->dir = DOWN : e->dir = UP;
			
			// Nos movemos en esa direccion
			moveInDir(e, moveSpeed);

			// esto es una cutrez forgive-me-kurnigam :(
			collDist = max(player->mask->width/2 + e->mask->width, player->mask->height/2+ e->mask->height);
			if(getDistance(e->x, e->y, player->x, player->y) < collDist)
				state = Attacking;
			break;

		/* ********************** Dead ************************* */
		case Dying:
			e->dead = true;
			break;

		/* ********************** Animation ************************* */
		case Animation:
			// Si ha terminado la animacion recuperamos el estado
			if (!e->inAnim)
				state = savedState;
			break;
	};
	
	e->graphic->setColor(Color::White);
	e->graphic->setAlpha(1);

	// Graphic settings
	switch (state)
	{
	case Standing:
		e->currentAnim = Enemy::STAND;
		savedState = Standing;
		// Indicamos a ComponentAnim que reproduzca la animacion
		e->inAnim = true;
		break;
	case Walking:
		e->currentAnim = Enemy::WALK;
		savedState = Walking;
		e->inAnim = true;
		break;
	case Attacking:
		e->currentAnim = Enemy::ATKMELEE;
		e->graphic->setColor(Color::Red);
		savedState = Attacking;
		e->inAnim = true;
		break;
	case ReceivingDamage:
		e->currentAnim = Enemy::DAMAGED;
		savedState = ReceivingDamage;
		e->inAnim = true;
		break;
	case Chasing:
		e->currentAnim = Enemy::WALK;
		e->graphic->setColor(Color::Green);
		savedState = Chasing;
		e->inAnim = true;
		break;
	case Dying:
		e->currentAnim = Enemy::DEAD;
		e->graphic->setAlpha(0.8f);
		savedState = Dying;
		e->inAnim = true;
		break;
	case Animation:
		if (savedState == Attacking)
			e->graphic->setColor(Color::Red);
		break;
	}
};

void ComponentMelee::onCCollision(Enemy* enemy, CollisionPair other, Entity* e)
{
	if (other.b == "coltest")
	{
		enemy->instance_destroy();
	}

	else if (other.b == "player")
	{
		// Mover al player
		Direction d;
		int ocx, ocy, mcx, mcy, vunit, hunit;

		mcx = enemy->x+enemy->mask->xoffset;
		mcy = enemy->y+enemy->mask->yoffset;

		ocx = e->x+e->mask->xoffset+(e->mask->width/2);
		ocy = e->y+e->mask->yoffset+(e->mask->height/2);

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

		((Player*) e)->setLastEnemyDirection(d);
		((Player*) e)->onDamage(5, 0x1);

		if (state != Attacking)
		{
			state = Attacking;
			enemy->setTimer(3,20); // esto sera en el futuro esperar a fin de animacion
		}
	}

	else if (other.b == "tool")
	{
		if (state != ReceivingDamage)
		{
			// Este daño lo hará el arma que nos pega
			state = ReceivingDamage;
			onDamage(5, 0x1);
			enemy->setTimer(1, 10);
		}
	}
};

// Esta funcion la invoca automaticamente iDamageable
void ComponentMelee::onDeath()
{
	state = Dying;
};

void ComponentMelee::onCTimer(Enemy* e, int timer)
{
	// timer de bounce al ser damageado
	if (timer == 1)
	{
		if (state == ReceivingDamage)
			if (!e->dead)
				state = Walking;
		if (state == Dying)
				e->setTimer(2,15); // esto sera en el futuro esperar a fin de animacion
	};

	// timer de desaparecer
	if (timer == 2)
		e->instance_destroy();

	// timer de la animacion de Attack (esto cambiara)
	if (timer == 3)
		state = Walking;

	// timer de estar persiguiendo
	if (timer == 4)
		if (state == Chasing || state == Attacking)
			state = Walking;
		
};

bool ComponentMelee::checkPlayerNear(Player* p, Enemy* e, int dist)
{
	// Solo comprobamos si estamos mirando hacia el player nos ahorramos sqrt
	switch (e->dir)
	{
		case UP: 
			if (p->y <= e->y)
				return getDistance(e->x, e->y, p->x, p->y) < dist;
			break;
		case DOWN:
			if (p->y >= e->y)
				return getDistance(e->x, e->y, p->x, p->y) < dist;
			break;
		case LEFT:
			if (p->x <= e->y)
				return getDistance(e->x, e->y, p->x, p->y) < dist;
			break;
		case RIGHT:
			if (p->y >= e->y)
				return getDistance(e->x, e->y, p->x, p->y) < dist;
			break;
	}
	return false;
};

int ComponentMelee::getDistance(int x1, int y1, int x2, int y2)
{
	int sqr1, sqr2;
	sqr1 = (x2-x1)*(x2-x1);
	sqr2 = (y2-y1)*(y2-y1);
	return (int)sqrt((double)(sqr1+sqr2));
};

// Mueve al enemigo en la direccion en la que este mirando, devuelve si se chocó con algo
bool ComponentMelee::moveInDir(Enemy* e, int speed){
	int xtemp = e->x;
	int ytemp = e->y;
	bool outOfScreen = true, collided = false;

	// Miramos a ver si seguimos en territorio pantallil
	cont->getScreenMap()->relative_position(e,outOfScreen);
	
	// Y corregimos apropiadamente
	if (outOfScreen)
		if (e->dir == RIGHT){
			e->x -= speed;
			e->dir = LEFT;
		}
		else if(e->dir == LEFT){
			e->x += speed;
			e->dir = RIGHT;
		}
		else if(e->dir == UP){
			e->y += speed;
			e->dir = DOWN;
		}
		else if(e->dir == DOWN){
			e->y -= speed;
			e->dir = UP;
		}
	
	// Coord donde intentaremos movernos
	if (e->dir == RIGHT) xtemp += speed;
	if (e->dir == LEFT) xtemp -= speed;
	if (e->dir == UP) ytemp -= speed;
	if (e->dir == DOWN) ytemp += speed;

	// Nos intentamos mover (el orden da igual), probamos placeFree si falla hacemos moveToContact
	// Primero vertical
	e->world->place_free(e->x, ytemp, e) ? e->y = ytemp : e->world->moveToContact(e->x, ytemp, e), collided = true;
	// Luego horizontal
	e->world->place_free(xtemp, e->y, e) ? e->x = xtemp : e->world->moveToContact(xtemp, e->y, e), collided = true; 
	
	return collided;
};

void ComponentMelee::setLastEnemyDirection(Direction dir)
{
	if (state != ReceivingDamage)
		lastEnemyDirection = dir;
};

Direction ComponentMelee::getDifDir(Direction direc){
	Direction newDir = (Direction) ((rand() % 4) +1);
	while (direc == newDir)
		newDir = (Direction) ((rand() % 4) +1);
	return newDir;
};