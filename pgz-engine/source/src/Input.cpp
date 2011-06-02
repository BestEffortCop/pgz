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

#include "Input.h"

/*	Tratamiento de teclas por defecto */
Input::Input()
{
	// Se obtiene el puntero al logger
	logger = Logger::Instance();

	// Se inicializa la lista de nombres de teclas
	keyNamesList = new map<string, int>();

	// Se prepara el traductor de teclas
	mapKeys();

	// Se inicializan los buffers de teclado
	for (int i = 0; i < numKeys; i++)
		keyBuffer[i] = false, oldKeyBuffer[i] = false;

	// Se inicializa la lista de nombres de botones de joys
	joyNamesList = new map<string, pair<int, int> >();

	// Se inicializan los buffers de joys
	for (unsigned int j = 0; j < numJoys; j++)
		// Para cada joystick, se inicializa el estado de todos sus botones a falso
		for (unsigned int jb = 0; jb < numJoyButtons; jb++)
			joyBuffer[j].button[jb] = false,
			oldJoyBuffer[j].button[jb] = false;

	// Todavía no se tiene la ventana
	window = NULL;

	// Ni se ha finalizado el juego
	finished = false;

	// Se preparan las variables de la posición del ratón
	mouse_x = 0; mouse_y = 0;
}

Input::~Input()
{
	// Se avisa
	logger->log("Se finaliza el Subsistema de Entrada.");

	// Se elimina el vector de teclas
	if (keyNamesList != NULL)
	{
		keyNamesList->clear();
		delete keyNamesList;
		keyNamesList = NULL;
	}

	// Se elimina el traductor del teclado
	if (keyTranslator != NULL)
	{
		keyTranslator->clear();
		delete keyTranslator;
		keyTranslator = NULL;
	}

	// Se elimina el traductor del gamepad
	if (joyNamesList != NULL)
	{
		joyNamesList->clear();
		delete joyNamesList;
		joyNamesList = NULL;
	}

	logger->dlog("\tFinalización efectuada correctamente.");

	//Logger::DestroyInstance();
}

bool Input::init(sf::Window* window)
{
	logger->log("Se inicializa el subsistema de entrada");
	// Se coge el puntero a la ventana del sistema
	this->window = window;

	// Se almacena el sf::Input del sistema por comodidad
	if (window != NULL)
		input = &(window->GetInput());
	else
		input = NULL;

	if (window == NULL)
	{
		logger->log("No se pudo inicializar el subsistema de entrada: La ventana de aplicación no existe");
		return false;
	};
	return true;
}

/* Procesa los eventos de SFML */
void Input::processEvents()
{
	// Se necesita una variable para procesar los eventos
	sf::Event Event;

	if (window != NULL)
		// Mientras queden eventos, se procesan
		while (window->PollEvent(Event))
		{
			// Aviso de que se quiere cerrar la ventana
			if (Event.Type == sf::Event::Closed)
				finished = true;
		}
}

bool Input::checkInput()
{
	// Se procesan los eventos de SFML
	processEvents();

	// Se actualiza la posición del mouse
	mouse_x = input->GetMouseX();
	mouse_y = input->GetMouseY();

	// El estado actual del ratón pasa a ser el antiguo
	// y se actualiza el estado actual
	for (int m = 0; m < numMouse; m++)
		oldMouseBuffer[m] = mouseBuffer[m],
		mouseBuffer[m] = input->IsMouseButtonDown((sf::Mouse::Button) m);

	// Se actualiza el estado del mouse

	// El estado actual del teclado pasa a ser el del antiguo paso
	for (int i = 0; i < numKeys; i++)
		oldKeyBuffer[i] = keyBuffer[i];

	// Se actualiza el estado del teclado
	// Para cada tecla de las nuestras
	for (int i = 0; i < numKeys; i++)
	{
		// Se busca la correspondiente en SFML con el traductor
		map<int, int>::iterator it = keyTranslator->find(i);
		// Si se ha encontrado
		if (it != keyTranslator->end())
			// Se coge su estado
			keyBuffer[i] = input->IsKeyDown((sf::Key::Code) it->second);
		else
			// Si no se ha encontrado, suponemos que nunca se pulsa
			keyBuffer[i] = false;
	}

	// Se actualiza el estado de todos los joysticks
	for (unsigned int j = 0; j < numJoys; j++)
	{
		// Para cada joystick, se copia el estado de todos sus botones y actualizamos al nuevo
		for (unsigned int jb = 0; jb < numJoyButtons; jb++)
		{
			// Se almacena el estado antiguo
			oldJoyBuffer[j].button[jb] = joyBuffer[j].button[jb];
			// Se coge el nuevo estado
			joyBuffer[j].button[jb] = input->IsJoystickButtonDown(j, jb);
		}
	}

	// Todo ha ido bien :)
	return true;
}

