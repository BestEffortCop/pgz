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
		//! Escala en la que se representará el gráfico.
		float scale;
		//! Valor del ángulo que rotará el gráfico.
		float rotation;

	public:
	
	//! Construye el elemento gráfico
	Graphic() 
	{
		color = new Color(255,255,255);
		alpha = 1;
		scale = 1;
		rotation = 0;
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
	virtual void setScale(float scale)
	{
		this->scale = scale;
	}
	
	//! Rota la imagen un angulo rotation.
	/*!
		\param rotation Valor del ángulo que rotará el gráfico.
	*/
	virtual void setRotation(float rotation)
	{
		this->rotation = rotation;
	}
		
};

#endif
