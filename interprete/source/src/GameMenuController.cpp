#include "GameMenuController.h"


GameMenuController::GameMenuController(int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate)
{
	selectableList = new list<iSelectable*>();
	menuItemList = new list<GameMenuItem*>();
	depth = 500;
	cursorEnable = false;
	cursorImage = NULL;
	selected = NULL;

	// Se inicia a la configuración por defecto
	inputConfig.joyMode = false;
	inputConfig.gamePad = 0;
	inputConfig.xAxis = 0;
	inputConfig.yAxis = 1;
	inputConfig.joyA = 0;
	inputConfig.joyB = 1;
	inputConfig.joySTART = 2;
	inputConfig.joySELECT = 3;
	
	inputConfig.keyLeft = Input::kLEFT;
	inputConfig.keyRight = Input::kRIGHT;
	inputConfig.keyUp = Input::kUP;
	inputConfig.keyDown = Input::kDOWN;
	inputConfig.keyA = Input::kA;
	inputConfig.keyB = Input::kS;
	inputConfig.keySTART = Input::kENTER;
	inputConfig.keySELECT = Input::kSPACE;


	currentInput.xAxis = 0;
	currentInput.yAxis = 0;
	currentInput.buttonA = OFF;
	currentInput.buttonB = OFF;
	currentInput.buttonSTART = OFF;
	currentInput.buttonSELECT = OFF;

	lastDir = NONE;
}

GameMenuController::~GameMenuController(void)
{
	// No debe borrar sus items ni selectables ya que pertenecen al gstate y los borra el
	
	delete selectableList;
	delete menuItemList;
	delete cursorImage;
}


void GameMenuController::onRender()
{

	graphic->render(x, y);
	if (cursorEnable)
		cursorImage->render(cursorPosX, cursorPosY);
}

void GameMenuController::onStep()
{
	parseInput();

	Direction dir = NONE;

	if (currentInput.yAxis < -0.3) {dir = UP;}
	if (currentInput.yAxis > 0.3) {dir = DOWN;}

		if (currentInput.xAxis > 0.3)
		{
			if (dir == UP)
				dir = UPRIGHT;
			else if (dir == DOWN)
				dir = DOWNRIGHT;
			else
				dir = RIGHT;
		}


	if (currentInput.xAxis < -0.3)
	{
		if (dir == UP)
				dir = UPLEFT;
			else if (dir == DOWN)
				dir = DOWNLEFT;
			else
				dir = LEFT;
	}

	if (currentInput.buttonA == PRESSED) 
	{
		selected->onChosen();
	}

	if (currentInput.buttonB == PRESSED) 
	{
		selected->onCancelled();
	}


	if (dir != lastDir)
	{
		iSelectable* slc = NULL;
		slc = getMandatorySelectable(selected, dir);

		if (slc == NULL)
		{
			iSelectable* slc = getSelectable(dir);
			if (slc != NULL)
			{
				selected = slc;
				cursorPosX = slc->cursorPlaceX;
				cursorPosY = slc->cursorPlaceY;
			}
			else
			{
				slc = getAlternativeSelectable(selected, dir);
				if (slc != NULL)
					selected = slc;
			}
		}
		else
		{
			selected = slc;
		}
		lastDir = dir;
	}

	if (selected != NULL)
	{
		cursorPosX = selected->cursorPlaceX;
		cursorPosY = selected->cursorPlaceY;
	}
}

iSelectable* GameMenuController::getMandatorySelectable(iSelectable* slc, Direction dir)
{
	return NULL;
}

iSelectable* GameMenuController::getAlternativeSelectable(iSelectable* slc, Direction dir)
{
	return NULL;
}


void GameMenuController::launch()
{
	world->add(this);
}

void GameMenuController::quit()
{
	for (list<GameMenuItem*>::iterator it = menuItemList->begin(); it != menuItemList->end(); it++)
	{
		(*it)->instance_destroy();
	}

	instance_destroy();
}


