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
	char r;
	//! Valor G de la nomenclatura RGB para el color.
	char g;
	//! Valor B de la nomenclatura RGB para el color.
	char b;
	
	//! Construye el color a partir de unos valores RGB dados
	/*!
		\param red Valor del rojo.
		\param green Valor del verde.
		\param blue Valor del azul.
	*/
	Color(char red, char green, char blue) { r = red; g = green; b = blue;}
	
	
	//! Color predefinido Negro
	static const Black = Color(0, 0, 0);
	//! Color predefinido Blanco
	static const White = Color(255, 255, 255);
	//! Color predefinido Rojo
	static const Red = Color(255, 0, 0);
	//! Color predefinido Amarillo
	static const Yellow = Color(255, 255, 0);
	//! Color predefinido Verde
	static const Green = Color(0, 255, 0);
	//! Color predefinido Cian
	static const Cyan = Color(0, 255, 255);
	//! Color predefinido Azul
	static const Blue = Color(0, 0, 255);
	//! Color predefinido Magenta
	static const Magenta = Color(255, 0, 255);
};
	
#endif