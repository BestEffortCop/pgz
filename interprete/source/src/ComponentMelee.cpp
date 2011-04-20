#include "ComponentMelee.h"

#define IMG_WIDTH 16    // ancho de la imagen
#define IMG_HEIGHT 16    // alto de la imagen
#define IMG_PATH "data/graphics/coltest.png"


ComponentMelee::ComponentMelee(Game* game, Controller* cont) : Component()
{
	this->cont = cont;
	this->game = game;
}

void ComponentMelee::onCInit(Enemy* e)
{
	// Comenzamos en una direccion random y estado Normal
	dir = (Direction) ((rand() % 4) +1);
	state = Normal;
	dead = false;
	lastEnemyDirection = UP;  //FIXME ESTO LO ESTABLECERA EL ONDAMAGE

	// Inicializamos damageable
	//FIXME POR AQUI ENTRARA ENEMYDATA DESDE LA DB
	iDamageable::init(hpProv, hpProv, 1, 0xFF);

	// Creamos la máscara
	e->mask = new MaskBox(e->x, e->y, IMG_WIDTH, IMG_HEIGHT, "meleeFucker", 0, 0); // offsets están a cero por defecto

	// Cambiamos la configuración por defecto de los flags que nos interesan
	e->solid = false;

	// Establecemos el gráfico del enemigo
	e->graphic = new Stamp(IMG_PATH, game->getGfxEngine());
}

void ComponentMelee::onCStep(Enemy* e)
{
	int xtemp, ytemp;
	int move_pixels = 1; // número de píxeles que se mueve el enemy -lvl ovejita que te pillo
	int aux = dir;
	Player* player;
	bool inScreen = false;
	int oldX;
	int oldY;

	int turnRatio = 10;
	
	switch (state)
	{
		case Normal:
			/* ********************** Normal ************************* */
			xtemp = e->x;
			ytemp = e->y;

			if (dir == RIGHT) {xtemp += move_pixels; dir = RIGHT;}
			if (dir == LEFT) {xtemp -= move_pixels; dir = LEFT;}
				// movimento vertical
			if (dir == UP) {ytemp -= move_pixels; dir = UP;}
			if (dir == DOWN) {ytemp += move_pixels; dir = DOWN;}

			//Cambiar, tiene que ver con la colision con pantalla
			oldX = e->x;
			oldY = e->y;
			e->x = xtemp;
			e->y = ytemp;
			cont->getScreenMap()->relative_position(e,inScreen);
			e->x = oldX;
			e->y = oldY;

			Entity* auxE;

			if(!inScreen){
				if (e->world->place_free(e->x, ytemp,e))
				{    
					e->y = ytemp; 
				}
				else
				{   
					e->world->moveToContact(e->x,ytemp, e);
					while(dir == aux)
						dir =(Direction) ((rand() % 4) +1);
				}

				if (e->world->place_free(xtemp, e->y,e))
				{    
					e->x = xtemp;
				}
				else
				{   
					e->world->moveToContact(xtemp,e->y, e); 
					while(dir == aux)
						dir =(Direction) ((rand() % 4) +1);
				}
			}

			//Cambiar, controla colision con pantalla.
			if (inScreen && (dir == RIGHT))
			{
				e->x -= move_pixels;
				while (dir == RIGHT)
					dir = (Direction) ((rand() % 4) +1);
			}
			else if(inScreen && (dir == LEFT))
			{
				e->x += move_pixels;
				while (dir == LEFT)
					dir = (Direction) ((rand() % 4) +1);
			}
			else if(inScreen && (dir == DOWN))
			{
				e->y -= move_pixels;
				while (dir == DOWN)
					dir = (Direction) ((rand() % 4) +1);
			}
			else if(inScreen && (dir == UP))
			{
				e->y += move_pixels;
				while (dir == UP)
					dir = (Direction) ((rand() % 4) +1);
			}
			break;

		case Damaged:
			/* ********************** Damaged ************************* */
			xtemp = e->x; 
			ytemp = e->y;

			// Bounce del enemy
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
			{    
				e->y = ytemp; 
			}
			else
			{   
				e->world->moveToContact(e->x,ytemp, e);
			}

			if (e->world->place_free(xtemp, e->y, e))
			{    
				e->x = xtemp; 
			}
			else
			{   
				e->world->moveToContact(xtemp,e->y, e); 
			}

			break;

		case Attacking:
			/*xtemp = e->x; 
			ytemp = e->y;
			if (!e->world->place_free(xtemp, ytemp, e))
			{
				auxE = NULL;
				switch (dir)
				{
				case LEFT:
						auxE = e->world->place_meeting(e->x-e->mask->width/2, e->y, e,"player");
						break;
				case RIGHT:
						auxE = e->world->place_meeting(e->x+e->mask->width/2, e->y, e, "player");
						break;
				case UP:
						auxE = e->world->place_meeting(e->x, e->y-e->mask->height/2, e, "player");
						break;
				case DOWN:
						auxE = e->world->place_meeting(e->x, e->y+e->mask->height/2, e, "player");
						break;
				}

				if (auxE != NULL)
					if (player = dynamic_cast<Player*>(auxE))
					{
						if (dir == RIGHT) {e->x += move_pixels; dir = RIGHT;}
						if (dir == LEFT) {e->x -= move_pixels; dir = LEFT;}
							// movimento vertical
						if (dir == UP) {e->y -= move_pixels; dir = UP;}
						if (dir == DOWN) {e->y += move_pixels; dir = DOWN;}
					}
			}*/
			currentAnim = Attack;
			
			break;
		
		case Dead:
			
			/* ********************** Dead ************************* */
			break;

		case Animation:
			/* ********************** Animation ************************* */
			if (((SpriteMap*) e->graphic)->animFinished())
			{
				state = savedState;
			}
			break;
	};
	
	e->graphic->setColor(Color::White);
	e->graphic->setAlpha(1);

	// Graphic settings
	switch (state)
	{
	case Normal:
		switch (currentAction)
		{
		case aWalk:
			//((SpriteMap*) e->graphic)->playAnim(getAnimName(Walk, dir));
			currentAnim = Walk;
			break;
		}
		break;
	case Attack:
		e->graphic->setColor(Color::Yellow);
		break;
	case Damaged:
		e->graphic->setColor(Color::Red);
		e->graphic->setAlpha(0.7f);
		break;
	case Dead:
		e->graphic->setColor(Color(30, 30, 30));
		break;
	case Animation:
		if (savedState == Damaged)
			e->graphic->setColor(Color::Red);
		if (savedState == Attacking)
			e->graphic->setColor(Color::Yellow);
		break;
	}
}

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
			if (state != Damaged)
			{
				// Este daño lo hará el arma que nos pega
				onDamage(5, 0x1);
				state = Damaged;
				enemy->setTimer(1, 15);
			}
		}
}