iSelectable* GameMenuController::getSelectable(Direction dir)
{
	if (dir != NONE)
	{
		int ox, oy;
		ox = selected->mask->x;
		oy = selected->mask->y;


		short dirY, dirX;
		dirX = dirY = 0;

		int tx, ty;
		tx = ty = 0;

		GameConfig* config = game->getGameConfig();

		if (((dir == DOWN) || (dir == DOWNRIGHT)) || (dir == DOWNLEFT))
		{
			dirY = 1;
			ty = config->gameHeight;
		}
		else if (((dir == UP) || (dir == UPRIGHT)) || (dir == UPLEFT))
		{
			dirY = -1;
			ty = 0;
		}
		
		if (((dir == RIGHT) || (dir == UPRIGHT)) || (dir == DOWNRIGHT))
		{
			dirX = 1;
			tx = config->gameWidth;
		}
		else if (((dir == LEFT) || (dir == UPLEFT)) || (dir == DOWNLEFT))
		{
			dirX = -1;
			tx = 0;
		}

		
		list<iSelectable*>::iterator i = selectableList->begin();
		list<iSelectable*>::iterator best;
		vector<CollisionPair>* collision_list;

		int distanceY = 0;
		int distanceX = 0;
		int distance = 0;
		int min = max(config->gameWidth,config->gameHeight)*max(config->gameWidth,config->gameHeight);
		bool found = false;
		while (!found && ((ty - selected->mask->y)*dirY >= 0) && ((tx - selected->mask->x)*dirX >= 0))
		{
			while (i != selectableList->end())
			{
				if (((*i) != selected) && ((*i)->enabled))
				{
					collision_list = selected->mask->collide((*i)->mask);
					if ((collision_list != NULL) && (collision_list->size() > 0))
					{
						if (dirX != 0)
							distanceX = abs((*i)->mask->x - selected->mask->x);
						if (dirY != 0)
							distanceY = abs((*i)->mask->y - selected->mask->y);

						distance = distanceY*distanceY + distanceX*distanceX;

						if	((distance < min) ||
							((distance == min) &&
								(((distanceY*distanceY == min) && ((dirY*((*i)->mask->x - selected->mask->x) >= 0))) ||
								((distanceX*distanceX == min) && (dirX*((*i)->mask->y - selected->mask->y) >= 0)))))
						{
							min = distance;
							best = i;
							found = true;
						}
					}
					if (collision_list != NULL)
						delete collision_list;
				}
				i++;
			}

			i = selectableList->begin();

			if ((dirX != 0) && (dirY != 0))
			{
				int tmp = (-max(-selected->mask->width, -selected->mask->height)) / 2;

				selected->mask->x += tmp*dirX;
				selected->mask->y += tmp*dirY;
			}
			else
			{
				selected->mask->x += (selected->mask->width / 2)*dirX;
				selected->mask->y += (selected->mask->height / 2)*dirY;
			}
		}
		selected->mask->x = ox;
		selected->mask->y = oy;

		delete config;

		if (found)
			return (*best);
		else
			return NULL;//selected;
	}
	return selected;
}

void GameMenuController::setCursorPos(int x, int y)
{
	this->cursorPosX = x;
	this->cursorPosY = y;
}

void GameMenuController::setCursorImage(Graphic* g)
{
	if (cursorImage != NULL)
		delete cursorImage;

	cursorImage = g;
}

void GameMenuController::addSelectable(iSelectable* selectable)
{
	selectable->setMenuController(this);
	if (selectable->enabled && ((selectableList->size() == 0) || ((selected == NULL) && (selectableList->size() > 0))))
	{
		setSelected(selectable);
	}
	selectableList->push_back(selectable);
}

void GameMenuController::addMenuItem(GameMenuItem* menuItem)
{
	world->add(menuItem);
	menuItemList->push_back(menuItem);

	if (iSelectable* i = dynamic_cast<iSelectable*>(menuItem))
		addSelectable(i);
}

void GameMenuController::removeSelectable(iSelectable* selectable)
{
	selectableList->remove(selectable);
	delete selectable;
}

void GameMenuController::removeMenuItem(GameMenuItem* menuItem)
{
	if (iSelectable* slc = dynamic_cast<iSelectable*>(menuItem))
		selectableList->remove(slc);

	menuItemList->remove(menuItem);
	menuItem->instance_destroy();
}

void GameMenuController::setSelected(iSelectable* i)
{
	cursorEnable = true;
	cursorPosX =  i->cursorPlaceX;
	cursorPosY =  i->cursorPlaceY;
	selected = i;
	selected->onSelected();
}


void GameMenuController::onSelected(iSelectable* selectable)
{
}

void GameMenuController::onDeselected(iSelectable* selectable)
{
}

void GameMenuController::onBeingDeselected(iSelectable* selectable)
{
}

void GameMenuController::onChosen(iSelectable* selectable)
{
}

