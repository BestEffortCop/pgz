#pragma once
#ifndef __MASK_CIRCLE_H__
#define __MASK_CIRCLE_H__

//! Máscara de colisión única de forma circular.
/*!
	Se trata de un hijo de Mask, representando la máscara de colisión
	de un objeto de forma circular.
*/

class MaskCircle : public Mask
{
	public:
	
	//! Coordenada x del centro de la máscara circular.
	int xcenter;
	//! Coordenada y del centro de la máscara circular.
	int ycenter;
	
	//! Radio de la máscara circular.
	float ratio;
	
	//! Construye la máscara a partir del centro y radio del círculo y las dimensiones globales.
	/*!
		\param x Coordenada x de la máscara.
		\param y Coordenada y de la máscara.
		\param width Ancho global de la máscara.
		\param height Alto global de la máscara.
		\param type Tipo de colisión de la máscara.
		\param xc Coordenada x del centro de la máscara circular.
		\param yc Coordenada y del centro de la máscara circular.
		\param r Radio de la máscara circular.
	*/
	MaskCircle(int x, int y, int width, int height, string type, int xc, int yc, float r);
	
	//! Destructora
	~MaskCircle();
		
	//! Comprueba si la máscara circular dada colisiona con otra máscara.
	/*!
		\param other Máscara con la que se comprueba la colisión.
		\return Lista de pares de colisión entre las 2 máscaras.
	*/
	list<CollisionPair>* collide(Mask* other);
};
	
#endif