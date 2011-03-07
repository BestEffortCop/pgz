#include "Game.h"

// Constructora y destructora

Game::Game(int screenW, int screenH, int bpp, int gameW, int gameH, int scale, int fps) 
{
	// Faltan datos para iniciar la aplicaci�n, debe cerrarse en cuanto avise, para lo cual neceista el engineManager
	bool mustClose = (screenW <= 0 || screenH <= 0 || bpp <= 0);

	// Se establece una configuraci�n b�sica para avisar del fallo
	if (mustClose)
	{
		screenW = 160; screenH = 144; bpp = 8;
	};

	// Si no se indica el ancho del juego, se supone el ancho de la ventana
	if (gameW <= 0) gameW = screenW;
	// Si no se indica el alto del juego, se supone el alto de la ventana
	if (gameH <= 0) gameH = screenH;

	// Si no se indica la escala del juego, suponemos escala real
	if (scale <= 0) scale = 1;

	// Si no se indican los fps, suponemos sin l�mite
	if (fps < 0) fps = 0;
	
	// Instancia el EngineManager con la configuraci�n solicitada
	engineManager = new EngineManager(screenW, screenH, bpp, fps, gameW, gameH, scale);

	// Si se debe cerrar la app por falta de datos, este es el momento
	if (mustClose)
		engineManager->log("Configuraci�n incorrecta para iniciar la aplicaci�n"), exit(2);
	else
		engineManager->log("Aplicaci�n arrancada correctamente, iniciando Subsistemas...");

	// Guarda un puntero a los subsistemas de sonido, gr�ficos, entrada y control de frames
	if ((soundEngine = engineManager->getSoundEngine()) == NULL) 
		engineManager->log("No se pudo iniciar el Subsistema de Audio, cerrando aplicaci�n."), exit(2);
	if ((gfxEngine = engineManager->getGfxEngine()) == NULL) 
		engineManager->log("No se pudo iniciar el Subsistema de Gr�ficos, cerrando aplicaci�n."), exit(2);
	if ((input = engineManager->getInput()) == NULL) 
		engineManager->log("No se pudo iniciar el Subsistema de Entrada, cerrando aplicaci�n."), exit(2);
	if ((frameControl = engineManager->getFrameControl()) == NULL) 
		engineManager->log("No se pudo iniciar el Subsistema de Timing, cerrando aplicaci�n."), exit(2);

	engineManager->log("Subsistemas iniciados correctamente.");
	
	// Guarda la configuraci�n del juego
	changeWorld = false;
	finished = false;
	gameWidth = gameW;
	gameHeight = gameH;
	screenWidth = screenW;
	screenHeight = screenH;
	theoricFps = fps;
	bpps = bpp;
	// de momento conservamos el ratio
	gameScaleWidth = scale;
	gameScaleHeight = scale;

	// Incialmente no guardamos estado del juego (world)
	gameState = NULL;
	nextState = NULL;
}

// Llama al evento asociado a la destrucci�n y elimina el engineManager instanciado
Game::~Game() 
{
	onDestroy();
	if (engineManager != NULL) 
	{ 
		delete engineManager; engineManager = NULL; 
	}
}

// M�todos de la clase

void Game::onStep() {};

void Game::step() 
{
	// Acciones a realizar si existe un GameState asignado al Game
	if (gameState != NULL) 
	{	
		// Actualiza el input
		input->checkInput();
		finished = input->getFinished();
		
		// se llama al evento onStep del juego
		onStep();

		// ejecuta Game::onStep (supongo que se refiere a GameState::onStep())
		gameState->onStep();
		
		// actualiza el gameState
		gameState->_update();

		// renderiza el gameState
		gameState->onRender();

		// pintamos sobre la pantalla de juego
		gfxEngine->display();
	}
	
	// Cambios en el GameState
	if (changeWorld)
		// Si hay un nuevo world v�lido
		if (gameState != NULL && nextState != NULL) 
		{
			// Invoca al evento de finalizaci�n del antiguo world
			gameState->onEnd();
			// Elimina el antiguo world
			delete gameState;
			// Actualiza al siguiente estado
			gameState = nextState;
			// No hay siguiente estado
			nextState = NULL;
			// Ya no hay que cambiar el world
			changeWorld = false;
			// Llama al evento de iniciaci�n del nuevo world
			gameState->onInit();
		}
	
	// Obtiene el valor de la duraci�n del �ltimo paso y actualiza el valor de los fps medios
	frameControl->update();
}

// Proporciona al Game el nuevo World al que se debe transitar
void Game::changeGameState(GameState* gState) {
	nextState = gState;
	changeWorld = true;
}

// Devuelve un puntero al world actual
GameState* Game::getGameState() { return gameState; }

// Devuelve un puntero al sistema de gr�ficos
GfxEngine* Game::getGfxEngine() { return gfxEngine; }

// Devuelve un puntero al sistema de sonido
SoundEngine* Game::getSoundEngine() { return soundEngine; }

// Devuelve un puntero al sistema de entrada
Input* Game::getInput() { return input; }

// Comprueba si la ejecuci�n debe finalizar
bool Game::isFinished() { return finished; }

// Devuelve un puntero a un struct con la configuraci�n del juego
GameConfig* Game::getGameConfig() 
{
	GameConfig* config = new GameConfig();
	config->gameWidth = this->gameWidth;
	config->gameHeight = this->gameHeight;
	config->screenWidth = this->screenWidth;
	config->screenHeight = this->screenHeight;
	config->theoricFps = this->theoricFps;
	config->bpps = this->bpps;
	config->gameScaleWidth = this->gameScaleWidth;
	config->gameScaleHeight = this->gameScaleHeight;
	
	return config;
}

// Determina si el juego debe o no finalizar
void Game::setFinished(bool finished) { this->finished = finished; }

void Game::onDestroy() {}