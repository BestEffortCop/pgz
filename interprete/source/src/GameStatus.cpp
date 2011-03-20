#include "GameStatus.h"

GameStatus::GameStatus()
{
}

//Llama a init para inicializar los elementos
GameStatus::GameStatus(int numKeyItems, int maxLife, std::map<int,ToolInfo> tools, int actualMoney,
			MapId actualScreen, std::pair<int,int> lastPos, int numPlayers, int numPidgeons,
			int numHeartPieces, int maxHeartPieces, int barterProgress, int gameProgress)
{
	init(numKeyItems, maxLife, tools, actualMoney, actualScreen, lastPos, numPlayers, numPidgeons, numHeartPieces, maxHeartPieces,
		barterProgress, gameProgress);
}

//Inicializa los atributos de GameStatus haciendo copias de los mapas entrantes
void GameStatus::init(int numKeyItems, int maxLife, std::map<int,ToolInfo> tools, int actualMoney,
			MapId actualScreen, std::pair<int,int> lastPos, int numPlayers, int numPidgeons,
			int numHeartPieces, int maxHeartPieces, int barterProgress, int gameProgress)
{
	this->numKeyItems = numKeyItems;
	this->maxLife = maxLife;
	this->actualMoney = actualMoney;
	this->actualScreen = actualScreen;
	this->lastPos = lastPos;
	this->numPlayers = numPlayers;
	this->numPidgeons = numPidgeons;
	this->numHeartPieces = numHeartPieces;
	this->barterProgress = barterProgress;
	this->gameProgress = gameProgress;

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
	return tools.at(idTool);
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
	return tools.at(idTool).available;
}

void GameStatus::setToolAvailable(int idTool, bool available)
{
	std::pair<int,ToolInfo> aux;
	aux.second = tools.at(idTool);
	aux.second.available = available;

	tools.insert(aux);
}

int GameStatus::getToolAmmoId(int idTool)
{
	return tools.at(idTool).idAmmo;
}

int GameStatus::getToolAmmoQuantity(int idTool)
{
	return tools.at(idTool).ammoQuantity;
}

void GameStatus::setToolAmmo(int idTool, int idAmmo)
{
	std::pair<int,ToolInfo> aux;
	aux.second = tools.at(idTool);
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
	aux.second = tools.at(idTool);
	aux.second.ammoQuantity = ammoQuantity;

	tools.insert(aux);
}

int GameStatus::getActualMoney()
{
	return actualMoney;
}

void GameStatus::setActualMoney(int actualMoney)
{
	this->actualMoney = actualMoney;
}

MapId GameStatus::getActualScreen()
{
	return actualScreen;
}

void GameStatus::setActualScreen(MapId acualtScreen)
{
	this->actualScreen = actualScreen;
}

//Devolvera un par con la ultima posición del jugador en la pantalla actual
std::pair<int,int> GameStatus::getLastPos()
{
	std::pair<int,int> aux;
	aux.first = actualScreen.mapX;
	aux.second = actualScreen.mapY;
	return aux;
}

void GameStatus::setLastPos(std::pair<int,int> lastPos)
{
	actualScreen.mapX = lastPos.first;
	actualScreen.mapY = lastPos.second;
}

int GameStatus::getNumPlayers()
{
	return numPlayers;
}

void GameStatus::setNumPlayers(int numPlayers)
{
	this->numPlayers = numPlayers;
}

int GameStatus::getNumPidgeons()
{
	return numPidgeons;
}

void GameStatus::setNumPidgeons(int numPidgeons)
{
	this->numPidgeons = numPidgeons;
}

int GameStatus::getHeartPieces()
{
	return numHeartPieces;
}
		
void GameStatus::setHeartPieces(int heartPieces)
{
	this->numHeartPieces = heartPieces;
}

int GameStatus::getMaxHeartPieces()
{
	return maxHeartPieces;
}

void GameStatus::setMaxHeartPieces(int maxHeartPieces)
{
	this->maxHeartPieces = maxHeartPieces;
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