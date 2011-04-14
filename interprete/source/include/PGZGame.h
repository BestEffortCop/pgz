#pragma once
#ifndef __PGZGAME_H__
#define __PGZGAME_H__

#include "Game.h"
#include "GamePlayState.h"
#include "controller.h"

#include "DataBaseInterface.h"
#include "Player.h"

//Testeo enemigo
#include "Enemy.h"
#include "Component.h"
#include "MummyComponent.h"




class PGZGame : public Game
{
	private:

	public:

		Controller* controller;

		PGZGame() : Game(224*3, 192*3, 32, 224, 192, 3, 30)
		{
			// Se inicializa la semilla del generador de números aleatorios
			//srand((unsigned int) time(NULL));

			// Se prepara la ventana de aplicación
			// Se establece el color de fondo
			//gfxEngine->setScreenBackgroundColor(Color(20, 20, 25));

			// Se instancia el GameState inicial y se activa

			controller = new Controller(this);
			controller->initData("");
			
			gameState = new GamePlayState(320, 240, this);
			controller->initGamePlayState((GamePlayState*) gameState);
			
			//Testeo enemigo
			vector<Component*>* components = new vector<Component*>();
			vector<Component*>* components1 = new vector<Component*>();
			vector<Component*>* components2 = new vector<Component*>();
			Component* mummy = new MummyComponent(this,controller);
			Component* mummy1 = new MummyComponent(this,controller);
			Component* mummy2 = new MummyComponent(this,controller);

			components->push_back(mummy);
			components1->push_back(mummy1);
			components2->push_back(mummy2);
			Enemy* e = new Enemy(50,100,this,gameState,components);
			Enemy* e1 = new Enemy(70,120,this,gameState,components1);
			Enemy* e2 = new Enemy(100,100,this,gameState,components2);
			gameState->add(e);
			gameState->add(e1);
			gameState->add(e2);

		}


		~PGZGame()
		{
			if (controller != NULL)
				delete controller, controller = NULL;

			if (gameState != NULL)
				delete gameState, gameState = NULL;
		}
		void onStep()
		{
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
};

#endif
