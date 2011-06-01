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

#include "GameStatus.h"

GameStatus::GameStatus()
{
}

GameStatus::~GameStatus()
{
};

//Inicializa los atributos de GameStatus haciendo copias de los mapas entrantes
void GameStatus::init(int numKeyItems, int maxLife, std::map<int,ToolInfo> tools, int actualMoney,
			MapLocation actualScreen, std::pair<int,int> lastPos, int numPlayers, int numPigeons)
{
	this->numKeyItems = numKeyItems;
	this->maxLife = maxLife;
	this->currentMoney = actualMoney;
	this->currentMapLocation = actualScreen;
	this->lastPlayerPosition = lastPos;
	this->numPlayers = numPlayers;
	this->numPigeons = numPigeons;

	//Copiamos la tabla de tools
	std::map<int,ToolInfo>::iterator it;	//Iterador para recorrer la lista de collectables entrante
	std::pair<int,ToolInfo> aux;			//Par para almacenar los valores que vamos recorriendo

	for(it = tools.begin(); it != tools.end(); it++)
	{
		aux.first = (*it).first;			//Copiamos la clave a un par auxiliar
		aux.second = (*it).second;			//Copiamos el valor a un par auxiliar
		
		this->tools.insert(aux);

	}//end for
}

int GameStatus::getNumKeyItems()
{
	return numKeyItems;
}
		
void GameStatus::setNumKeyItems(int numKeyItems)
{
	this->numKeyItems = numKeyItems;
}

int GameStatus::getMaxLife()
{
	return maxLife;
}

void GameStatus::setMaxLife(int maxLife)
{
	this->maxLife = maxLife;
}

std::map<int, ToolInfo> GameStatus::getTools()
{
	return tools;
}

void GameStatus::setTools(std::map<int, ToolInfo> tools)
{
	std::map<int,ToolInfo>::iterator it;	//Iterador para recorrer la lista de collectables entrante
	std::pair<int,ToolInfo> aux;			//Par para almacenar los valores que vamos recorriendo

	//Borramos el mapa anterior
	this->tools.clear();

	for(it = tools.begin(); it != tools.end(); it++)
	{
		aux.first = (*it).first;			//Copiamos la clave a un par auxiliar
		aux.second = (*it).second;			//Copiamos el valor a un par auxiliar
		
		this->tools.insert(aux);

	}//end for
}

ToolInfo GameStatus::getToolInfo(int idTool)
{
	return tools[idTool];
}

//Se parte de la base que el map no admite repeticiones, sino faltaría comprobar si ese elemento ya existe y realizar los computos pertinentes
void GameStatus::setTool(int idTool, bool available, int idAmmo, int ammoQuantity)
{
	std::pair<int,ToolInfo> aux;

	aux.second.available = available;
	aux.second.idAmmo = idAmmo;
	aux.second.ammoQuantity = ammoQuantity;

	tools.insert(aux);
}

bool GameStatus::isToolAvailable(int idTool)
{
	return tools[idTool].available;
}

void GameStatus::setToolAvailable(int idTool, bool available)
{
	/*std::pair<int,ToolInfo> aux;
	aux.second = tools[idTool];
	aux.second.available = available;

	tools.insert(aux);*/
	tools[idTool].available = true;
}

int GameStatus::getToolAmmoId(int idTool)
{
	return tools[idTool].idAmmo;
}

int GameStatus::getToolAmmoQuantity(int idTool)
{
	return tools[idTool].ammoQuantity;
}

void GameStatus::setToolAmmo(int idTool, int idAmmo)
{
	std::pair<int,ToolInfo> aux;
	aux.second = tools[idTool];
	aux.second.idAmmo = idAmmo;

	tools.insert(aux);
}

//!Establece la cantidad de munición de una herramienta dada
/*!
	\param idTool identificador de la herramienta a actualizar
	\param ammoQuantity cantidad de munición que tendrá dicha herramienta
*/
void GameStatus::setToolAmmoQuantity(int idTool, int ammoQuantity)
{
	std::pair<int,ToolInfo> aux;
	aux.second = tools[idTool];
	aux.second.ammoQuantity = ammoQuantity;

	tools.insert(aux);
}

int GameStatus::getCurrentMoney()
{
	return currentMoney;
}

void GameStatus::setCurrentMoney(int actualMoney)
{
	this->currentMoney = actualMoney;
}

MapLocation GameStatus::getCurrentMapLocation()
{
	return currentMapLocation;
}

void GameStatus::setCurrentMapLocation(MapLocation actualScreen)
{
	this->currentMapLocation = actualScreen;
}

//Devolvera un par con la ultima posición del jugador en la pantalla actual
std::pair<int,int> GameStatus::getLastPlayerPosition()
{
	std::pair<int,int> aux;
	aux.first = currentMapLocation.screenX;
	aux.second = currentMapLocation.screenY;
	return aux;
}

