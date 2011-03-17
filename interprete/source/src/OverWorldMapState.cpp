#include "OverWorldMapState.h"

OverWorldMapState::OverWorldMapState(std::map<int, bool> collectables, std::map<int, bool> doors, std::map<int, bool> puzzles,	
									 std::map<int, bool> minibosses)
									 : MapState(collectables, doors, puzzles, minibosses)
{
}