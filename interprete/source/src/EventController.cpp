/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
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
//    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "EventController.h"
#include "Controller.h"

#include "StateMenu.h"
#include "ToolMenu.h"
#include "ArenaEntity.h"
#include "DamageableBlockade.h"
#include "MessageDialog.h"
#include "CollectableGameItem.h"
#include "FloorButton.h"
#include "ComponentDivide.h"
#include "ComponentMelee.h"
#include "ComponentRanged.h"
#include "ComponentMeleeSimple.h"
#include "ComponentAnim.h"
#include "ComponentAnimFlying.h"
#include "ComponentTiledMovement.h"
#include "ComponentTest.h"
#include "ComponentBatMovement.h"
#include "Enemy.h"
#include "Instantiator.h"
#include "MessageController.h"
#include "GameFinalItem.h"

#include "ComponentTackle.h"


EventController::EventController(Game* g, GameState* gs, Controller* controller) : Entity(0, 0, g, gs)
{
	this->controller = controller;
	visible = true;
	collidable = false;
	persistent = true;

	currentTrans.effect = SCROLL;
	currentTrans.direction = NONE;
	currentTrans.speed = -1;

	depth = -5;

	toolMenu = NULL;
	stateMenu = NULL;
	gameOver = NULL;
}

EventController::~EventController()
{
};

void EventController::initTransition(TransitionProperties e, Image* oldRoom, Image* newRoom)
{
	// Se pone el controller en modo transition
	controller->setState(Controller::TRANSITION);

	// Se guardan los datos de transisición
	currentTrans = e;
	// y las imágenes
	currentRoom = oldRoom;
	nextRoom = newRoom;

	// actualizamos nuestros datos
	speed = e.speed;
	if (oldRoom != NULL)
		width = oldRoom->getWidth(),
		height = oldRoom->getHeigth();
	else width = 0, height = 0;

	switch (e.effect)
	{
	case SCROLL:
		{ 
			std::pair<int, int> off = ((GamePlayState*) world)->getOffset(); 
			mx = tx = off.first;
			my = ty = off.second;
		}
		xdir = 0; ydir = 0;
		switch (e.direction) 
		{			
			case UP: 
				ydir = 1;
				ty += height;
				break;
			case DOWN: 
				ydir = -1;
				ty -= height;
				break;
			case LEFT:  
				xdir = 1; 
				tx += width;
				break;
			case RIGHT:  
				xdir = -1; 
				tx -= width;
				break;
		}

		// Player visibles
		/*for (int i = 0; i < controller->getNumPlayers(); i++)
			controller->getPlayer(i)->setVisible(true);*/

		break;
	case FADE:

		for (int i = 0; i < controller->getNumPlayers(); i++)
			controller->getPlayer(i)->setVisible(false);

		fadeOut = true;
		falpha = 1;
		maxCounter = (int) ((float) speed)/2*game->getTargetFPS();
		setTimer(1, maxCounter);

		break;
	}
};

