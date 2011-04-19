#include "GameMenuStampItemS.h"


GameMenuStampItemS::GameMenuStampItemS(Stamp* s, int x, int y, Game* game, GameState* gstate) : GameMenuStampItem(s, x, y, game, gstate)
{
		iSelectable::iSelectable();
}


GameMenuStampItemS::~GameMenuStampItemS()
{
}
