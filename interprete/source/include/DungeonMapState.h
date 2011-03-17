#pragma once
#ifndef __DUNGEONMAPSTATE_H__
#define __DUNGEONMAPSTATE_H__

#include "MapState.h"

class DungeonMapState : public MapState
{
	private:
		bool bossDefeated;
		bool gotBossKey;
		bool gotCompass;
		bool gotMap;
		bool gotPowerUp;

	public:
		DungeonMapState(std::map<int, bool> collectables,	std::map<int, bool> doors, std::map<int, bool> puzzles,	
						  std::map<int, bool> minibosses, bool bossDefeated, bool gotBossKey,
					 bool gotCompass, bool gotMap, bool gotPowerUp);

		~DungeonMapState();

		void init(bool bossDefeated, bool gotBossKey, bool gotCompass, bool gotMap, bool gotPowerUp);

		bool isBossDefeated();
		void setBossDefeated(bool bossDefeated);

		bool isGotBossKey();
		void setGotBossKey(bool gotBossKey);

		bool isGotCompass();
		void setGotCompass(bool gotCompass);

		bool isGotMap();
		void setGotMap(bool gotMap);

		bool isGotPowerUp();
		void isGotPowerUp(bool gotPowerUp);
};

#endif