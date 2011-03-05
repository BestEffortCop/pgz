#include "ObjBad.h"


void objBad::onCollision(CollisionPair other)
{
	((Level *) world)->on();
	stepped = true;
}