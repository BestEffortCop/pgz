#include "Player.h"

#define IMG_WIDTH 14    // ancho de la imagen del player
#define IMG_HEIGHT 15    // alto de la imagen del player

// Suponemos que mask y graphic no están inicialmente creados, sino dejaría basura
Player::Player(int x, int y, Game* game, GameState* world) : GameEntity(x, y, game, world) {

   // Creamos la máscara
   mask = new MaskBox(x, y, IMG_WIDTH, IMG_HEIGHT, "player", 1, 7); // offsets están a cero por defecto

   // Cambiamos la configuración por defecto de los flags que nos interesan
   solid = true;
};

bool Player::init(std::string gfxpath, int ncol, int nrow, int hp, int mp, Controller* c)
{
	// Asignamos el gráfico a la entidad player, de momento una imagen estática
	graphic = new SpriteMap(gfxpath, ncol, nrow, game->getGfxEngine());
	this->hp = hp;
	this->mp = mp;

	controller = c;

	// CONF

	int s_up = 0;
	int s_down = 4;
	int s_right = 8;
	int s_left = 12;

	int s_frame_1 = 0;

	vector<int>* v_standup = new vector<int>();
	v_standup->push_back(s_up + s_frame_1);
	((SpriteMap*) graphic)->addAnim("stand-up",v_standup, 4,true);

	vector<int>* v_standdown = new vector<int>();
	v_standdown->push_back(s_down + s_frame_1);
	((SpriteMap*) graphic)->addAnim("stand-down",v_standdown, 4,true);

	vector<int>* v_standright = new vector<int>();
	v_standright->push_back(s_right +  s_frame_1);;
	((SpriteMap*) graphic)->addAnim("stand-right",v_standright, 4,true);

	vector<int>* v_standleft = new vector<int>();
	v_standleft->push_back(s_left +  s_frame_1);
	((SpriteMap*) graphic)->addAnim("stand-left",v_standleft, 4,true);

	int w_up = 0;
	int w_down = 4;
	int w_right = 8;
	int w_left = 12;

	int w_frame_1 = 0;
	int w_frame_2 = 1;
	int w_frame_3 = 0;
	int w_frame_4 = 2;

	vector<int>* v_walkup = new vector<int>();
	v_walkup->push_back(w_up +  w_frame_1);
	v_walkup->push_back(w_up +  w_frame_2);
	v_walkup->push_back(w_up +  w_frame_3);
	v_walkup->push_back(w_up +  w_frame_4);
	((SpriteMap*) graphic)->addAnim("walk-up",v_walkup, 4,true);

	vector<int>* v_walkdown = new vector<int>();
	v_walkdown->push_back(w_down +  w_frame_1);
	v_walkdown->push_back(w_down +  w_frame_2);
	v_walkdown->push_back(w_down +  w_frame_3);
	v_walkdown->push_back(w_down +  w_frame_4);
	((SpriteMap*) graphic)->addAnim("walk-down",v_walkdown, 4,true);

	vector<int>* v_walkright = new vector<int>();
	v_walkright->push_back(w_right +  w_frame_1);
	v_walkright->push_back(w_right +  w_frame_2);
	v_walkright->push_back(w_right +  w_frame_3);
	v_walkright->push_back(w_right +  w_frame_4);
	((SpriteMap*) graphic)->addAnim("walk-right",v_walkright, 4,true);

	vector<int>* v_walkleft = new vector<int>();
	v_walkleft->push_back(w_left +  w_frame_1);
	v_walkleft->push_back(w_left +  w_frame_2);
	v_walkleft->push_back(w_left +  w_frame_3);
	v_walkleft->push_back(w_left +  w_frame_4);
	((SpriteMap*) graphic)->addAnim("walk-left",v_walkleft, 4,true);


	dir = DOWN;
	((SpriteMap*) graphic)->playAnim("stand-down");

	return true;
}

bool Player::getNewPos(int& xtemp, int& ytemp)
{
	int move_pixels = 3; // número de píxeles que se mueve el player

	if	(((game->getInput()->key(Input::kRIGHT)) || (game->getInput()->key(Input::kLEFT)))
			&&
		 ((game->getInput()->key(Input::kUP)) || (game->getInput()->key(Input::kDOWN))))
		 move_pixels = 2;


	if (game->getInput()->key(Input::kRIGHT)) {xtemp += move_pixels; dir = RIGHT;}
	if (game->getInput()->key(Input::kLEFT)) {xtemp -= move_pixels; dir = LEFT;}
		// movimento vertical
	if (game->getInput()->key(Input::kUP)) {ytemp -= move_pixels; dir = UP;}
	if (game->getInput()->key(Input::kDOWN)) {ytemp += move_pixels; dir = DOWN;}

	return ((xtemp != x) || (ytemp != y));
}

void Player::onStep()
{

	// MOVIMIENTO
	int xtemp = x;
	int ytemp = y;

	// Comprobamos entrada para mover al player

	bool moved = getNewPos(xtemp, ytemp);

	if (moved)
	{
		if (abs(xtemp - x) >= abs(ytemp - y))
			if ((xtemp - x) >= 0)
				dir = RIGHT;
			else
				dir = LEFT;
		else
			if ((ytemp - y) >= 0)
				dir = DOWN;
			else
				dir = UP;

		switch (dir){
			case UP : ((SpriteMap*) graphic)->playAnim("walk-up");break;
			case DOWN : ((SpriteMap*) graphic)->playAnim("walk-down");break;
			case RIGHT : ((SpriteMap*) graphic)->playAnim("walk-right");break;
			case LEFT : ((SpriteMap*) graphic)->playAnim("walk-left");break;
		}
	}
	else
	{
		switch (dir){
			case UP : ((SpriteMap*) graphic)->playAnim("stand-up");break;
			case DOWN : ((SpriteMap*) graphic)->playAnim("stand-down");break;
			case RIGHT : ((SpriteMap*) graphic)->playAnim("stand-right");break;
			case LEFT : ((SpriteMap*) graphic)->playAnim("stand-left");break;
		}
	}
	if (place_free(x, ytemp))
	{    
		y = ytemp; 
	}
	else
	{   
		world->moveToContact(x,ytemp, this);
	}

	if (place_free(xtemp, y))
	{    
		x = xtemp; 
	}
	else
	{   
		world->moveToContact(xtemp,y, this);
	}

};

Dir Player::getDir(){

	return UP;

}