#include "ZoneInfo.h"

ZoneInfo::ZoneInfo(string theme, string zone, int zoneNumber, GenZone* genZone, vector<DungeonInfo>* dungeons, vector<SafeZoneInfo>* safeZones, short numEnemies){
	this->theme = theme;
	this->zone = zone;
	this->zoneNumber = zoneNumber;
	myGenZone = genZone;
	dungeonsI = dungeons;
	safeZonesI = safeZones;
	this->numEnemies = numEnemies;
}

ZoneInfo::~ZoneInfo(){
	
	//dungeonsI->clear();
	delete dungeonsI;
	dungeonsI = NULL;

	//safeZonesI->clear();
	delete safeZonesI;
	safeZonesI = NULL;

	delete myGenZone;
	myGenZone = NULL;
}

//Getter & setters

GenZone* ZoneInfo::getMyGenZone(){
	return myGenZone;
}

short ZoneInfo::getNumEnemies()
{
	return numEnemies;
}

string ZoneInfo::getTheme()
{
	return theme;
}

string ZoneInfo::getZone()
{
	return zone;
}