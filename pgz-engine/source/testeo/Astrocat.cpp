#include "Astrocat.h"
#include "OneLevel.h"

void AstroCat::onDestroy()
{
	if (hit)
		((OneLevel*) world)->oneDown(*myColor);

	delete hitS;
};