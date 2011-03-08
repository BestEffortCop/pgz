#include "Stamp.h"

//Construye un Stamp a partir de un nombre de imagen
Stamp::Stamp(string fname, GfxEngine* gfxEngine) : Graphic()
{
	//Crea una imagen a partir del nombre que le pasan y el subsistema grafico
	this->image = new Image(fname,gfxEngine);
	//Apunta a su subsistema grafico
	this->gfxEngine = gfxEngine;

	// se toma el ancho y alto de la imagen.
	w = image->getWidth();
	h = image->getHeigth();
};

//Construye un Stamp a partir de una imagen
Stamp::Stamp(Image* image, GfxEngine* gfxEngine)
{
	//Toma la imagen y el subsistema grafico que le proporcionan
	this->image = image;
	this->gfxEngine = gfxEngine;

	// se toma el ancho y alto de la imagen.
	w = image->getWidth();
	h = image->getHeigth();
};

//Destructora
Stamp::~Stamp()
{
	// se libera la memoria reservada para la imagen.
	delete image;
};


//Devuelve en encho de la imagen
int Stamp::getWidth()
{
	return w;
};

//Devuelve el alto de la imagen
int Stamp::getHeight()
{
	return h;
};

//Metodo de renderizado del Stamp, que hace que el subsistema grafico lo pinte en el lugar indicado
void Stamp::render(int x, int y)
{
	gfxEngine->renderExt(image,x+originX,y+originY, *color, alpha, scaleH, scaleV, rotation, NULL, originX, originY);
};