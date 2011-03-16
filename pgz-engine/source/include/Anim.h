#pragma once

#ifndef __ANIM_H__
#define __ANIM_H__

#include <string>
using namespace std;

//! Anim es el elemento de animación de mayor alto nivel.
/*!
	De él derivarán los distintos tipos de animaciones con que pueda trabajar el programador.
*/
class Anim {
	protected:
		//! Atributo de la clase anim.
		/*!
			\param _name nombre de la animación.
		*/
		string name;
	public:

		//! Construye una animación indicando su nombre
		/*! \param name Nombre de la animación */
		Anim(string name){};
		//! Destruye la animación
		virtual ~Anim(){};
		
		//! Obtiene el nombre de la animación
		/*!
			\return Nombre de la animación
		*/
		virtual string getName(){return  NULL;};
};

#endif