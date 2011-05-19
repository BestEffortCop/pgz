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