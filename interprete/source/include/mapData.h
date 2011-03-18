#pragma once
#ifndef __MAPDATA_H__
#define __MAPDATA_H__


class MapData
{
public:

	GameData(void);
	~GameData(void);


	MapId getMapId(){MapId m; return m;};
	bool hasScreen(MapId m){return true;};
	void setMapId(MapId m){};
};

#endif