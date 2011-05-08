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

void GameData::save(FILE* f){
	// Escribimos datos del game status
	this->gameStatus->save(f);
};

void GameData::load(FILE* f){
	gameStatus = new GameStatus();
	// Cargamos datos del game status
	gameStatus->load(f);
};