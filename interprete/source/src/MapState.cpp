#include "MapState.h"

MapState::MapState(std::map<int, bool> collectables, std::map<int, bool> doors, std::map<int, bool> puzzles,	
									 std::map<int, bool> minibosses)
{
	init(collectables, doors, puzzles, minibosses);
}

void MapState::init(std::map< int, bool > collectables, std::map< int, bool > doors, std::map< int, bool > puzzles, std::map< int, bool > minibosses)
{
	std::map< int, bool >::iterator it = this->collectables.begin();
	std::map< int, bool >::iterator it2 = collectables.begin();
	bool tmp;
	while (it2 != collectables.end())
	{

		tmp = it->second;
		it++;
	}
}