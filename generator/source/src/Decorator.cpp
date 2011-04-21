#include "Decorator.h"

Decorator::Decorator()
{
	theme = "";
	zone = "";
	autoTiler = NULL;
}

Decorator::~Decorator()
{
	if (autoTiler != NULL) delete autoTiler;
}

void Decorator::init(string zone, string theme, string tileSetPath)
{
	this->zone = zone;
	this->theme = theme;

	if (autoTiler != NULL) delete autoTiler; // si había un autotiler anterior lo borramos
	autoTiler = new AutoTiler(tileSetPath);	 // creamos el nuevo
}

