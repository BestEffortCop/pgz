#include "ScreenMap.h"

ScreenMap::ScreenMap(vector<Entity*>* entidades, int width, int height, int tileW, int tileH, int x, int y, GfxEngine* gfxEngine) : Map(tileW, tileH, gfxEngine)
{
	//Llamo a la constructora de Map con los parametros que me pasan
	//Pongo los atributos de la clase al valor que me dan
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->entidades = entidades;
}

ScreenMap::~ScreenMap(){};

vector<CollisionPair>* ScreenMap::checkColision(Entity* e)
{
	//Cojo el solidGrid de mi Map, y le pido que me de el par de colision con la entidad que me han pasado
	return this->solidGrid->collide(e->mask);
}

bool ScreenMap::isInBounds(Entity* e)
{
	//Cojo el solidGrid de mi Map y le pregunto si la entidad se encuentra dentro del mismo
	return this->solidGrid->isMaskInbounds(e->mask);
}

//Su funcion seria la de mantener actualizados los tiles animados, pero por ahora no hay
void ScreenMap::update(){};

//
void ScreenMap::render()
{
	//Avisa al tileMap de que se renderize
	this->tileMap->render(x,y);
}