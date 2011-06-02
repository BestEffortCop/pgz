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
#ifndef __INPUT_H__
#define __INPUT_H__

#include "SFML/Window.hpp"
#include <map>
#include <utility>
#include <string>

#include "Logger.h"

using namespace std;

//! Provee funciones para obtener el estado del teclado, el ratón y el gamepad.

/*!
	Se encarga de controlar las acciones realizadas en los distintos dispositivos de
	entrada y devolver toda la información relevante para que la pueda usar el intérprete. Ofrecerá
	métodos para comprobar el estado de las teclas (si están pulsadas, pulsándose durante
	un tiempo o soltadas), tanto de un joystick como de un teclado.
*/
class Input
{
	private:

		Logger* logger;

		/* *** Propio de Input *** */

		// Número de botones del mouse
		const static int numMouse = 3;

		// Número de teclas
		const static int numKeys = 61;

		// Máximo número de Joysticks
		const static int numJoys = 8;

		// Máximo número de botones por joystick
		const static int numJoyButtons = 12;


		// Estructura que mantiene los botones de un gamepad
		struct GamePad
		{
			// Botones
			bool button[numJoyButtons];
		};

		// Posición del mouse en la ventana
		int mouse_x, mouse_y;

		// Buffer con el estado del mouse en este paso
		bool mouseBuffer[numMouse];

		// Buffer con el estado del mouse el paso anterior
		bool oldMouseBuffer[numMouse];

		// Buffer con estado del teclado en este paso
		bool keyBuffer[numKeys];

		// Buffer con el estado del teclado el paso anterior
		bool oldKeyBuffer[numKeys];

		// Mapa para traducir nuestras teclas a las de la librería subyaciente.
		map<int,int>* keyTranslator;

		// Mapa de teclas con nombre asignado
		map<string, int>* keyNamesList;

		// Buffer con el estado de los joysticks
		GamePad joyBuffer[numJoys];

		// Buffer con el estado anterior de todos los joysticks
		GamePad oldJoyBuffer[numJoys];

		// Mapa de botones del joystick con nombre asignado
		map<string, pair<int,int> >* joyNamesList;

		// Se ha solicitado el cierre de la ventana?
		bool finished;

		// Prepara el traductor de teclas
		void mapKeys();

		/* *** Relacionado con el sistema *** */

		// Ventana del sistema
		sf::Window* window;

		// Sistema de entrada del sistema
		const sf::Input* input;

		// Procesa los eventos del sistema
		void processEvents();

	public:

		// Botones del mouse
		enum Mouse
		{
			Left, Right, Middle
		};

		// Lista de teclas
		enum Key
		{
			/* Direcciones */
			kUP,
			kLEFT,
			kDOWN,
			kRIGHT,

			/* Otras teclas */
			kRCTRL,
			kLCTRL,
			kRSHIFT,
			kLSHIFT,
			kRALT,
			kLALT,

			kESC,
			kENTER,
			kSPACE,
			kBACK,
			kMAYUS,
			kTAB,

			kF1,
			kF2,
			kF3,
			kF4,
			kF5,
			kF6,
			kF7,
			kF8,
			kF9,

			/* Teclado numérico */
			kN0,
			kN1,
			kN2,
			kN3,
			kN4,
			kN5,
			kN6,
			kN7,
			kN8,
			kN9,

			/* Letras */
			kA, kB, kC, kD, kE, kF, kG, kH, kI, kJ, kK, kL, kM, kN, kO, kP, kQ, kR, kS, kT, kU, kV, kW, kX, kY, kZ,

			/* Default key */
			kDefault
		};

	//! Construye el sistema de input
	/*!
		Preparara las estructuras necesarias para la gestión de entrada de datos por el usuario, dejando
		al método Input::init() la inicialización de la clase y librería.
	*/
	Input();

	//! Destructora
	~Input();

	//! Inicializa la clase Input
	/*! Necesita que se le indique la ventana creada para la aplicación
		\param window Ventana instanciada de la librería subyaciente
	*/
	bool init(sf::Window* window);

	//!Actualiza la información de todos los elementos de entrada
	/*!
		\return true si ha actualizado todo correctamente, false si algo ha fallado
	*/
	bool checkInput();

	/*********************************************************************\
	*	Tratamiento de teclas por defecto								  *
	\*********************************************************************/

	//! Comprueba si se ha pulsado una tecla del teclado
	/*!
		\param key Tecla a comprobar.
		\return True si se ha pulsado una tecla, falso en caso contrario.
	*/
	bool key(Key key);

	//! Comprueba si se está manteniendo pulsada una tecla del teclado.
	/*!
		\param key Tecla a comprobar.
		\return True si se está pulsando la tecla, falso en caso contrario.
	*/
	bool keyPressed(Key key);

	//! Comprueba si se ha soltado una tecla del teclado.
	/*!
		\param key Tecla a comprobar.
		\return True si se ha soltado la tecla, falso en caso contrario.

	*/
	bool keyReleased(Key key);

	/*********************************************************************\
	*	Tratamiento de teclas personalizadas							  *
	\*********************************************************************/

	//! Asigna un identificador personalizado a una tecla del sistema
	/*!#include <map>
		\param name Nombre de la tecla personalizada.
		\param key Tecla a personalizar.
	*/
	void keySet(string name, Key key);

