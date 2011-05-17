#pragma once
#ifndef __MASK_CIRCLE_H__
#define __MASK_CIRCLE_H__

#include "Mask.h"
#include "MaskBox.h"
#include "MaskList.h"
#include "SolidGrid.h"
#include <math.h>

//! Máscara de colisión única de forma circular.
/*!
	Se trata de un hijo de Mask, representando la máscara de colisión
	de un objeto de forma circular.
*/

class MaskCircle : public Mask
{
	public:

	//! Radio de la máscara circular.
	float radius;

	//! Construye la máscara a partir de la posición y radio del círculo y las dimensiones globales.
	/*!
        La posición (x,y) y desplazamiento (xoffset,yoffset) de la máscara servirán para representar
        la posición de la esquina superior izquierda del cuadrado que envuelve al círculo.
		\param x Coordenada x origen de la máscara.
		\param y Coordenada y origen de la máscara.
		\param r Radio de la máscara circular.
        \param type Tipo de colisión de la máscara.
		\param xoffset Coordenada x de desplazamiento la máscara.
		\param yoffset Coordenada y de desplazamiento la máscara.
	*/
	MaskCircle(int x, int y, float r, string type, int xoffset = 0, int yoffset = 0);

	//! Destructora
	virtual ~MaskCircle();

	//! Comprueba si la máscara circular dada colisiona con otra máscara.
	/*!
		\param other Máscara con la que se comprueba la colisión.
		\return Lista de pares de colisión entre las 2 máscaras.
	*/
	vector<CollisionPair>* collide(Mask* other);

	private:

	//! Calcula la distancia de un punto a otro punto.
	/*!
		\param x1 Cordenada x del primer punto.
		\param x2 Cordenada x del segundo punto.
		\param y1 Cordenada y del primer punto.
		\param y2 Cordenada y del segundo punto.
		\return Float con el valor de la distancia entre los puntos.
	*/
	float getDistance (int x1, int x2, int y1, int y2);

	//! Calcula si la circunferencia colisiona con los lados perpendiculares de un rectángulo.
	/*!
		\param bx Cordenada x del rectángulo.
		\param by Cordenada y del rectángulo.
		\param bwidth Ancho del rectángulo.
		\param bheigth Alto del rectángulo.
		\return bool true si hubo colisión, false si no hubo.
	*/
	bool checkBoxCollision(int bx, int by, int bwidth, int bheigth);
};

#endif
