#include "objStar.h"

void objStar::onStep()
{
	if (!world->position_free(x + 10, y + 10))
		((Level *) world)->on();
}
