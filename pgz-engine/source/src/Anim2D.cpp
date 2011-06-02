/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
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
//	  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "Anim2D.h"



//Constructora parametrizada
Anim2D::Anim2D(string name, vector<int>* frames, int framesPerStep, bool loop):Anim(name)
{
	//Asigno todos los atributos con su parametro de entrada correspondiente
	this->name = name;
	this->framesPerStep = framesPerStep;
	this->loop = loop;
	this->frameList = frames;
	logger = Logger::Instance();
	//Si la lista que me han pasado no es NULL asigno su tamaño a la variable frameCount
	if (frameList != NULL)
		frameCount = frameList->size();
	else 
		logger->log(std::string("Anim2D::Anim2D - La animación \"" + name + "\" tiene una lista de frames vacía.").c_str());
}

//Destructora
Anim2D::~Anim2D()
{
	//Borro el frameList
	delete frameList;
	frameList = NULL;
	//Logger::DestroyInstance();
}

//Devuelve el numero de steps que se ejecuta un frame
int Anim2D::getFramesPerStep()
{
	return framesPerStep;
}

//Modifica el numero de steps que se ejecuta un frame
void Anim2D::setFramesPerStep(int framesPerStep)
{
	this->framesPerStep = framesPerStep;
}

//Devuelve si la animación se repetirá al acabar o no
bool Anim2D::getLoop()
{
	return loop;
}

//Modifica si la animación se repetirá al acabar o no
void Anim2D::setLoop(bool loop)
{
	this->loop = loop;
}

//Devuelve el nombre de la animación
string Anim2D::getName()
{
	return name;
}

//Devuelve el número de frames que tiene la animación
int Anim2D::getFrameCount()
{
	return frameCount;
}

//Devuelve la lista de frames
vector<int>* Anim2D::getFrameList()
{
	return frameList;
}








