#pragma once

#ifndef _ZONEINFO_H_
#define _ZONEINFO_H_

#include <vector>
#include "GenZone.h"
#include "GenWormZone.h"
#include "DungeonInfo.h"
#include "SafeZoneInfo.h"

class ZoneInfo{
	private:
		string theme;
		string zone;
		int zoneNumber;  //esto no tiene mucho sentido, porque corresponde a la posición del vector + 1 (0 es frontera)
		vector<DungeonInfo>* dungeonsI;
		vector<SafeZoneInfo>* safeZonesI;
		GenZone* myGenZone;	// tipo de generador que se empleará
		short numEnemies;

	public:
		// Constructora
		ZoneInfo(string theme, string zone, int zoneNumber, GenZone* genZone, vector<DungeonInfo>* dungeons, vector<SafeZoneInfo>* safeZones, short numEnemies);
		// Destructora
		~ZoneInfo();
		// getter de genZone
		GenZone* getMyGenZone();
		short getNumEnemies();
		string getTheme();
		string getZone();

};

#endif