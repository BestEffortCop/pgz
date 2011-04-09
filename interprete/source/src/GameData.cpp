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

void GameData::init(int maxHeartPieces)
{
	neededHeartPieces = maxHeartPieces;
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