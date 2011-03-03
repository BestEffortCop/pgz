#include "Game.h"

// Constructora y destructora

Game::Game(int screenW, int screenH, int bpp, int gameW, int gameH, int scale, int fps) {
	if (screenW <= 0 || screenH <= 0 || bpp <= 0 || gameW <= 0 ||
		gameH <= 0 || scale <= 0 || fps < 0)
		exit(1);
	
	// Instancia el EngineManager con la configuración solicitada
	engineManager = new EngineManager(screenW, screenH, bpp, fps, gameW, gameH, scale);

	// Guarda un puntero a los subsistemas de sonido, gráficos, entrada y control de frames
	if ((soundEngine = engineManager->getSoundEngine()) == NULL) 
		exit(2);
	if ((gfxEngine = engineManager->getGfxEngine()) == NULL) 
		exit(2);
	if ((input = engineManager->getInput()) == NULL) 
		exit(2);
	if ((frameControl = engineManager->getFrameControl()) == NULL) 
		exit(2);
	
	// Guarda la configuración del juego
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

// Llama al evento asociado a la destrucción y elimina el engineManager instanciado
Game::~Game() {
	onDestroy();
	if (engineManager != NULL) { 
		delete engineManager; engineManager = NULL; 
	}
}

// Métodos de la clase

void Game::onUpdate() {}

void Game::step() {
	// Acciones a realizar si existe un GameState asignado al Game
	if (gameState != NULL) {	
		// Actualiza el input
		input->checkInput();
		finished = input->getFinished();
		
		// ejecuta Game::onStep (supongo que se refiere a GameState::onStep())
		gameState->onStep();
		
		// actualiza el gameState
		gameState->_update();
		// renderiza el gameState
		gameState->onRender();
	}
	
	// Cambios en el GameState
	if (changeWorld)
		// Si hay un nuevo world válido
		if (gameState != NULL && nextState != NULL) {
			// Invoca al evento de finalización del antiguo world
			gameState->onEnd();
			// Elimina el antiguo world
			delete gameState;
			// Actualiza al siguiente estado
			gameState = nextState;
			// No hay siguiente estado
			nextState = NULL;
			// Ya no hay que cambiar el world
			changeWorld = false;
			// Llama al evento de iniciación del nuevo world
			gameState->onInit();
		}
	
	// Obtiene el valor de la duración del último paso y actualiza el valor de los fps medios
	frameControl->update();
}

// Proporciona al Game el nuevo World al que se debe transitar
void Game::changeGameState(GameState* gState) {
	nextState = gState;
	changeWorld = true;
}

// Devuelve un puntero al world actual
GameState* Game::getGameState() { return gameState; }

// Devuelve un puntero al sistema de gráficos
GfxEngine* Game::getGfxEngine() { return gfxEngine; }

// Devuelve un puntero al sistema de sonido
SoundEngine* Game::getSoundEngine() { return soundEngine; }

// Devuelve un puntero al sistema de entrada
Input* Game::getInput() { return input; }

// Comprueba si la ejecución debe finalizar
bool Game::isFinished() { return finished; }

// Devuelve un puntero a un struct con la configuración del juego
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