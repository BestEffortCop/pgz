#pragma once

#ifndef __HELPER_TYPES_H__
#define __HELPER_TYPES_H__

enum Dir {UP, DOWN, LEFT, RIGHT,NONE};

// Representa la dirección de una posición
struct MapId
{
	// id del mapa
	int id;
	// coordenadas de la pantalla dentro del mapa
	int mapX;
	int mapY;
	// coordenadas de la entidad dentro de la pantalla
	int sX;
	int sY;
};

struct ToolInfo
{
	bool available;
	int idAmmo;
	int ammoQuantity;
};

#endif