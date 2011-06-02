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

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define FULL_T_FORMAT "%d/%m/%Y %H:%M"
#define T_FORMAT "%H:%M"
#define D_FORMAT "%d/%m/%Y"

#define FULL_T_SIZE 17
#define T_SIZE 6
#define D_SIZE 11

#define DEFAULT_PATH ".\\log.txt"

using namespace std;

//!Clase encargada de escribir en archivo información relevante que pueda necesitar el programador
/*!
	Su función es la de encapsular los posibles errores o trazas del programa como ayuda para
	el programador, pero puede ser usado para otros fines.
*/

class Logger {
	private:
		static Logger* pinstance;

		// Indica si se deben escribir los mensajes de depuración
		bool debugMode;

		// Archivo sobre el que escribir
		FILE* file;

        //! Crea flog en una ruta por defecto y lo prepara para escribir en el
		Logger();

		//! Crea flog en la ruta indicada y lo prepara para escribir en el
		/*!
			\param fname contiene la ruta en la que se creará el archivo de log
		*/
		Logger(const char* fname);

		//! Destructora, escribe un final para el archivo y lo cierra
		~Logger();


	public:

		//! Intenta crear instancia del flog en una ruta por defecto
		static Logger* Instance();

        //! Intenta crear instancia del flog en la ruta indicada
        /*!
			\param fname contiene la ruta en la que se creará el archivo de log
		*/
		static Logger* Instance(const char* fname);

		//! Intenta destruir la instancia del log
		static void DestroyInstance();

		//! Escribe el string en el archivo de log que esté abierto
		/*!
			\param s es la información que escribirá
		*/
		void log(const char* c);

		//! Escribe el mensaje de debug en el archivo de log que esté abierto
		/*!
			Sólo se escribirá el mensaje si el modo debug está activado
			\param msg Mensaje de debug a escribir
		*/
		void dlog(const char* msg);

		//! Indica si el Logger está trabajando en modo debug
		/*! \return True si está trabajando en modo debug */
		bool getDebugMode();

		//! Establece si el Logger trabajará en modo debug
		/*! \param on True para activar el modo debug */
		void setDebugMode(bool on = true);

		//! Devuelve la hora actual en formato de texto
		char* getTime();

		//! Devuelve la fecha actual en formato de texto
		char* getDate();
};

#endif // _LOGGER_H_
