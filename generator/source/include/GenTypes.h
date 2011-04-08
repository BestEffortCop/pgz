#pragma once

#ifndef _GENTYPES_H_
#define _GENTYPES_H_

#include "GenMath.h"

using namespace std;

#define screenWidth 14
#define screenHeight 12
#define zoneSpacing 10  //se usa para mínima distancia entre los puntos de generación de zonas(en Voronoi)

typedef enum {Nothing, OWPortal, DUNPortal} EntType;

struct GenEntity
{
	EntType type; // Nos indica si es una entrada a mazmorra, un portal, (mas en un futuro)
	string dungeonPath; // archivo a cargar de mazmorra
	GPoint dest; // destino del portal

	GenEntity(){ type=OWPortal; dungeonPath=""; dest.x=0; dest.y=0;}
};

#endif
