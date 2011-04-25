#include "GameMenuItemS.h"


GameMenuItemS::GameMenuItemS(int x, int y, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate), iSelectable(x, y, 0, 0)
{

}

GameMenuItemS::GameMenuItemS(int x, int y, int w, int h, Game* game, GameState* gstate) : GameMenuItem(x, y, game, gstate), iSelectable(x, y, w, h)
{

}

GameMenuItemS::~GameMenuItemS()
{
}