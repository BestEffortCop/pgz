#include "GameMenuController.h"


GameMenuController::GameMenuController(int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate)
{
	selectableList = new list<iSelectable*>();
	menuItemList = new list<GameMenuItem*>();
	depth = 500;
	cursorEnable = false;
	cursorImage = NULL;
	selected = NULL;
}

GameMenuController::~GameMenuController(void)
{
	// No debe borrar sus items ni selectables ya que (por ahora) pertenecen al gstate y los borra el
	/*
	GameMenuItem* tmp;
	list<GameMenuItem*>::iterator it = menuItemList->begin();
	while( it != menuItemList->end())
	{
		tmp = (*it);
		menuItemList->remove(*it);
		if (tmp != NULL)
			delete tmp;
		it = menuItemList->begin();
	}*/

	delete selectableList;
	delete menuItemList;
}


void GameMenuController::onRender()
{

	graphic->render(x, y);
	if (cursorEnable)
		cursorImage->render(cursorPosX, /*offset*/16 + cursorPosY);
}

void GameMenuController::onStep()
{
	Direction dir = NONE;
	if (game->getInput()->key(Input::kUP)) {dir = UP;}
	if (game->getInput()->key(Input::kDOWN)) {dir = DOWN;}

		if (game->getInput()->key(Input::kRIGHT)) 
		{
			if (dir == UP)
				dir = UPRIGHT;
			else if (dir == DOWN)
				dir = DOWNRIGHT;
			else
				dir = RIGHT;
		}


	if (game->getInput()->key(Input::kLEFT))	
	{
		if (dir == UP)
				dir = UPLEFT;
			else if (dir == DOWN)
				dir = DOWNLEFT;
			else
				dir = LEFT;
	}

	if (game->getInput()->key(Input::kQ)) 
	{
		quit();
	}

	if (game->getInput()->key(Input::kX)) 
	{
		selected->onChosen();
	}

	iSelectable* slc = getSelectable(dir);

	selected = slc;

	if (selected != NULL)
	{
		cursorPosX = slc->cursorPlaceX;
		cursorPosY = slc->cursorPlaceY;
	}
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
			return selected;
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