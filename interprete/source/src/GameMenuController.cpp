#include "GameMenuController.h"


GameMenuController::GameMenuController(int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate)
{
}


GameMenuController::~GameMenuController(void)
{
}


void GameMenuController::onRender()
{
}

void GameMenuController::onUpdate()
{
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

	g = cursorImage;
}