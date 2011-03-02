#include "Anim2D.h"



//Constructora parametrizada
Anim2D::Anim2D(string name, vector<int>* frames, int framesPerStep, bool loop):Anim(name)
{
	this->name = name;
	this->framesPerStep = framesPerStep;
	this->loop = loop;
	this->frameList = frameList;
	frameCount = frameList->size();
}

Anim2D::~Anim2D()
{
	delete frameList;
	frameList = NULL;
}

int Anim2D::getFramesPerStep()
{
	return framesPerStep;
}

void Anim2D::setFramesPerStep(int framesPerStep)
{
	this->framesPerStep = framesPerStep;
}

bool Anim2D::getLoop()
{
	return loop;
}

void Anim2D::setLoop(bool loop)
{
	this->loop = loop;
}

string Anim2D::getName()
{
	return name;
}

int Anim2D::getFrameCount()
{
	return frameCount;
}

vector<int>* Anim2D::getFrameList()
{
	return frameList;
}








