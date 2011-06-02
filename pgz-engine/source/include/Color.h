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

#pragma once
#ifndef __COLOR_H__
#define __COLOR_H__

//! Representa un color RGB
/*!
	Los colores se representan mediante 3 atributos red, green y blue,
	de 0 a 255 cada uno, correspondientes a los colores primarios luz,
	rojo, verde y azul, que indicarán el valor del color.
*/

class Color
{
	public:
	
	//! Valor R de la nomenclatura RGB para el color.
	unsigned char r;
	//! Valor G de la nomenclatura RGB para el color.
	unsigned char g;
	//! Valor B de la nomenclatura RGB para el color.
	unsigned char b;
	
	//! Construye el color a partir de unos valores RGB dados
	/*!
		\param red Valor del rojo.
		\param green Valor del verde.
		\param blue Valor del azul.
	*/
	Color(unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255);
	
	//! Color predefinido Negro
	static const Color Black;
	//! Color predefinido Blanco
	static const Color White;
	//! Color predefinido Rojo
	static const Color Red;
	//! Color predefinido Amarillo
	static const Color Yellow;
	//! Color predefinido Verde
	static const Color Green;
	//! Color predefinido Cian
	static const Color Cyan;
	//! Color predefinido Azul
	static const Color Blue;
	//! Color predefinido Magenta
	static const Color Magenta;
};
	
#endif