/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//	  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

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

int TileSet::getTileW()
{
	return tileW;
};

int TileSet::getTileH()
{
	return tileH;
};