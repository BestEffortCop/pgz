#include "objStar.h"

void objStar::onStep()
{
	if (!place_free(x, y))
		((Level *) world)->on();
}
