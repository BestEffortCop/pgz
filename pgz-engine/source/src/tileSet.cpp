#include "TileSet.h"

//Constructora parametrizada
TileSet::TileSet(string path, int tileW, int tileH, GfxEngine* gfxEngine, bool transparent)
{
	//Escribo los atributos de entrada
	this->path = path;
	this->gfxEngine = gfxEngine;
	this->tileW = tileW;
	this->tileH = tileH;
	
	//Cargo la imagen correspondiente
	this->image = new Image(path, gfxEngine, transparent);
	
	//Compruebo el ancho y alto de la imagen
	tileSetW = image->getWidth();
	tileSetH = image->getHeigth();
	
	//Calculo el numero de tiles de ancho y alto que me salen para el tileSet a partir del tamaño
	//del mismo y del alto y ancho de un tile
	colNumber = tileSetW/tileW;
	rowNumber = tileSetH/tileH;
}

//Destructora
TileSet::~TileSet()
{
	//Si habia una imagen valida en el tileSet
	if (image != NULL)
	{
		//La destruimos
		delete image;
		image = NULL;
	}
}

//Devuelve la imagen
Image* TileSet::getImg()
{
	return image;
}

//Devuelve el número de columnas del tileSet
int TileSet::getColumns()
{
	return colNumber;
}

//Devuelve el número de filas del tileSet
int TileSet::getRows()
{
	return rowNumber;
}