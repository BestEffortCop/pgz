#include "Color.h"

Color::Color(unsigned char red, unsigned char green, unsigned char blue)
{ 
	r = red;
	g = green;
	b = blue;
};

const Color Color::Black = Color(0, 0, 0);
const Color Color::White = Color(255, 255, 255);
const Color Color::Red = Color(255, 0, 0);
const Color Color::Yellow = Color(255, 255, 0);
const Color Color::Green = Color(0, 255, 0);
const Color Color::Cyan = Color(0, 255, 255);
const Color Color::Blue = Color(0, 0, 255);
const Color Color::Magenta = Color(255, 0, 255);