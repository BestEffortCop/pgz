#pragma once
#ifndef __TOOLSWORD_H__
#define __TOOLSWORD_H__

#include "Tool.h"

class ToolSword : public Tool
{
public:
	ToolSword(int x, int y, Game* game, GameState* world, string graphicPath);
	~ToolSword();

	void activate();
	
};
#endif