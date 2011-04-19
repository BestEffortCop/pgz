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
		cursorImage->render(cursorPosX, cursorPosY);
}

void GameMenuController::onStep()
{
	Direction dir = NONE;
	if (game->getInput()->key(Input::kUP)) {dir = UP;}
	if (game->getInput()->key(Input::kDOWN)) {dir = DOWN;}

	if (game->getInput()->key(Input::kQ)) 
	{
		quit();
	}

	iSelectable* slc = getSelectable(dir);

	selected = slc;
	cursorPosX = slc->cursorPlaceX;
	cursorPosY = slc->cursorPlaceY;
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
	if (dir == UP)
		return selectableList->front();
	else if (dir == DOWN)
		return selectableList->back();
	else
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
	if (selectableList->size() == 0)
	{
		cursorEnable = true;
		cursorPosX =  selectable->cursorPlaceX;
		cursorPosY =  selectable->cursorPlaceY;
		selected = selectable;
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