/* Realiza la conversión de teclas-teclas SFML */
void Input::mapKeys()
{
	// Traducción de la lista de teclas de SFML a las nuestras

	keyTranslator = new map<int,int>();
	keyTranslator->insert(make_pair(kZ, sf::Key::Z));
	keyTranslator->insert(make_pair(kX, sf::Key::X));
	keyTranslator->insert(make_pair(kLEFT, sf::Key::Left));
	keyTranslator->insert(make_pair(kRIGHT, sf::Key::Right));
	keyTranslator->insert(make_pair(kDOWN, sf::Key::Down));
	keyTranslator->insert(make_pair(kUP, sf::Key::Up));

	keyTranslator->insert(make_pair(kRCTRL, sf::Key::RControl));
	keyTranslator->insert(make_pair(kRSHIFT, sf::Key::RShift));
	keyTranslator->insert(make_pair(kLCTRL, sf::Key::LControl));
	keyTranslator->insert(make_pair(kLSHIFT, sf::Key::LShift));
	keyTranslator->insert(make_pair(kRALT, sf::Key::RAlt));
	keyTranslator->insert(make_pair(kLALT, sf::Key::LAlt));
	keyTranslator->insert(make_pair(kESC, sf::Key::Escape));
	keyTranslator->insert(make_pair(kENTER, sf::Key::Return));
	keyTranslator->insert(make_pair(kSPACE, sf::Key::Space));
	keyTranslator->insert(make_pair(kBACK, sf::Key::Back));

	/* SFML no proporciona el BloqMayus */
	//keyTranslator->insert(make_pair(kMAYUS, sf::Key::Mayus));

	keyTranslator->insert(make_pair(kTAB, sf::Key::Tab));

	keyTranslator->insert(make_pair(kF1, sf::Key::F1));
	keyTranslator->insert(make_pair(kF2, sf::Key::F2));
	keyTranslator->insert(make_pair(kF3, sf::Key::F3));
	keyTranslator->insert(make_pair(kF4, sf::Key::F4));
	keyTranslator->insert(make_pair(kF5, sf::Key::F5));
	keyTranslator->insert(make_pair(kF6, sf::Key::F6));
	keyTranslator->insert(make_pair(kF7, sf::Key::F7));
	keyTranslator->insert(make_pair(kF8, sf::Key::F8));
	keyTranslator->insert(make_pair(kF9, sf::Key::F9));

	keyTranslator->insert(make_pair(kN0, sf::Key::Num0));
	keyTranslator->insert(make_pair(kN1, sf::Key::Num1));
	keyTranslator->insert(make_pair(kN2, sf::Key::Num2));
	keyTranslator->insert(make_pair(kN3, sf::Key::Num3));
	keyTranslator->insert(make_pair(kN4, sf::Key::Num4));
	keyTranslator->insert(make_pair(kN5, sf::Key::Num5));
	keyTranslator->insert(make_pair(kN6, sf::Key::Num6));
	keyTranslator->insert(make_pair(kN7, sf::Key::Num7));
	keyTranslator->insert(make_pair(kN8, sf::Key::Num8));
	keyTranslator->insert(make_pair(kN9, sf::Key::Num9));

	keyTranslator->insert(make_pair(kA, sf::Key::A));
	keyTranslator->insert(make_pair(kB, sf::Key::B));
	keyTranslator->insert(make_pair(kC, sf::Key::C));
	keyTranslator->insert(make_pair(kD, sf::Key::D));
	keyTranslator->insert(make_pair(kE, sf::Key::E));
	keyTranslator->insert(make_pair(kF, sf::Key::F));
	keyTranslator->insert(make_pair(kG, sf::Key::G));
	keyTranslator->insert(make_pair(kH, sf::Key::H));
	keyTranslator->insert(make_pair(kI, sf::Key::I));
	keyTranslator->insert(make_pair(kJ, sf::Key::J));
	keyTranslator->insert(make_pair(kK, sf::Key::K));
	keyTranslator->insert(make_pair(kL, sf::Key::L));
	keyTranslator->insert(make_pair(kM, sf::Key::M));
	keyTranslator->insert(make_pair(kN, sf::Key::N));
	keyTranslator->insert(make_pair(kO, sf::Key::O));
	keyTranslator->insert(make_pair(kP, sf::Key::P));
	keyTranslator->insert(make_pair(kQ, sf::Key::Q));
	keyTranslator->insert(make_pair(kR, sf::Key::R));
	keyTranslator->insert(make_pair(kS, sf::Key::S));
	keyTranslator->insert(make_pair(kT, sf::Key::T));
	keyTranslator->insert(make_pair(kU, sf::Key::U));
	keyTranslator->insert(make_pair(kV, sf::Key::V));
	keyTranslator->insert(make_pair(kW, sf::Key::W));
	keyTranslator->insert(make_pair(kX, sf::Key::X));
	keyTranslator->insert(make_pair(kY, sf::Key::Y));
	keyTranslator->insert(make_pair(kZ, sf::Key::Z));
};