void ComponentMelee::onCRender(Enemy* e)
{
	e->Entity::onRender();
}

void ComponentMelee::onDeath()
{
	dead = true;
};

void ComponentMelee::onCTimer(Enemy* e, int timer)
{
	if (timer == 1)
	{
		if (state == Damaged)
			if (!dead)
				state = Normal;
			else {
				state = Dead;
				e->setTimer(2,10); // esto sera en el futuro esperar a fin de animacion
			}
	};

	if (timer == 2)
		e->instance_destroy();

	if (timer == 3)
		state = Normal;
};

void ComponentMelee::playAnim(EnemyAnim anim, int speed, Direction dir)
{
	/*if (dir == NONE)
		dir = this->dir;
	// Si la animación no existe, seguro que no se puede
	std::string name = getAnimName(anim, dir);
	if (name == "")
		return false;

	// Si la animación no tiene datos, algo va mal
	PlayerAnimData data = getAnimationData(anim, dir);
	if (data.numFrames < 0)
		return false;

	if (speed < 0)
		speed = data.animSpeed;

	// 1. Comprobación de estado actual: ¿permite manipulación?
	if (state == Animation)
		return false;
	// 2. Almacenar estado, animación y cosas actuales
	savedState = state;
	// 3. Establecer nueva animación
	state = Animation;
	((SpriteMap*) graphic)->playAnim(name, speed, false, false);
	currentAnim = anim;

	return true;*/
};