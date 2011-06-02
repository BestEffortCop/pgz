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

#include "Graphic.h"

Graphic::Graphic() 
{
	color = new Color(255,255,255);
	alpha = 1;
	scaleH = 1;
	scaleV = 1;
	rotation = 0;
	originX = 0;
	originY = 0;
};
	
//! Destructora
Graphic::~Graphic()
{	
	if (color != NULL)
		delete color;
	color = NULL;
}
		
//! Realiza la actualización en cada paso del juego.
void Graphic::update() {}
	
//! Realiza el renderizado de la imagen en las coordenadas dadas de la ventana de juego.
/*!
	\param x Coordenada x de reenderizado.
	\param y Coordenada y de reenderizado.
*/
 void Graphic::render(int x, int y){}
		
//! Tinta el gráfico del color dado
/*!
	\param color Color con el que se tintará la imagen.
*/
 void Graphic::setColor(Color color)
{
	*this->color = color;
}
	
//! Cambia la transparencia del gráfico a un valor alpha.
/*!
	\param alpha Valor de la nueva transparencia del gráfico.
*/
 void Graphic::setAlpha(float alpha)
{
	this->alpha = alpha;
}
	
//! Cambia la escala con que será renderizado el gráfico a un valor scale.
/*!
	\param scale Valor de la nueva escala del gráfico.
*/
 void Graphic::setScale(float scaleH, float scaleV)
{
	this->scaleH = scaleH;
	this->scaleV = scaleV;
}
	
//! Rota la imagen un angulo rotation.
/*!
	\param rotation Valor del ángulo que rotará el gráfico.
*/
 void Graphic::setRotation(float rotation)
{
	this->rotation = rotation;
}

//! Establece la posición horizontal del origen de rotación.
/*!
	\param x Posición horizontal del origen
*/
 void Graphic::setOriginX(int x)
{
	this->originX = x;
}

//! Establece la posición vertical del origen de rotación.
/*!
	\param x Posición vertical del origen
*/
 void Graphic::setOriginY(int y)
{
	this->originY = y;
}

/* Uncomented zone of weirdness */

float Graphic::getAlpha() 
{ 
	return alpha; 
};

Color Graphic::getColor() 
{ 
	return Color(color->r, color->g, color->b); 
};

float Graphic::getRotation() 
{ 
	return rotation; 
};

float Graphic::getScaleH() 
{ 
	return scaleH; 
};

float Graphic::getScaleV() 
{ 
	return scaleV; 
};

int Graphic::getOriginX() 
{ 
	return originX; 
};

int Graphic::getOriginY() 
{ 
	return originY; 
};

int Graphic::getWidth() 
{ 
	return 0; 
};

int Graphic::getHeight() 
{ 
	return 0; 
};

