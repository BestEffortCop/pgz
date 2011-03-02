#pragma once
#ifndef __MASK_BOX_H__
#define __MASK_BOX_H__

#include <string>
#include "MaskCircle.h"
#include "MaskList.h"
#include "SolidGrid.h"

using namespace std;

//! Máscara de colisión única de forma rectangular.
/*!
	Se trata de un hijo de Mask, representando la máscara de colisión
	de un objeto de forma rectangular.
*/

class MaskBox : public Mask
{
	public:
	
	//! Construye la máscara a partir de las dimensiones globales.
	/*!
		Las dimensiones de la máscara rectangular serán las globales.
		\param x Coordenada x de la máscara.
		\param y Coordenada y de la máscara.
		\param width Ancho global de la máscara.
		\param height Alto global de la máscara.
		\param type Tipo de colisión de la máscara.
	*/
	MaskBox(int x, int y, int width, int height, string type);
	
	//! Destructora
	~MaskBox();
		
	//! Comprueba si la máscara rectangular dada colisiona con otra máscara.
	/*!
		\param other Máscara con la que se comprueba la colisión.
		\return Lista de pares de colisión entre las 2 máscaras.
	*/
	vector<CollisionPair>* collide(Mask* other);
};
	
#endif