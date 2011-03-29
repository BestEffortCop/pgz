#pragma once
#ifndef __PGZGAME_H__
#define __PGZGAME_H__

#include "Game.h"
#include "GamePlayState.h"
#include "controller.h"

class PGZGame : public Game
{
	private:
		

	public:

		PGZGame() : Game(256*3, 224*3, 32, 256, 224, 3, 30)
		{
			// Se inicializa la semilla del generador de números aleatorios
			//srand((unsigned int) time(NULL));

			// Se prepara la ventana de aplicación
			// Se establece el color de fondo
			//gfxEngine->setScreenBackgroundColor(Color(20, 20, 25));

			// Se instancia el GameState inicial y se activa


			Controller* controller = new Controller(this);
			controller->initData("");
			gameState = new GamePlayState(320, 240, this);
			controller->initGamePlayState((GamePlayState*) gameState);
		}

		void onStep()
		{
			// Eventos generales a todo el juego
			// Por ahora, ESCAPE para salir (luego habrá de cambiarse)
			if (getInput()->keyPressed(Input::kESC))
				setFinished(true);

			/*// Depuración
			// Zoom del juego
			if (getInput()->keyPressed(Input::kO))
				gfxEngine->setGameScreenScale(min(gfxEngine->getGameScreenScaleH()+1, 3), min(gfxEngine->getGameScreenScaleV()+1, 3));
			else if (getInput()->keyPressed(Input::kL))
				gfxEngine->setGameScreenScale(max(gfxEngine->getGameScreenScaleH()-1, 1), max(gfxEngine->getGameScreenScaleV()-1, 1));*/
		};
};

#endif