bool Input::key(Key key)
{
	// Una tecla está pulsada en el estado actual si está pulsada en el estado actual
	return (keyBuffer[key]);
}

bool Input::keyPressed(Key key)
{
	// Una tecla se ha pulsado en el estado actual si en el paso anterior no se había pulsado y en el actual sí
	return ((!oldKeyBuffer[key]) && (keyBuffer[key]));
}

bool Input::keyReleased(Key key)
{
	// Una tecla se ha soltado en el estado actual si en el paso anterior estaba pulsada y en el actual no
	return ((oldKeyBuffer[key]) && (!keyBuffer[key]));
}

/*	Tratamiento de teclas personalizadas */

/*Inserta una tecla personalizada*/
void Input::keySet(string name, Key key)
{
	// Se busca la acción entre las existentes
	map<string, int>::iterator it;
	it = keyNamesList->find(name);
	// Si no está, se añade
	if (it == keyNamesList->end())
		keyNamesList->insert(make_pair(name, key));
	else
	{
		// Si está, se reemplaza
		keyNamesList->erase(it);
		keyNamesList->insert(make_pair(name, key));
	}
}

/*Devuelve una tecla personalizada*/
Input::Key Input::getKey(string name)
{
	// Se busca el nombre en la lista
	if (keyNamesList->find(name) != keyNamesList->end())
		// Si se encuentra, se traduce y se devuelve
		return (Key) keyNamesList->find(name)->second;
	// Si no, se devuelve la tecla por defecto
	else return kDefault;
}

/*Comprueba si se ha pulsado una tecla personalizada*/
bool Input::key(string key)
{
	// Se busca el nombre en la lista
	if (keyNamesList->find(key) != keyNamesList->end())
		// Si se encuentra, se comprueba su estado y se devuelve
		return this->key((Key) keyNamesList->find(key)->second);
	// Si no, se supone que no está pulsada
	else return false;
}

/*Comprueba si se está manteniendo pulsada una tecla personalizada*/
bool Input::keyPressed(string key)
{
	// Se busca el nombre en la lista
	if (keyNamesList->find(key) != keyNamesList->end())
		// Si se encuentra, se comprueba su estado y se devuelve
		return this->keyPressed((Key) keyNamesList->find(key)->second);
	// Si no, se supone que no está pulsada
	else return false;
}

/*Comprueba si se ha soltado una tecla personalizada*/
bool Input::keyReleased(string key)
{
	// Se busca el nombre en la lista
	if (keyNamesList->find(key) != keyNamesList->end())
		// Si se encuentra, se comprueba su estado y se devuelve
		return this->keyReleased((Key) keyNamesList->find(key)->second);
	// Si no, se supone que no está pulsada
	else return false;
}

/*	Joystick */

