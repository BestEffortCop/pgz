#pragma once
#ifndef __MASK_H__
#define __MASK_H__

#include <string>
#include <vector>

using namespace std;

//! Par de colisión que representa los tipos de colisión que se han producido.
struct CollisionPair {
	//! Tipo de colisión de la máscara A en la colisión.
	string a;
	//! Tipo de colisión de la máscara B en la colisión.
	string b;
};


//! Máscara de colisión abstracta capaz de comprobar colisiones con otras máscaras.
/*!
	Una máscara es un elemento abstracto que representa la estructura física 
	de una entidad y su delimitación a la hora de calcular su contacto con otras entidades.
	
	Contiene además una etiqueta editable que definirá qué tipo de colisión posee 
	la máscara, útil a la hora de calcular colisiones. Esta etiqueta será una cadena 
	de caracteres y deberá ser construída por el programador.
*/
class Mask
{
	public:
	
	//! Valor de la anchura de las dimensiones globales de la máscara de colisión.
	/*!
		Toda máscara hija estará envuelta en una máscara abstracta global.
		Debe ser colocada cuidadosamente, ya que dos máscaras no colisionan 
		si sus máscaras globales no están en contacto, aunque sus 
		correspondientes máscaras internas sí colisionen.
	*/
	int width;

	//! Valor de la altura de las dimensiones globales de la máscara de colisión.
	/*!
		Toda máscara hija estará envuelta en una máscara abstracta global.
		Debe ser colocada cuidadosamente, ya que dos máscaras no colisionan 
		si sus máscaras globales no están en contacto, aunque sus 
		correspondientes máscaras internas sí colisionen.
	*/
	int height;
	
	//! Coordenada x de posición de la máscara.
	int x;
	//! Coordenada y de posición de la máscara.
	int y;
	
	//! Tipo de colisión de la máscara.
	string type;
	
	//! Construye la máscara a partir de una anchura y altura globales dadas.
	/*!
		\param x Coordenada x de la máscara.
		\param y Coordenada y de la máscara.
		\param width Ancho de la máscara.
		\param height Alto de la máscara.
		\param type Tipo de colisión de la máscara.
	*/
	Mask(int x, int y, int width, int height, string type);
	
	//! Destructora
	~Mask();
		
	//! Comprueba si la máscara dada colisiona con otra máscara.
	/*!
		\param other Máscara con la que se comprueba la colisión.
		\return Lista de pares de colisión entre las 2 máscaras.
	*/
	virtual vector<CollisionPair>* collide(Mask* other);

	//! Invierte todos los pares de collisión contenidos en un vector de CollisionPair.
	/*!
		\param vect Vector de CollisionPair cuyos componentes queremos invertir.
	*/
	void flipAll (vector<CollisionPair>* vect);
};
	
#endif