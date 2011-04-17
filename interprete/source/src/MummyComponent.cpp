#include "MummyComponent.h"

#define IMG_WIDTH 16    // ancho de la imagen del mummy
#define IMG_HEIGHT 16    // alto de la imagen del mummy
#define IMG_PATH "data/graphics/coltest.png"

MummyComponent::MummyComponent(Game* game, Controller* cont) : Component()
{
	srand(time(NULL));
	this->cont = cont;
	this->game = game;
	dir = UP;
	xtemp = 0;
	ytemp = 0;
}
		
void MummyComponent::onCInit(Enemy* e)
{
	// Creamos la máscara
   e->mask = new MaskBox(e->x, e->y, IMG_WIDTH, IMG_HEIGHT, "mummy", 0, 0); // offsets están a cero por defecto

   // Cambiamos la configuración por defecto de los flags que nos interesan
   e->solid = false;

   // Establecemos el gráfico del enemigo
   e->graphic = new Stamp(IMG_PATH,game->getGfxEngine());
}

void MummyComponent::onCStep(Enemy* e)
{
	int move_pixels = 3; // número de píxeles que se mueve el enemy
	int aux = dir;
	Player* player;

	bool inScreen = false;
	xtemp = e->x;
	ytemp = e->y;

	if (dir == RIGHT) {xtemp += move_pixels; dir = RIGHT;}
	if (dir == LEFT) {xtemp -= move_pixels; dir = LEFT;}
		// movimento vertical
	if (dir == UP) {ytemp -= move_pixels; dir = UP;}
	if (dir == DOWN) {ytemp += move_pixels; dir = DOWN;}

	//Cambiar, tiene que ver con la coolision con pantalla
	int oldX = e->x;
	int oldY = e->y;
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

}

void MummyComponent::onCCollision(Enemy* enemy, CollisionPair other, Entity* e)
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

			((Player*) e)->setLastEnemyDirection(d);
			((Player*) e)->onDamage(5, 0x1);
		}
}

void MummyComponent::onCRender(Enemy* e)
{
	e->Entity::onRender();
}