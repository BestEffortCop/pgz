#pragma once

#ifndef __FONT_H__
#define __FONT_H__

#include "Image.h"

using namespace std;


class Font
{
public:

	Font();								//No hace ná
	int getGlyphId(char c);             //La implementará TileFont
	Image* getGlyphImage(char c);       //La implementará la posible Ttf font

};
#endif __FONT_H__