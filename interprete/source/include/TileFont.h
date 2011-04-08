#pragma once

#ifndef __TILEFONT_H__
#define __TILEFONT_H__

#define NUM_CHAR 94

#include <map>

#include "Font.h"
#include "TileSet.h"


using namespace std;


class TileFont: public Font
{

private:
	map<int, int>* posicion;
	TileSet* tileSet;
public:

	TileFont(string path, GfxEngine* gfxEngine); 
	~TileFont();

	int getGlyphId(char c);
	TileSet* getTileSet();
	int getTileH();
	int getTileW();

};
#endif __TILEFONT_H__