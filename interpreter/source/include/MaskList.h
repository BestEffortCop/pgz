#pragma once
#ifndef __MASK_LIST_H__
#define __MASK_LIST_H__

//! Lista de máscaras de colisión
/*!
	Se trata de un hijo de Mask, representando la máscara de colisión
	de un objeto en varias partes.
*/

class MaskList : public Mask
{
	public:
	
	//! Lista de las máscaras de colisión que contiene.
	list<Mask*>* masks;
	
	//! Construye la máscara a partir de una lista de máscaras y las dimensiones globales.
	/*!
		\param x Coordenada x de la máscara.
		\param y Coordenada y de la máscara.
		\param width Ancho global de la máscara.
		\param height Alto global de la máscara.
		\param type Tipo de colisión de la máscara.
		\param m Lista de máscaras ya creada.
	*/
	MaskList(int x, int y, int width, int height, string type, list<Mask*>* m);
	
	//! Destructora
	~MaskList();
		
	//! Comprueba si la máscara dada colisiona con otra máscara.
	/*!
		Hace uso del método de la clase padre para comprobar si cada
		una de las máscaras de su lista colisiona con la máscara other.
		\param other Máscara con la que se comprueba la colisión.
		\return Lista de pares de colisión entre las 2 máscaras.
	*/
	list<CollisionPair>* collide(Mask* other);
};
	
#endif