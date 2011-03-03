#include "Logger.h"

Logger* Logger::pinstance = NULL; // Inicializar el puntero

//Intenta crear una instancia con Path por defecto
Logger* Logger::Instance (){
  if (pinstance == NULL){  // Comprueba si es la primera llamada a Instance
    pinstance = new Logger(DEFAULT_PATH); // Creamos la instancia
	atexit(&DestroyInstance);
  }
  return pinstance; // Retornamos la dirección de la instancia
}

//Intenta crear una instancia con Path dada
Logger* Logger::Instance(const char* fname){
  if (pinstance == NULL){  // Comprueba si es la primera llamada a Instance
    pinstance = new Logger(fname); // Creamos la instancia
	atexit(&DestroyInstance);
  }
  return pinstance; // Retornamos la dirección de la instancia
}

//Construye la instancia  y avisa en el log
Logger::Logger(){
	time_t t = time(NULL);
	char* timestr = new char[T_SIZE];
	strftime(timestr,T_SIZE,T_FORMAT,localtime(&t));

	cout << "\nNew Session [" << timestr << "]============================\n" << endl;
	delete timestr;
}

//Construye la instancia y avisa en el log
//Si la ruta es inaccesible o similares, hace los log por consola
Logger::Logger(const char* fname){
	file.open(fname,ios::app | ios::out);
	time_t t = time(NULL);
    char* timestr = new char[T_SIZE];
	strftime(timestr,T_SIZE,T_FORMAT,localtime(&t));

	char* datestr = new char[D_SIZE];
	strftime(datestr,D_SIZE,D_FORMAT,localtime(&t));


	if ( file.is_open() )
		file << "\nNew Session [" << timestr << "]==========["<< datestr<< "]===========\n" << endl;

	else
        cout << "\nNew Session [" << timestr << "]==========["<< datestr<< "]===========\n" << endl;

	delete timestr;
	delete datestr;
}

//Destruye la instancia y avisa en el log
Logger::~Logger(){

	time_t t = time(NULL);
	char* timestr = new char[T_SIZE];
	strftime(timestr,T_SIZE,T_FORMAT,localtime(&t));

	char* datestr = new char[D_SIZE];
	strftime(datestr,D_SIZE,D_FORMAT,localtime(&t));

	if ( file.is_open() ){
		file << "\nEnd Session [" << timestr << "]==========["<< datestr<< "]===========\n" << endl;
		file.close();
	}
	else
		cout << "\nEnd Session [" << timestr << "]==========["<< datestr<< "]===========\n" << endl;

	delete timestr;
	delete datestr;
}

//Intenta destruir la instancia
void Logger::DestroyInstance(){
	if ( pinstance != NULL )
		delete pinstance;
}

//Escribe en el log el string solicitado
void Logger::log(string s){
	if ( file.is_open() )
	{
		file << ">" << s.c_str() << endl;
	}
	else
		cout << ">" << s.c_str() << endl;
}

//Devuelve la hora actual formateada
char* Logger::getTime(){
	time_t t = time(NULL);
	char* timestr = new char[T_SIZE];
	strftime(timestr,T_SIZE,T_FORMAT,localtime(&t));

	return timestr;
}

//Devuelve la fecha actual formateada
char* Logger::getDate(){
	time_t t = time(NULL);
	char* datestr = new char[D_SIZE];
	strftime(datestr,D_SIZE,D_FORMAT,localtime(&t));

	return datestr;
}
