#include "OverWorldMapState.h"

class DungeonState : public OverWorldMapState
{
	private:
		bool bossDefeated;
		bool gotBossKey;
		bool gotCompass;
		bool gotMap;
		bool gotPowerUp;
	public:
		DungeonState(map<int, bool>* collectables,	map<int, bool>* doors, map<int, bool>* puzzles,	
						  map<int, bool>* minibosses, bool bossDefeated, bool gotBossKey,
					 bool gotCompass, bool gotMap, bool gotPowerUp);

		~DunegonState();

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
}