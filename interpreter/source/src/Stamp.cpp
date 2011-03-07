#include "Stamp.h"

Stamp::Stamp(string fname, GfxEngine* gfxEngine) : Graphic()
{
	this->image = new Image(fname,gfxEngine);
	this->gfxEngine = gfxEngine;

	// se toma el ancho y alto de la imagen.
	w = image->getWidth();
	h = image->getHeigth();
};

Stamp::Stamp(Image* image, GfxEngine* gfxEngine)
{
	this->image = image;
	this->gfxEngine = gfxEngine;

	// se toma el ancho y alto de la imagen.
	w = image->getWidth();
	h = image->getHeigth();
};
		
Stamp::~Stamp()
{
	// se libera la memoria reservada para la imagen.
	delete image;
};

int Stamp::getWidth()
{
	return w;
};
		
int Stamp::getHeight()
{
	return h;
};

void Stamp::render(int x, int y)
{
	gfxEngine->renderExt(image,x+originX,y+originY, *color, alpha, scaleH, scaleV, rotation, NULL, originX, originY);
};