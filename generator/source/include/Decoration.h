#pragma once

#ifndef _DECORATION_H_
#define _DECORATION_H_

#include <vector>
#include "Screen.h"

class Decoration
{
	public:

		enum DecorationSize {sNone, small, medium, big};
		enum DecorationType {tNone, solid, walkable, hangable};

		struct DecorationData
		{
			int idDeco;
			std::vector<int> compatibleTerrains; // id del terreno con el que puede ir (útil para hangables)
			int width, height;
			DecorationType type;
			DecorationSize size;
			std::vector<int> tileTypes;
			std::vector<int> tiles;
		};

	private:
		DecorationData data;	// datos de la decoración

	public:
		int x, y;	// posición (en tiles) de la decoración en la pantalla

		// Constructora
		Decoration(DecorationData data);
		void init(int x, int y);
		// Destructora
		virtual ~Decoration();

		// Método que devuelve las entidades (bueno no recuerdo bien, debe ser review by Rafa)
		std::vector<Entity*> toEntities();

		// Getter del data
		DecorationData getDecorationData();
};

#endif