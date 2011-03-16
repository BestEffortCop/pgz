#pragma once
#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include "Color.h"

//! Clase virtual de la que heredarán todos los elementos gráficos
/*!
	Ofrece funciones de update (actualización con el transcurso de un tick 
	del juego) y render (momento en que se pinta por pantalla), así como 
	modificadores de color, transparencia, escala y rotación de la imagen.
*/
class Graphic {
	protected:
		//! Color que va a tener el gráfico.
		Color* color;
		//! Transparencia del gráfico.
		float alpha;
		//! Escala horizontal en la que se representará el gráfico.
		float scaleH;
		//! Escala vertical en la que se representará el gráfico.
		float scaleV;
		//! Valor del ángulo que rotará el gráfico.
		float rotation;
		//! Origen de rotación X
		int originX;
		//! Origen de rotación Y
		int originY;

	public:
	
	//! Construye el elemento gráfico
	Graphic() 
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
	virtual ~Graphic()
	{	
		delete color;
		color = NULL;
	}
		
	//! Realiza la actualización en cada paso del juego.
	virtual void update() {}
	
	//! Realiza el renderizado de la imagen en las coordenadas dadas de la ventana de juego.
	/*!
		\param x Coordenada x de reenderizado.
		\param y Coordenada y de reenderizado.
	*/
	virtual void render(int x, int y){}
		
	//! Tinta el gráfico del color dado
	/*!
		\param color Color con el que se tintará la imagen.
	*/
	virtual void setColor(Color color)
	{
		*this->color = color;
	}
	
	//! Cambia la transparencia del gráfico a un valor alpha.
	/*!
		\param alpha Valor de la nueva transparencia del gráfico.
	*/
	virtual void setAlpha(float alpha)
	{
		this->alpha = alpha;
	}
	
	//! Cambia la escala con que será renderizado el gráfico a un valor scale.
	/*!
		\param scale Valor de la nueva escala del gráfico.
	*/
	virtual void setScale(float scaleH, float scaleV)
	{
		this->scaleH = scaleH;
		this->scaleV = scaleV;
	}
	
	//! Rota la imagen un angulo rotation.
	/*!
		\param rotation Valor del ángulo que rotará el gráfico.
	*/
	virtual void setRotation(float rotation)
	{
		this->rotation = rotation;
	}

	//! Establece la posición horizontal del origen de rotación.
	/*!
		\param x Posición horizontal del origen
	*/
	virtual void setOriginX(int x)
	{
		this->originX = x;
	}

	//! Establece la posición vertical del origen de rotación.
	/*!
		\param x Posición vertical del origen
	*/
	virtual void setOriginY(int y)
	{
		this->originY = y;
	}

	/* Uncomented zone of weirdness */

	float getAlpha() { return alpha; };
	Color getColor() { return Color(color->r, color->g, color->b); };
	float getRotation() { return rotation; };
	float getScaleH() { return scaleH; };
	float getScaleV() { return scaleV; };
	int getOriginX() { return originX; };
	int getOriginY() { return originY; };
};

#endif
