#include "DungeonMapStatus.h"

DungeonMapStatus::DungeonMapStatus() : MapStatus()
{
	bossDefeated = false;
	gotBossKey = false;
	gotCompass = false;
	gotMap = false;
	gotPowerUp = false;
}

void DungeonMapStatus::init(/*std::map<int, bool> collectables, std::map<int, bool> doors, std::map<int, bool> puzzles,	
							std::map<int, bool> minibosses, bool bossDefeated, bool gotBossKey, bool gotCompass, 
							bool gotMap, bool gotPowerUp*/)
{
	MapStatus::init();
	/*this->bossDefeated = bossDefeated;
	this->gotBossKey = gotBossKey;
	this->gotCompass = gotCompass;
	this->gotMap = gotMap;
	this->gotPowerUp = gotPowerUp;*/
}

bool DungeonMapStatus::isBossDefeated()
{
	return bossDefeated;
}
void DungeonMapStatus::setBossDefeated(bool bossDefeated)
{
	this->bossDefeated = bossDefeated;
}

bool DungeonMapStatus::isBossKeyGot()
{
	return gotBossKey;
}

void DungeonMapStatus::setBossKeyGot(bool gotBossKey)
{
	this->gotBossKey = gotBossKey;
}

bool DungeonMapStatus::isCompassGot()
{
	return gotCompass;
}

void DungeonMapStatus::setCompassGot(bool gotCompass)
{
	this->gotCompass = gotCompass;
}

bool DungeonMapStatus::isMapGot()
{
	return gotMap;
}

void DungeonMapStatus::setMapGot(bool gotMap)
{
	this->gotMap = gotMap;
}

bool DungeonMapStatus::isPowerUpGot()
{
	return gotPowerUp;
}

void DungeonMapStatus::setPowerUpGot(bool gotPowerUp)
{
	this->gotPowerUp = gotPowerUp;
}

void DungeonMapStatus::save(FILE* f){
	MapStatus::save(f);
	short* buffer = new short[5];
	// Escribimos los datos
	// Boss derrotado?
	buffer[0] = bossDefeated;
	// Llave de boss cogida?
	buffer[1] = gotBossKey;
	// Compás cogido?
	buffer[2] = gotCompass;
	// Mapa cogido?
	buffer[3] = gotMap;
	// PowerUp cogido?
	buffer[4] = gotPowerUp;

	fwrite(buffer, sizeof(short), 5, f);
	delete buffer; buffer = NULL;
}

void DungeonMapStatus::load(FILE* f){
	MapStatus::load(f);
	short buffer[5];
	fread(buffer, sizeof(short), 5 , f);
	// Cargamos los datos
	// Boss derrotado?
	bossDefeated = buffer[0];
	// Llave de boss cogida?
	gotBossKey = buffer[1];
	// Compás cogido?
	gotCompass = buffer[2];
	// Mapa cogido?
	gotMap = buffer[3];
	// PowerUp cogido?
	gotPowerUp = buffer[4];
}