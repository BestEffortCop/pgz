#include "FrameControl.h"

// Constructora y destructora

// Simplemente guarda el valor de fpsLimit
// Si fpsLimit < 0 => fpsLimit = 0 (sin límite)
FrameControl::FrameControl(int fpsL) 
{
	logger = Logger::Instance();

	if (fpsL < 0) 
		fpsLimit = 0;
	else 
		fpsLimit = fpsL;

	// Inicialmente, fps = 0
	fps = 0;

	window = NULL;
}

// La destructora no necesita liberar nada (window lo libera EngineManager)
FrameControl::~FrameControl() 
{
	logger->log("Se finaliza el Subsistema de Temporización.");
	logger->dlog("\tFinalización efectuada correctamente.");
}

// Métodos de la clase

// Inicializa el sistema de control de frames
bool FrameControl::init(sf::Window* window, bool reboot) 
{
	if (!reboot)
		logger->log("Se inicializa el subsistema de temporización");

	// Comprueba que window ha sido instanciado previamente
	if (window != NULL)
	{
		// Almacena la dirección del objeto window
		this->window = window;
		// fpsLimit es el valor con el que se invocó a la constructora
		window->SetFramerateLimit(fpsLimit);

		// Inicializamos el puntero y el contador de la cola de frames
		n_frames = 0;
		last_frame = -1;
		return true;
	}

	logger->log("No se pudo inicializar el subsistema de temporización: La ventana de aplicación no existe");
	return false;
}

// Cambia el límite de frames por segundo
void FrameControl::setFPSLimit(int fpsL) 
{
	// Si el control de frames no ha sido inicializado no hace nada
	if (window != NULL) 
	{
		logger->dlog(string("Limitación de Frames por Segundo cambiada").c_str());
		// Almacena el nuevo valor de fpsLimit
		if (fpsL < 0) 
			fpsLimit = 0;
		else 
			fpsLimit = fpsL;

		// Inicia de nuevo el control de frames
		init(window, true);
	}
	else
		logger->log("FrameControl::setFPSLimit - Fallo al establecer el límite de FPS: La ventana de aplicación no existe");
}

// Devuelve el valor de fpsLimit
int FrameControl::getFPSLimit() {
	return fpsLimit;
}

// Obtiene el valor medio de los fps a los que "corre" (yeah!) la aplicación
int FrameControl::getFramesPerSecond() {
	return fps;
}

// Devuelve la duración del último frame
int FrameControl::getDelay() {
	// Comprueba que el control de frames ha sido inicializado correctamente
	if (window == NULL) 
		return 0;
	else 
		return ((int) window->GetFrameTime());
}

// Obtiene el valor de la duración del frame en cada paso del juego
// y actualiza el valor de la media de fps en consecuencia
// Debe llamarse en cada paso del juego
void FrameControl::update() {
	// Si no ha sido inicializado FrameControl no hace nada

	// OLD VERSION!
	/*if (window != NULL) {
		// Comprueba cuánto duró el último paso de juego
		float new_delay = (float) getDelay();

		// Si fps = 0 => No había valor medio de fps previo => fps = 1/getDelay
		if (fps == 0)
			fps = (int) (1.0/new_delay);
		// Si no, devuelve la media entre el valor medio acumulado y el nuevo valor
		else
			fps = (int) ((((float) fps) + (1.0/new_delay))/2.0);
	}*/

	// NEW VERSION!
	if (window != NULL) {
		// Obtenemos el valor del retardo del último frame
		float new_delay = (float) getDelay();
		// Añadimos uno al contador de frames totales (hasta un máximo de 10)
		n_frames = min(n_frames + 1, 10);
		// Avanzamos el puntero una posición
		last_frame = (last_frame + 1) % 10;
		// Guardamos el valor del último frame en la posición que nos indica el puntero
		frame_time[last_frame] = new_delay;
		// Hacemos la media de las duraciones de frame que tenemos
		float sum_frame = 0;
		for (int i = 0; i < n_frames; i++)
			sum_frame += frame_time[i];

		float sum_frame_avg = sum_frame / n_frames;

		// Los fps medios serán la inversa de la media
		fps = (int) (1.0 / sum_frame_avg);
	}
}