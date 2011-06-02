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

#include "SurfaceManagerItem.h"

/***********************************************
 *			Funciones Públicas				   *
 ***********************************************/

/* SurfaceManagerItem::SurfaceManagerItem(sf::Image* surf) */
/*
	Guardamos la direccion/puntero de una imagen y la cantidad de
	enlaces simbólicos que inicialmente es 1.
*/
SurfaceManagerItem::SurfaceManagerItem(sf::Image* surf)
{
	surface = surf;
	links = 1;
}

/* void SurfaceManagerItem::link() */
/*
	Añadimos un nuevo enlace simbólico ya que alguien más
	está usando la imagen.
*/
void SurfaceManagerItem::link()
{
	links++;
}
	
/* bool SurfaceManagerItem::unlink() */
/*
	Quitamos un enlace a la imagen.
	Si no hay enlaces con la imagen entonces devolvemos true.
*/
bool SurfaceManagerItem::unlink()
{
	links--;
	return (links <= 0);
}
	
/* sf::Image* SurfaceManagerItem::getSurface() */
/*
	Devuelve puntero a la propia imagen/superficie
*/
sf::Image* SurfaceManagerItem::getSurface()
{
	return surface;
}
	
/* int SurfaceManagerItem::getLinks() */
/*
	Devuelve el número de enlaces que tiene la imagen
*/
int SurfaceManagerItem::getLinks()
{
	return links;
}