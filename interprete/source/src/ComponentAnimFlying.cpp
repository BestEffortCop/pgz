#include "ComponentAnimFlying.h"


ComponentAnimFlying::ComponentAnimFlying(Game* game, Enemy* e, std::string gfxPath) : ComponentAnim(game, e, gfxPath)
{
	height = 0;
	period = 1;
	amplitude = 0;
	phase = 1;
}


ComponentAnimFlying::~ComponentAnimFlying()
{
}

void ComponentAnimFlying::init(int height, float period, int amplitude, int phase)
{
	this->height = height;
	this->period = period;
	this->amplitude = amplitude;
	this->phase = phase;
}

void ComponentAnimFlying::onCInit()
{
	e->cAnim->setHeight(height);
	e->setTimer(1, rand()%phase);
	ComponentAnim::onCInit();
}

void ComponentAnimFlying::onCStep()
{
	e->cAnim->setHeight(height + (int) (sin((float) e->getTimer(1)*period)*amplitude));
	ComponentAnim::onCStep();
}

void ComponentAnimFlying::onCRender()
{
	ComponentAnim::onCRender();
}

void ComponentAnimFlying::onCTimer(int timer)
{
	if (timer == 1)
			e->setTimer(1, 359);
	ComponentAnim::onCTimer(timer);
}
