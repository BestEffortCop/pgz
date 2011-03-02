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
		fstream file;

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
		void log(string s);

		//! Devuelve la hora actual en formato de texto
		char* getTime();

		//! Devuelve la fecha actual en formato de texto
		char* getDate();
};

#endif // _LOGGER_H_