/*	Tratamiento de input por joystick por defecto */
float Input::joyAxis(int joy, int axis)
{
	// Se devuelve el estado del eje del joystick en el rango -1 ~ 1
	return (float) input->GetJoystickAxis(joy, (sf::Joy::Axis) axis)/100;
}

bool Input::joyButton(int joy, int button)
{
	// El botón del joy está pulsado actualmente si está pulsado actualmente
	return joyBuffer[joy].button[button];
}

bool Input::joyPressed(int joy, int button)
{
	// El botón del joystick se ha pulsado en el paso actual si
	// no estaba pulsado en el paso anterior pero sí en este
	return (joyBuffer[joy].button[button] &&
			!oldJoyBuffer[joy].button[button]);
}

bool Input::joyReleased(int joy, int button)
{
	// El botón del joystick se ha soltado en el paso actual si
	// estaba pulsado en el paso anterior pero no en este
	return (!joyBuffer[joy].button[button] &&
			oldJoyBuffer[joy].button[button]);
}

/*	Tratamiento de input por joystick personalizadas */

void Input::joySet(string name, int joy, int button)
{
	// Se busca la acción entre las existentes
	map<string, pair<int, int> >::iterator it;
	it = joyNamesList->find(name);
	// Si no está, se añade
	if (it == joyNamesList->end())
		joyNamesList->insert(make_pair(name, make_pair(joy, button)));
	else
	{
		// Si está, se reemplaza
		joyNamesList->erase(it);
		joyNamesList->insert(make_pair(name, make_pair(joy, button)));
	}
}

int Input::getJoy(string name, int* joy)
{
	// Se busca el identificador
	map<string, pair<int, int> >::iterator it;
	it = joyNamesList->find(name);
	// Si se encuentra
	if (it != joyNamesList->end())
	{
		// Se devuelve el joystick por referencia
		*joy = it->second.first;
		// Y el botón por valor
		return it->second.second;
	}
	else
	{
		// Si no se encuentra, devolvemos bogus
		*joy = -1;
		return -1;
	}
}

bool Input::joyButton(string button)
{
	// Se busca el identificador
	map<string, pair<int, int> >::iterator it;
	it = joyNamesList->find(button);
	// Si se encuentra
	if (it != joyNamesList->end())
	{
		// Se comprueba el estado y se devuelve
		return joyButton(it->second.first, it->second.second);
	}
	// Si no, se supone que no está pulsado
	else return false;
}

bool Input::joyPressed(string button)
{
	// Se busca el identificador
	map<string, pair<int, int> >::iterator it;
	it = joyNamesList->find(button);
	// Si se encuentra
	if (it != joyNamesList->end())
	{
		// Se comprueba el estado y se devuelve
		return joyPressed(it->second.first, it->second.second);
	}
	// Si no, se supone que no se ha pulsado
	else return false;
}

bool Input::joyReleased(string button)
{
	// Se busca el identificador
	map<string, pair<int, int> >::iterator it;
	it = joyNamesList->find(button);
	// Si se encuentra
	if (it != joyNamesList->end())
	{
		// Se comprueba el estado y se devuelve
		return joyReleased(it->second.first, it->second.second);
	}
	// Si no, suponemos que no está pulsado
	else return false;
}

/*	Demás teclas */

/*Comprueba si se ha pulsado el boton de cierre de la ventana*/
bool Input::getFinished()
{
	return finished;
}

/*Devuelve la coordenada x de la posición del ratón relativa a la ventana*/
int Input::getMouseX()
{
	return mouse_x;
}

/*Devuelve la coordenada y de la posición del ratón relativa a la ventana*/
int Input::getMouseY()
{
	return mouse_y;
}

bool Input::mouseButton(Mouse button)
{
	// Una tecla está pulsada en el estado actual si está pulsada en el estado actual
	return (mouseBuffer[button]);
}

bool Input::mousePressed(Mouse button)
{
	// Una tecla se ha pulsado en el estado actual si en el paso anterior no se había pulsado y en el actual sí
	return ((!oldMouseBuffer[button]) && (mouseBuffer[button]));
}

bool Input::mouseReleased(Mouse button)
{
	// Una tecla se ha soltado en el estado actual si en el paso anterior estaba pulsada y en el actual no
	return ((oldMouseBuffer[button]) && (!mouseBuffer[button]));
}