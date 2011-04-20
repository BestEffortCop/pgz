#include "ComponentMelee.h"

#define IMG_WIDTH 16    // ancho de la imagen
#define IMG_HEIGHT 16    // alto de la imagen
#define IMG_PATH "data/graphics/coltest.png"


ComponentMelee::ComponentMelee(Game* game, Controller* cont) : Component()
{
	this->cont = cont;
	this->game = game;
}

// POR AQUI ENTRARA ENEMYDATA DESDE LA DB
void ComponentMelee::onCInit(Enemy* e)
{
	// Comenzamos en una direccion random y estado Normal
	dir = (Direction) ((rand() % 4) +1);
	state = Normal;
	dead = false;

	// Inicializamos damageable
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
	int move_pixels = 2; // número de píxeles que se mueve el enemy
	int aux = dir;
	Player* player;
	bool inScreen = false;
	int oldX;
	int oldY;
	
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

			//Cambiar, tiene que ver con la coolision con pantalla
			oldX = e->x;
			oldY = e->y;
			e->x = xtemp;
			e->y = ytemp;
			cont->getScreenMap()->relative_position(e,inScreen);
			e->x = oldX;
			e->y = oldY;

			Entity* auxE;

			if (!e->world->place_free(xtemp, ytemp,e))
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
			}


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
			// Este daño vendrá dado por el arma que nos pega
			onDamage(5, 0x1);
			
			xtemp = e->x, ytemp = e->y;

			// Bounce del enemy
			if (lastEnemyDirection == UP) ytemp += e->getTimer(3)/2;
			else if (lastEnemyDirection == DOWN) ytemp -= e->getTimer(3)/2;
			else if (lastEnemyDirection == LEFT) xtemp += e->getTimer(3)/2;
			else if (lastEnemyDirection == RIGHT) xtemp -= e->getTimer(3)/2;
			else if (lastEnemyDirection == UPLEFT) ytemp += e->getTimer(3)/2, xtemp += e->getTimer(5)/2;
			else if (lastEnemyDirection == UPRIGHT) ytemp += e->getTimer(3)/2, xtemp -= e->getTimer(5)/2;
			else if (lastEnemyDirection == DOWNLEFT) ytemp -= e->getTimer(3)/2, xtemp += e->getTimer(5)/2;
			else if (lastEnemyDirection == DOWNRIGHT) ytemp -= e->getTimer(3)/2, xtemp -= e->getTimer(5)/2;

			// Actualizamos posición
			if (e->world->place_free(e->x, ytemp,e))
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
		
		case Dead:
			/* ********************** Dead ************************* */
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
		e->graphic->setColor(Color::Red);
		break;
	case Damaged:
		e->graphic->setColor(Color::Red);
		e->graphic->setAlpha(0.7f);
		break;
	case Dead:
		e->graphic->setColor(Color(30, 30, 30));
		break;
	}
}

void ComponentMelee::onCCollision(Enemy* enemy, CollisionPair other, Entity* e)
	{
		if (other.b == "coltest")
		{
			e->instance_destroy();
		}
		else if (other.b == "player")
		{
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

			if (state != Damaged)
			{
				state = Damaged;
				e->setTimer(3, 15);
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
	if (timer == 3)
	{
		if (state == Damaged)
			if (!dead)
				state = Normal;
			else state = Dead;
	};
};
