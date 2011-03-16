#include "ObjBad.h"


void objBad::onCollision(CollisionPair other)
{
	((Level *) world)->on();
	stepped = true;
	((SpriteMap*) graphic)->setColor(Color(rand()%255, rand()%255, rand()%255));
}