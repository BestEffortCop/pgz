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

#include "Logger.h"

Logger* Logger::pinstance = NULL; // Inicializar el puntero

//Intenta crear una instancia con Path por defecto
Logger* Logger::Instance ()
{
  if (pinstance == NULL)
  {  // Comprueba si es la primera llamada a Instance
    pinstance = new Logger(DEFAULT_PATH); // Creamos la instancia
	//atexit(&DestroyInstance);
  }
  return pinstance; // Retornamos la dirección de la instancia
}

//Intenta crear una instancia con Path dada
Logger* Logger::Instance(const char* fname)
{
  if (pinstance == NULL)
  {  // Comprueba si es la primera llamada a Instance
    pinstance = new Logger(fname); // Creamos la instancia
	atexit(&DestroyInstance);
  }
  return pinstance; // Retornamos la dirección de la instancia
}

//Construye la instancia  y avisa en el log
Logger::Logger()
{
	debugMode = true;

	char* timestr = getTime();
	char* datestr = getDate();
	file = fopen(DEFAULT_PATH , "w");

	fprintf(file, "New Session [%s . %s]===============\n\n", datestr, timestr);
	delete timestr;
	delete datestr;
}

//Construye la instancia y avisa en el log
//Si la ruta es inaccesible o similares, hace los log por consola
Logger::Logger(const char* fname)
{
	char* timestr = getTime();
	char* datestr = getDate();

	debugMode = true;

	file = fopen(fname , "w");

	fprintf(file, "New Session [%s . %s]===============\n\n", datestr, timestr);
	delete timestr;
	delete datestr;
}

//Destruye la instancia y avisa en el log
Logger::~Logger()
{
	char* timestr = getTime();

	fprintf(file, "\nEnd Session [%s]============================\n", timestr);
	fclose(file);

	delete timestr;
}

//Intenta destruir la instancia
void Logger::DestroyInstance()
{
	if ( pinstance != NULL )
		delete pinstance, pinstance = NULL;
}

//Escribe en el log el string solicitado
void Logger::log(const char* s)
{
	char* timestr = getTime();

	fprintf(file, "> [%s] %s \n", timestr, s);
	
	delete timestr;
}

//Escribe en el log el mensaje de debug solicitado
void Logger::dlog(const char* msg)
{
	if (debugMode)
	{
		char* timestr = getTime();
		fprintf(file, "> [%s] [DEBUG] %s \n", timestr, msg);
		delete timestr;
	}
}

void Logger::setDebugMode(bool on)
{
	debugMode = on;
};

bool Logger::getDebugMode()
{
	return debugMode;
};

//Devuelve la hora actual formateada
char* Logger::getTime()
{
	time_t t = time(NULL);
	char* timestr = new char[T_SIZE];
	strftime(timestr,T_SIZE,T_FORMAT,localtime(&t));

	return timestr;
}

//Devuelve la fecha actual formateada
char* Logger::getDate()
{
	time_t t = time(NULL);
	char* datestr = new char[D_SIZE];
	strftime(datestr,D_SIZE,D_FORMAT,localtime(&t));

	return datestr;
}
