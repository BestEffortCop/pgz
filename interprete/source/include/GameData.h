#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <vector>
#include "GameStatus.h"

// Almacena info invariable sobre el juego
// y guarda la clase que almacena la info variable
class GameData 
{
private:
	int neededHeartPieces;
	GameStatus* gameStatus;

public:
	GameData();
	~GameData();

	void init(int neededHeartPieces);

	int getNeededHeartPieces();
	void setNeededHeartPieces(int number);

	GameStatus* getGameStatus();
};
#endif
