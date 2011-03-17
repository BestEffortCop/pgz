#pragma once
#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__


class GameData
{
public:

	struct MapId{
	int id;
	int mapX;
	int mapY;
	};

	GameData(void);
	~GameData(void);


	MapId getMapId(){MapId m; return m;};
	bool hasScreen(MapId m){return true;};
	void setMapId(MapId m){};
};


#endif