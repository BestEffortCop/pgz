#pragma once
#ifndef __OVERWORLDMAPSTATE_H__
#define __OVERWORLDMAPSTATE_H__

#include <map>
#include "MapState.h"

class OverWorldMapState : public MapState
{
	public:

		//!Instancia el OverworldMapState
		OverWorldMapState();

		//!Instancia e inicializa el OverWorldMapState
		OverWorldMapState(std::map<int, bool> collectables,	std::map<int, bool> doors, std::map<int, bool> puzzles,	
						  std::map<int, bool> minibosses);

		//!Destruye la instancia del OverWorldMapState
		~OverWorldMapState();
};

#endif