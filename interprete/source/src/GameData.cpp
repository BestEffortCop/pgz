/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by working on it and helping it be better or by playing it in it's actual state	//																			
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "GameData.h"


GameData::GameData()
{
	// creamos el estado del juego por defecto
	gameStatus = new GameStatus();
}

GameData::~GameData()
{
	// borramos el gameStatus
	if (gameStatus != NULL) 
		delete gameStatus, gameStatus = NULL;
}

void GameData::init(int maxHeartPieces, int maxPigeons, int maxKeyItems)
{
	neededHeartPieces = maxHeartPieces;
	this->maxKeyItems = maxKeyItems;
	this->maxPigeons = maxPigeons;
}

GameStatus* GameData::getGameStatus()
{
	return gameStatus;
}

int GameData::getNeededHeartPieces()
{
	return neededHeartPieces;
};
void GameData::setNeededHeartPieces(int number)
{
	neededHeartPieces = number;
};

int GameData::getMaxKeyItems()
{
	return maxKeyItems;
}

void GameData::setMaxKeyItems(int number)
{
	maxKeyItems = number;
}

int GameData::getMaxPigeons()
{
	return maxPigeons;
}

void GameData::setMaxPigeons(int number)
{
	maxPigeons = number;
}

void GameData::save(FILE* f){
	// Escribimos datos del game status
	this->gameStatus->save(f);
};

void GameData::load(FILE* f){
	// Cargamos datos del game status
	gameStatus->load(f);
};