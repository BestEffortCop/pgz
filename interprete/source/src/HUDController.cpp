#include "HUDController.h"

HUDController::HUDController(Game* g, GameState* gs) : Entity(0, 0, g, gs)
{
	numHUDs = 0;
	collidable = false;
};

HUDController::~HUDController()
{
	for (int i = 0; i < numHUDs; i++)
		if (HUDS[i] != NULL) delete HUDS[i], HUDS[i] = NULL;
};

void HUDController::onStep()
{
	for (int i = 0; i < numHUDs; i++)
		HUDS[i]->refresh();
};

void HUDController::onRender()
{
	for (int i = 0; i < numHUDs; i++)
		HUDS[i]->onRender();
};

bool HUDController::addHud(Player* p)
{
	if (numHUDs > 4)
		return false;
	else
	{
		if (numHUDs == 0)
			HUDS[numHUDs] = new HUD(0, 0, p);
		else
			HUDS[numHUDs] = new HUD(0, 208, p);
		numHUDs++;
	}

	return true;
};

void HUDController::enableHUDs()
{
	this->disable();
};

void HUDController::disableHUDs()
{
	this->enable();
};

int HUDController::getNumHUDS()
{
	return numHUDs;
};

HUD* HUDController::getHUD(int num)
{
	if (num >= numHUDs)
		return NULL;
	else return HUDS[num];
};