void GameMenuController::onCancelled(iSelectable* selectable)
{
}

void GameMenuController::onIddle(iSelectable* selectable)
{
}

void GameMenuController::parseInput()
{
	// Here be the config and such
	Input* input = game->getInput();

	if (inputConfig.joyMode)
	{
		// Control por gamepad
		currentInput.xAxis = input->joyAxis(inputConfig.gamePad, inputConfig.xAxis);
		currentInput.yAxis = input->joyAxis(inputConfig.gamePad, inputConfig.yAxis);

		if (input->joyPressed(inputConfig.gamePad, inputConfig.joyA))
			currentInput.buttonA = PRESSED;
		else if (input->joyReleased(inputConfig.gamePad, inputConfig.joyA))
			currentInput.buttonA = RELEASED;
		else if (input->joyButton(inputConfig.gamePad, inputConfig.joyA))
			currentInput.buttonA = ON;
		else
			currentInput.buttonA = OFF;

		if (input->joyPressed(inputConfig.gamePad, inputConfig.joyB))
			currentInput.buttonB = PRESSED;
		else if (input->joyReleased(inputConfig.gamePad, inputConfig.joyB))
			currentInput.buttonB = RELEASED;
		else if (input->joyButton(inputConfig.gamePad, inputConfig.joyB))
			currentInput.buttonB = ON;
		else
			currentInput.buttonB = OFF;

		if (input->joyPressed(inputConfig.gamePad, inputConfig.joySTART))
			currentInput.buttonSTART = PRESSED;
		else if (input->joyReleased(inputConfig.gamePad, inputConfig.joySTART))
			currentInput.buttonSTART = RELEASED;
		else if (input->joyButton(inputConfig.gamePad, inputConfig.joySTART))
			currentInput.buttonSTART = ON;
		else
			currentInput.buttonSTART = OFF;

		if (input->joyPressed(inputConfig.gamePad, inputConfig.joySELECT))
			currentInput.buttonSELECT = PRESSED;
		else if (input->joyReleased(inputConfig.gamePad, inputConfig.joySELECT))
			currentInput.buttonSELECT = RELEASED;
		else if (input->joyButton(inputConfig.gamePad, inputConfig.joySELECT))
			currentInput.buttonSELECT = ON;
		else
			currentInput.buttonSELECT = OFF;
	}
	else
	{
		// Control por teclado
		if (input->key(inputConfig.keyLeft)) currentInput.xAxis = -1;
		else if (input->key(inputConfig.keyRight)) currentInput.xAxis = 1;
		else currentInput.xAxis = 0;

		if (input->key(inputConfig.keyUp)) currentInput.yAxis = -1;
		else if (input->key(inputConfig.keyDown)) currentInput.yAxis = 1;
		else currentInput.yAxis = 0;

		if (input->keyPressed(inputConfig.keyA))
			currentInput.buttonA = PRESSED;
		else if (input->keyReleased(inputConfig.keyA))
			currentInput.buttonA = RELEASED;
		else if (input->key(inputConfig.keyA))
			currentInput.buttonA = ON;
		else
			currentInput.buttonA = OFF;

		if (input->keyPressed(inputConfig.keyB))
			currentInput.buttonB = PRESSED;
		else if (input->keyReleased(inputConfig.keyB))
			currentInput.buttonB = RELEASED;
		else if (input->key(inputConfig.keyB))
			currentInput.buttonB = ON;
		else
			currentInput.buttonB = OFF;
	
		if (input->keyPressed(inputConfig.keySTART))
			currentInput.buttonSTART = PRESSED;
		else if (input->keyReleased(inputConfig.keySTART))
			currentInput.buttonSTART = RELEASED;
		else if (input->key(inputConfig.keySTART))
			currentInput.buttonSTART = ON;
		else
			currentInput.buttonSTART = OFF;

		if (input->keyPressed(inputConfig.keySELECT))
			currentInput.buttonSELECT = PRESSED;
		else if (input->keyReleased(inputConfig.keySELECT))
			currentInput.buttonSELECT = RELEASED;
		else if (input->key(inputConfig.keySELECT))
			currentInput.buttonSELECT = ON;
		else
			currentInput.buttonSELECT = OFF;
	}
}

void GameMenuController::setInputConfig(InputConfig ic)
{
	inputConfig = ic;
}

InputConfig GameMenuController::getInputConfig()
{
	return inputConfig;
}