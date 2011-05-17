#include "PGZGame.h"


PGZGame::PGZGame() : Game(224*3, 224*3, 32, 224, 224, 3, 30)
{
	// Se inicializa la semilla del generador de números aleatorios
	srand((unsigned int) time(NULL));

	// Se prepara la ventana de aplicación
	// Se establece el color de fondo
	gfxEngine->setScreenBackgroundColor(Color(20, 20, 25));

	// Se instancia el GameState inicial y se activa
	
	controller = new Controller(this);
	controller->loadInputConfig(controller->mainInputConfig, "config-p1"); 
	gameState = new MainMenuState(224, 224, this);

	reset = false;
	numSaves = 3;
}

PGZGame::~PGZGame()
{
	if (controller != NULL)
		delete controller, controller = NULL;

	/*if (gameState != NULL)
		delete gameState, gameState = NULL;*/
}

void PGZGame::onStep()
{
	if (reset)
	{
		controller->gamePlayState = NULL;
		delete controller;
		controller = new Controller(this);
		controller->loadInputConfig(controller->mainInputConfig, "config-p1"); 
		reset = false;
	}

	// Eventos generales a todo el juego
	// Por ahora, ESCAPE para salir (luego habrá de cambiarse)
	if (getInput()->keyPressed(Input::kESC))
		setFinished(true);

	// Depuración
	// Zoom del juego
	if (getInput()->keyPressed(Input::kO))
		gfxEngine->setGameScreenScale(min(gfxEngine->getGameScreenScaleH()+1, 3), min(gfxEngine->getGameScreenScaleV()+1, 3));
	else if (getInput()->keyPressed(Input::kL))
		gfxEngine->setGameScreenScale(max(gfxEngine->getGameScreenScaleH()-1, 1), max(gfxEngine->getGameScreenScaleV()-1, 1));
};

void PGZGame::startNewgame()
{
	controller->initData("");
			
	GamePlayState* gameState = new GamePlayState(224, 224, this);

	changeGameState(gameState);
	controller->initGamePlayState((GamePlayState*) gameState);
}


void PGZGame::showPrologue()
{
	changeGameState(new IntroState(gameWidth, gameHeight, this));
}

void PGZGame::loadGame(int i){
	if (controller->initData("data/save" + i)){
		GamePlayState* gameState = new GamePlayState(224, 224, this);

		changeGameState(gameState);
		controller->initGamePlayState((GamePlayState*) gameState);
	}
}

void PGZGame::resetGame()
{
	reset = true;
	changeGameState(new MainMenuState(224, 224, this));
}

int PGZGame::getNumSaves(){
	return numSaves;
}