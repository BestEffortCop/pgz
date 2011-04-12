#pragma once
#ifndef __TOOLSWORD_H__
#define __TOOLSWORD_H__

#include "Tool.h"
#include "SpriteMap.h"

class ToolSword : public Tool
{
public:
	ToolSword(int x, int y, Game* game, GameState* world);
	~ToolSword();

	void init(bool passive, Player* p, string graphicpath, int ncol, int nrow);
	void activate();
	
};
#endif