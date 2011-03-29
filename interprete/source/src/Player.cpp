#include "Player.h"

#define IMG_WIDTH 10    // ancho de la imagen del player
#define IMG_HEIGHT 16    // alto de la imagen del player

// Suponemos que mask y graphic no están inicialmente creados, sino dejaría basura
Player::Player(int x, int y, Game* game, GameState* world) : GameEntity(x, y, game, world) {



   // Creamos la máscara
   mask = new MaskBox(x, y, IMG_WIDTH, IMG_HEIGHT, "player"); // offsets están a cero por defecto

   // Cambiamos la configuración por defecto de los flags que nos interesan
   solid = true;
   collidable = false;
};

bool Player::init(std::string gfxpath, int ncol, int nrow, int hp, int mp)
{
	// Asignamos el gráfico a la entidad player, de momento una imagen estática
   graphic = new SpriteMap(gfxpath, ncol, nrow, game->getGfxEngine());
   this->hp = hp;
   this->mp = mp;


   vector<int>* v = new vector<int>();
   v->push_back(0);
   ((SpriteMap*) graphic)->addAnim("walk",v, 1,false);
   ((SpriteMap*) graphic)->playAnim("walk");
   return true;
}

void Player::onStep()
{

   // MOVIMIENTO
   int move_pixels = 2; // número de píxeles que se mueve el player
   int xtemp = x;
   int ytemp = y;

   // Comprobamos entrada para mover al player
       // movimiento horizontal
   if (game->getInput()->key(Input::kRIGHT)) xtemp += move_pixels;
   else if (game->getInput()->key(Input::kLEFT)) xtemp -= move_pixels;
       // movimento vertical
   if (game->getInput()->key(Input::kUP)) ytemp -= move_pixels;
   else if (game->getInput()->key(Input::kDOWN)) ytemp += move_pixels;

   // Si el sitio está libre movemos el player, sino lo dejamos donde está
   if (place_free(xtemp, ytemp))
       x = xtemp; y = ytemp; // movimiento de la entidad
};

Dir Player::getDir(){

	return UP;

}