void EventController::onStep()
{
	switch (controller->getState()) 
	{
		case Controller::NORMAL: 
			{
				if (controller->getMessageController() != NULL)
					controller->messageController->onStep();
				// check player in bounds map
				int i = 0;
				bool out = false;
				Direction dir = NONE;
				// Calculamos si algún player se sale del mapa
				while ((i < controller->getNumPlayers()) && !out)
				{ 
					//inside = controller->getScreenMap()->isInBounds(controller->getPlayer(i));
					dir = controller->getScreenMap()->relative_position(controller->getPlayer(i), out);
					i++;
				}

				// Si ocurre, realizamos la transición
				if (out)
				{
					// Cambiamos de pantalla
					if ((controller->getPlayer(i-1)->getState() != Player::Normal) || (!controller->moveScreen(dir)))
					{
						Player* p = controller->getPlayer(i-1);
						p->toLastPosition();
					}
				}
				bool muerte = true;
				int j = 0;
				while(muerte && j < controller->getNumPlayers())
				{
					if (controller->getPlayer(j)->hp == 0)
						muerte = false;
					j++;
				}

				if (!muerte && (gameOver == NULL))
				{
					gameOver = new GameOverMenu(0, 0, game, game->getGameState(),controller->getDataBaseInterface());
					gameOver->launch();
				}

				/*TESTEO*/

				stepTest();


				break;
			}
		case Controller::TRANSITION:
			{
				switch (currentTrans.effect)
				{
				case SCROLL:
					// Si no hemos acabado de desplazar la pantalla, continuamos
					if (abs(mx + speed*xdir) < abs(tx))
					{
						mx += speed*xdir;
						for (int i = 0; i < controller->getNumPlayers(); i++)
						{
							// Colocamos al player ajustando con el offset del GamePlayState
							controller->getPlayer(i)->x = mx-controller->getPlayer(i)->graphic->getWidth()/2-((GamePlayState*)world)->getOffset().first;
							if (currentTrans.direction == RIGHT) controller->getPlayer(i)->x += width;
							controller->getPlayer(i)->setVisible(true);
						}
					}
					else if (abs(my + speed*ydir) < abs(ty))
					{
						my += speed*ydir;
						for (int i = 0; i < controller->getNumPlayers(); i++)
						{
							// Colocamos al player ajustando con el offset del GamePlayState
							controller->getPlayer(i)->setVisible(true);
							controller->getPlayer(i)->y = my-16-((GamePlayState*)world)->getOffset().second;
							if (currentTrans.direction == DOWN) controller->getPlayer(i)->y += height-2;
						}
					}
					// Si hemos acabado, pasamos a estado normal
					else
						controller->endTransition();

					break;

				case FADE:
					if (!fadeOut)
						falpha = 1.f - ((float) getTimer(1))/((float)maxCounter);
					else
						falpha = ((float)getTimer(1))/((float)maxCounter);

					if (getTimer(1) <= 0 && !fadeOut) controller->endTransition();
					break;
				}

				break;
			}

		default:
			break;
	}
}

void EventController::onRender()
{
	std::pair<int, int> offset = ((GamePlayState*)world)->getOffset();
	switch (controller->getState()) 
	{
	case Controller::TRANSITION:
		switch (currentTrans.effect)
		{
		case SCROLL:
			// Durante la transición, pintamos el mapa en desplazamiento en la correspondiente posición
			controller->game->getGfxEngine()->render(currentRoom, mx, my);
			controller->game->getGfxEngine()->render(nextRoom, mx - xdir*width, my - ydir*height);
			break;
		case FADE:
			game->getGfxEngine()->renderRectangle(offset.first, offset.second, width, height, Color::Black);

			if (fadeOut)
				game->getGfxEngine()->renderExt(currentRoom, offset.first, offset.second, Color::White, falpha, 1, 1, 0);
			else
				game->getGfxEngine()->renderExt(nextRoom, offset.first, offset.second, Color::White, falpha, 1, 1, 0);
			
			for (int i = 0; i < controller->getNumPlayers(); i++)
			{
				Player* p = controller->getPlayer(i);
				p->setVisible(true);
				p->graphic->setAlpha(falpha),
				p->x += offset.first;
				p->y += offset.second;
				p->onRender();
				p->x -= offset.first;
				p->y -= offset.second;
				p->graphic->setAlpha(1),
				p->setVisible(false);
			}

			break;
		}

	default:
		break;
	}
}


void EventController::onTimer(int timer){

	switch (timer) {

		// multiplayer-warp timer
		case 0:
			/* resolver conflicto de cambio de mapas

			PortInfo winner;

			// get portal with most players in them

			// realiza el cambio de mapa de forma forzada sobre el jugador p
			change_map(winner.MapLocation, winner.p, winner.te, true);*/

			break;

		case 1:
			// fade timer
			if (fadeOut)
			{
				fadeOut = false;
				setTimer(1, maxCounter);
				for (int i = 0; i < controller->numPlayers; i++)
				{
					Player* p = controller->players[i];
					p->setPos(xpos+8-p->mask->width/2, ypos+8-p->mask->height/2);
				}
			}
			else
				controller->endTransition();
	}
}

