#pragma once
#ifndef __INPUT_H__
#define __INPUT_H__

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

	public:
	
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
	/*!
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
		\param button Botón a personalizar.
	*/
	void joySet(string name, int button);
	
	//! Permite recuperar el botón del joystick asociado al identificador.
	/*!
		\param name Identificador del botón personalizado.
		\return Botón del joystick asignado al identificador dado.
	*/
	int getJoy(string name);
	
	
	//!Comprueba si se está pulsando un botón personalizado de un gamepad.
    /*!    
		\param joy Identificador del gamepad.
		\param button Identificador personalizado del botón.
		\return True si se está pulsando el botón del gamepad, falso en caso contrario.
	*/
	bool joyButton(int joy, string button);
     
	//!Comprueba si se está manteniendo pulsado un botón personalizado de un gamepad.
    /*!    
		\param joy Identificador del gamepad.
		\param button Identificador personalizado del botón.
		\return True si se está manteniendo pulsado el botón del gamepad, falso en caso contrario.
	*/
	bool joyPressed(int joy, string button);

	//!Comprueba si se ha soltado un botón personalizado de un gamepad.
    /*!    
		\param joy Identificador del gamepad.
		\param button Identificador personalizado del botón.
		\return True si se ha soltado el botón del gamepad, falso en caso contrario.
	*/
    bool joyReleased(int joy, string button);
	
	
	/*********************************************************************\
	*	Demás teclas													  *
	\*********************************************************************/
    
	//!Coprueba si se ha pulsado el boton de cierre de la ventana.
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
}

#endif