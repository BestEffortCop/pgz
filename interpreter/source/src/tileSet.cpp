#include "TileSet.h"


//Constructora parametrizada
TileSet::TileSet(string path, int tileW, int tileH, GfxEngine* gfxEngine, bool transparent)
{
	//Escribo losa atributos de entrada
	this->path = path;
	this->gfxEngine = gfxEngine;
	this->tileW;
	this->tileH;
	
	//Cargo la imagen correspondiente
	this->image = new Image(path, gfxEngine, transparent);
	
	//Compruebo el ancho y alto de la imagen
	tileSetW = image->getWidth();
	tileSetH = image->getHeigth();
	
	//Calculo el numero de tiles de ancho y alto que me salen para el tileSet
	colNumber = tileSetW/tileW;
	rowNumber = tileSetH/tileH;
}


//Destructora
TileSet::~TileSet()
{
	delete image;
	image = NULL;	
}

Image* TileSet::getImg()
{
	return image;
}

int TileSet::getColumns()
{
	return colNumber;
}

int TileSet::getRows()
{
	return rowNumber;
}