void EventController::stepTest()
{
	CollectableGameItem* it;

	if (game->getInput()->keyPressed(Input::kT)){
		controller->save();
	}
	if (game->getInput()->keyReleased(Input::kN1))
	{
		MapLocation m; m.id = 0; m.screenX = -1; m.screenY = -1;
		m.positionX = -1; m.positionY = -1;
		controller->teleportTo(m, controller->getPlayer(0), FADE, false);
	}
	else if (game->getInput()->keyReleased(Input::kN2))
	{
		MapLocation m; m.id = 1; m.screenX = -1; m.screenY = -1;
		m.positionX = -1; m.positionY = -1;
		controller->teleportTo(m, controller->getPlayer(0), FADE, false);
	}
	else if (game->getInput()->keyReleased(Input::kN3))
	{
		MapLocation m; m.id = 2; m.screenX = -1; m.screenY = -1;
		m.positionX = -1; m.positionY = -1;
		controller->teleportTo(m, controller->getPlayer(0), FADE, false);
	};

	if (game->getInput()->keyPressed(Input::kG))
	{
		controller->toolController->equip(0, controller->getPlayer(0), 0);
	}

	else if (game->getInput()->key(Input::kF))
	{
		controller->toolController->equip(1, controller->getPlayer(0), 1);
	}

	if (game->getInput()->keyPressed(Input::kE))
	{
		vector<Component*>* components = new vector<Component*>();
		components->push_back(new ComponentTiledMovement(game, controller));
		//components->push_back(new ComponentRanged(game, controller));
		ComponentDivide* h = new ComponentDivide(game,controller);
		h->setMinions(3);
		components->push_back(h);
		Enemy* e = new Enemy(game, world);
		EnemySpawnData spw;
		spw.id = 0;
		spw.x = 112;
		spw.y = 96;
		ComponentAnim* cAnim = new ComponentAnim(game, e, "data/gfx/enemy-octorok.png");
		//ComponentAnimFlying* cAnim = new ComponentAnimFlying(game, e, "data/Gfx/enemy-octorok.png");
		//cAnim->init(13, 0.5f, 6, 359);
		e->init(spw, components, cAnim, 15, 5, 8, 1);
		world->add(e);
	};
				/*
	if (game->getInput()->keyPressed(Input::kBACK)) {
		vector<Component*>* components = new vector<Component*>();
		components->push_back(new ComponentBatMovement(game, controller));
		Enemy* e = new Enemy(game, world);
		EnemySpawnData spw;
		spw.id = 0;
		spw.x = 112;
		spw.y = 96;
		ComponentAnimFlying* cAnim = new ComponentAnimFlying(game, e, "data/graphics/bat.png");
		cAnim->init(10, 0.2f, 3, 359);
		e->init(spw, components, cAnim, 5, 5, 8, 0);
		world->add(e);
	}
	*/
	if (game->getInput()->keyPressed(Input::kBACK))
	{
		controller->changeGameStateTo(Controller::TITLE);
	}

	if (game->getInput()->keyPressed(Input::kJ))
	{
		GameFinalItem* gfi = new GameFinalItem(100, 100, game, world);
		gfi->init("data/gfx/triforce.png", controller);
		gfi->initShadow(GameEntity::sSmall);
		world->add(gfi);
	};

	if (game->getInput()->keyPressed(Input::kI))
	{
		GameItem* it = new GameItem(16*(2+rand()%10), 16*(2+rand()%8), game, world);

		DataBaseInterface::ToolData tdata;
		DataBaseInterface* dbi = controller->getDataBaseInterface();
		int tries = 100;
		bool valid = false;
		while (tries > 0 && !valid)
		{
			tdata = dbi->getToolData(dbi->getToolAtPosition(rand()%(controller->getDataBaseInterface()->getToolNumber())));
			valid = (tdata.gfxAmmo != -1);
		}
		if (valid)
		{
			it->init(dbi->getImagePath(tdata.gfxAmmo), GameItem::ieTOOLAMMO, tdata.idTool);
		}

		controller->gamePlayState->add(it);
	}
}

void EventController::closeGameOverMenu()
{
	gameOver = NULL;
}


void EventController::launchToolsMenu()
{
	if (toolMenu == NULL && gameOver == NULL)
	{
		toolMenu = new ToolMenu(0, 0, game, game->getGameState());
		toolMenu->launch();
		toolMenu = NULL;
	}
};

void EventController::launchStatusMenu()
{
	if (stateMenu == NULL && gameOver == NULL)
	{
		stateMenu = new StateMenu(0, 0, game, game->getGameState());
		stateMenu->launch();
		stateMenu = NULL;
	}
};