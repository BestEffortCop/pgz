#pragma once

#ifndef _DECORATION_H_
#define _DECORATION_H_

#include <vector>

class Decoration
{
	public:

		enum DecorationSize {sNone, small, medium, big};
		enum DecorationType {tNone, solid, walkable, hangable};

		struct TiledEntity
		{
			int x, y;
			int idTile;
			bool solid;
		};

		struct DecorationData
		{
			int idDeco;
			std::vector<int> compatibleTerrains; // id del terreno con el que puede ir (útil para hangables)
			int width, height;
			DecorationType type;
			DecorationSize size;
			std::vector<int> solids;
			std::vector<int> tiles;
		};

	private:
		
		int x, y;
		DecorationData data;

	public:
		// Constructora
		Decoration(DecorationData data);
		void init(int x, int y);
		// Destructora
		virtual ~Decoration();

		// Método que devuelve las entidades (bueno no recuerdo bien, debe ser review by Rafa)
		std::vector<TiledEntity> toEntities();		// Devolvemos solo el id de las entidades o la entidad completa?
};

#endif