void GameStatus::setLastPlayerPosition(std::pair<int,int> lastPos)
{
	lastPlayerPosition.first = lastPos.first;
	lastPlayerPosition.second = lastPos.second;
}

int GameStatus::getNumPlayers()
{
	return numPlayers;
}

void GameStatus::setNumPlayers(int numPlayers)
{
	this->numPlayers = numPlayers;
}

int GameStatus::getNumPigeons()
{
	return numPigeons;
}

void GameStatus::setNumPigeons(int numPigeons)
{
	this->numPigeons = numPigeons;
}

int GameStatus::getCurrentHeartPieces()
{
	return currentHeartPieces;
}
		
void GameStatus::setCurrentHeartPieces(int heartPieces)
{
	this->currentHeartPieces = heartPieces;
}

int GameStatus::getBarterProgress()
{
	return barterProgress;
}

void GameStatus::setBarterProgress(int barterProgress)
{
	this->barterProgress = barterProgress;
}

int GameStatus::getGameProgress()
{
	return gameProgress;
}

//!Setter de gameProgress
void GameStatus::setGameProgress(int gameProgress)
{
	this->gameProgress = gameProgress;
}

void GameStatus::save(FILE* f){
	int* buffer = new int[14];
	// Escribimos los datos
	// Número de llave
	buffer[0] = numKeyItems;
	// Máxima vida
	buffer[1] = maxLife;
	// Dinero actual
	buffer[2] = currentMoney;
	// Número de pidgeons
	buffer[3] = numPigeons;
	// Número de piezas de corazón actuales
	buffer[4] = currentHeartPieces;
	
	buffer[5] = barterProgress;
	// Progreso del juego
	buffer[6] = gameProgress;
	// Última posición del player
	buffer[7] = lastPlayerPosition.first;
	buffer[8] = lastPlayerPosition.second;

	// Datos del mapa donde se encuentra el player
	buffer[9] = currentMapLocation.id;
	buffer[10] = currentMapLocation.positionX;
	buffer[11] = currentMapLocation.positionY;
	buffer[12] = currentMapLocation.screenX;
	buffer[13] = currentMapLocation.screenY;

	fwrite(buffer, sizeof(int), 14, f);
	delete buffer; buffer = new int[1];
	// Datos de la tabla de herramientas
	// Número de herramientas
	buffer[0] = tools.size();
	fwrite(buffer, sizeof(int), 1, f);
	delete buffer; buffer = new int[4];
	bool* buffer1 = new bool[1];

	for (map<int,ToolInfo>::iterator it = tools.begin(); it != tools.end(); it++){
		/* key */
		buffer[0] = (*it).first;
		/* ToolInfo
					int idTool;
					int idAmmo;
					int ammoQuantity;
					bool available;
		*/
		buffer[1] = (*it).second.idTool;
		buffer[2] = (*it).second.idAmmo;
		buffer[3] = (*it).second.ammoQuantity;
		fwrite(buffer, sizeof(int), 4, f);
		buffer1[0] = (*it).second.available;
		fwrite(buffer1, sizeof(bool), 1, f);
	}
	delete buffer; buffer = NULL;
	delete buffer1; buffer1 = NULL;
}

void GameStatus::load(FILE* f){
	int buffer[14];
	fread(buffer, sizeof(int), 14, f);
	// Número de llave
	numKeyItems = buffer[0];
	// Máxima vida
	maxLife = buffer[1];
	// Dinero actual
	currentMoney = buffer[2];
	// Número de pidgeons
	numPigeons = buffer[3];
	// Número de piezas de corazón actuales
	currentHeartPieces = buffer[4];
	
	barterProgress = buffer[5];
	// Progreso del juego
	gameProgress = buffer[6];
	// Última posición del player
	lastPlayerPosition.first = buffer[7];
	lastPlayerPosition.second = buffer[8];

	// Datos del mapa donde se encuentra el player
	currentMapLocation.id = buffer[9];
	currentMapLocation.positionX = buffer[10];
	currentMapLocation.positionY = buffer[11];
	currentMapLocation.screenX = buffer[12];
	currentMapLocation.screenY = buffer[13];

	// Datos de la tabla de herramientas
	// Número de herramientas

	buffer[1];
	fread(buffer, sizeof(int), 1, f);
	// Datos de la tabla de herramientas
	// Número de herramientas
	int numTools = buffer[0];
	std::pair<int,ToolInfo> aux;
	for (int i = 0; i < numTools; i++){
		/* key */
		buffer[4];
		fread(buffer, sizeof(int), 4, f);
		aux.first = buffer[0];
		aux.second.idTool = buffer[1];
		aux.second.idAmmo = buffer[2];
		aux.second.ammoQuantity = buffer[3];
		bool buffer1[1];
		fread(buffer1, sizeof(bool), 1, f);
		aux.second.available = buffer1[0];
		this->tools.insert(aux);
	}
}