	//! Permite recuperar la tecla del sistema asociada al identificador.
	/*!
		\param name Identificador de la tecla personalizada.
		\return Tecla del sistema asignada al identificador dado.
	*/
	Key getKey(string name);

	//! Comprueba si se está pulsando una tecla personalizada del teclado.
	/*!
		\param key Tecla a comprobar
		\return True si se está pulsando la tecla, falso en caso contrario.
	*/
	bool key(string key);

	//! Comprueba si se está manteniendo pulsada una tecla personalizada del teclado.
	/*!
		\param key Tecla a comprobar.
		\return True si se está pulsando la tecla, falso en caso contrario.
	*/
	bool keyPressed(string key);

	//! Comprueba si se ha soltado una tecla personalizada del teclado.
	/*!
		\param key Tecla a comprobar.
		\return True si se ha soltado la tecla, falso en caso contrario.

	*/
	bool keyReleased(string key);

	/*********************************************************************\
	*	Tratamiento de input por joystick por defecto					  *
	\*********************************************************************/

	//!Devuelve el valor de un eje del stick en un gamePad.
	/*!
		\param joy Identificador del gamepad.
		\param axis Identificador del eje.
		\return Valor del stick.
	*/
	float joyAxis(int joy, int axis);

	//!Comprueba si se está pulsando un botón determinado de un gamepad.
    /*!
		\param joy Identificador del gamepad.
		\param button Identificador del botón.
		\return True si se está pulsando el botón del gamepad, falso en caso contrario.
	*/
	bool joyButton(int joy, int button);

	//!Comprueba si se está manteniendo pulsado un botón determinado de un gamepad.
    /*!
		\param joy Identificador del gamepad.
		\param button Identificador del botón.
		\return True si se está manteniendo pulsado el botón del gamepad, falso en caso contrario.
	*/
	bool joyPressed(int joy, int button);

	//!Comprueba si se ha soltado un botón determinado de un gamepad.
    /*!
		\param joy Identificador del gamepad.
		\param button Identificador del botón.
		\return True si se ha soltado el botón del gamepad, falso en caso contrario.
	*/
    bool joyReleased(int joy, int button);

	/*********************************************************************\
	*	Tratamiento de input por joystick personalizado					  *
	\*********************************************************************/


	//! Asigna un identificador personalizado a un botón de un joystick del sistema
	/*!
		\param name Nombre del botón personalizado.
		\param joy Joystick al que pertenece el botón
		\param button Botón a personalizar.
	*/
	void joySet(string name, int joy, int button);

	//! Permite recuperar el botón del joystick asociado al identificador.
	/*!
		Nota! Es tarea del programador reservar memoria para el entero
		del joy antes de la llamada.
		\param name Identificador del botón personalizado.
		\param joy Joystick al que pertenece el botón (se devuelve por referencia)
		\return Botón del joystick asignado al identificador dado.
	*/
	int getJoy(string name, int* joy);


	//!Comprueba si se está pulsando un botón personalizado de un gamepad.
    /*!
		\param joy Identificador del gamepad.
		\param button Identificador personalizado del botón.
		\return True si se está pulsando el botón del gamepad, falso en caso contrario.
	*/
	bool joyButton(string button);

	//!Comprueba si se está manteniendo pulsado un botón personalizado de un gamepad.
    /*!
		\param joy Identificador del gamepad.
		\param button Identificador personalizado del botón.
		\return True si se está manteniendo pulsado el botón del gamepad, falso en caso contrario.
	*/
	bool joyPressed(string button);

	//!Comprueba si se ha soltado un botón personalizado de un gamepad.
    /*!
		\param joy Identificador del gamepad.
		\param button Identificador personalizado del botón.
		\return True si se ha soltado el botón del gamepad, falso en caso contrario.
	*/
    bool joyReleased(string button);


	/*********************************************************************\
	*	Eventos, Ventana y Ratón										  *
	\*********************************************************************/

	//!Comprueba si se ha pulsado el boton de cierre de la ventana.
    /*!
		\return Valor lógico, cierto si se ha pulsado y falso si no.
	*/
    bool getFinished();

	//! Devuelve la coordenada x de la posición del ratón relativa a la ventana.
    /*!
		\return Coordenada x del ratón.
	*/
	int getMouseX();

	//!Devuelve la coordenada y de la posición del ratón relativa a la ventana.
    /*!
		\return Coordenada y del ratón.
	*/
    int getMouseY();

	//! Comprueba si se ha pulsado un botón del ratón
	/*!
		\param button Botón a comprobar
		\return True si se está pulsando el botón, falso en caso contrario.
	*/
	bool mouseButton(Mouse button);

	//! Comprueba si se ha pulsado un botón del ratón
	/*!
		\param button Botón a comprobar
		\return True si se ha pulsado el botón, falso en caso contrario.
	*/
	bool mousePressed(Mouse button);

	//! Comprueba si se ha soltado un botón del ratón
	/*!
		\param button Botón a comprobar
		\return True si se ha soltado el botón, falso en caso contrario.
	*/
	bool mouseReleased(Mouse button);
};

#endif
