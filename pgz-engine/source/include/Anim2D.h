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

#pragma once

#ifndef __ANIM2D_H__
#define __ANIM2D_H__

#include "Logger.h"
#include "Anim.h"
#include <vector>

using namespace std;

//! Miembro de la familia de Anim que representa una animación en dos dimensiones.
/*!
	Almacena los frames o marcos de imagen en que consiste la animación, 
	la velocidad de reproducción y si debe repetirse al terminar.
	
	Cada frame se representa como un entero que indica la posición del frame
	en la imagen bidimensional ligada a la animación.
*/
class Anim2D : public Anim 
{
	private:
		//! Atributos de la clase Anim2D.
		/*!
			\param nombre de la animación en curso.
			\param frameCount contará el número de frames que han pasado.
			\param framesPerStep contiene la información del número de steps que se ejecutará cada frame.
			\param frameList contiene la lista de frames que se van a utilizar para la animación dada.
			\param loop indica si la animación ha de repetirse o no.
		*/
		int frameCount;
		int framesPerStep;
		vector<int>* frameList;
		bool loop;
		Logger *logger;
		
	public:

		//! Construye la Anim2D
		/*!
			\param name Nombre de la animación.
			\param frames Vector de frames de la animación
			\param framesPerStep Pasos del juego que dura cada frame
			\param loop Indica si la animación ha de repetirse o no
		*/
		Anim2D(string name, vector<int>* frames, int framesPerStep, bool loop);

		//! Destruye la animación
		~Anim2D();
		
		/* Getters & Setters */
		
		//! Obtiene el número de frames por step de la animación
		/*!
			\return Número de pasos del juego que dura cada frame
		*/
		int getFramesPerStep();

		//! Establece el número de frames por step de la animación
		/*!
			\param framesPerStep Pasos del juego que dura cada frame
		*/
		void setFramesPerStep(int framesPerStep);
		
		//! Obtiene si la animación se ha de repetir
		/*!
			\return True si la animación se repite
		*/
		bool getLoop();

		//! Establece si la animación ha de repetirse
		/*!
			\param loop True si debe repetirse
		*/
		void setLoop(bool loop);
		
		//! Obtiene el nombre de la animación
		/*!
			\return Nombre de la animación
		*/
		string getName();
		
		//! Obtiene el número de frames de la animación
		/*!
			\return Número de frames
		*/
		int getFrameCount();

		//! Obtiene el vector con los frames de la animación
		/*!
			\return Vector de frames
		*/
		vector<int>* getFrameList();
};

#endif