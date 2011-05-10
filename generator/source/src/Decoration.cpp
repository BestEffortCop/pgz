#include "Decoration.h"

Decoration::Decoration(DecorationData data)
{
	this->data = data;
};

Decoration::~Decoration()
{
	this->x = -1;
	this->y = -1;
};

void Decoration::init(int x, int y)
{
	this->x = x;
	this->y = y;
};

std::vector<Entity*> Decoration::toEntities()
{
	std::vector<Entity*> v;
	std::vector<int>::iterator itTile, itType;
	short solid;

	if (data.tiles.size() != data.tileTypes.size())
		return v;	// error al cargar no coinciden el nº de tiles con sus tipos

	// iniciamos los iteradores
	itTile = data.tiles.begin();
	itType = data.tileTypes.begin();

	for (int i = 0; i < data.height; i++)
		for (int j = 0; j < data.width; j++)
		{
			// Diferenciamos si es sólido o no para el motor (type = 1 es base, es decir, solido)
			if ((*itType) != 1) solid = 0; 
			else solid = 1;
			// Creamos la entidad y la metemos en el vector
			// -1 -1 indican que no tienen idCollectable ni linkedTo
			EntityTiled* e = new EntityTiled(entityType::TILEDENTITY, x + j, y + i, -1, -1, (*itTile), solid);
			v.push_back(e);

			itTile++;
			itType++;
		}

/*
	// para cada tile comprobamos el tipo y creamos la entidad que corresponda
	while (itTile != data.tiles.end())
	{
		// Diferenciamos si es sólido o no para el motor (type = 1 es base, es decir, solido)
		if ((*itType) != 1) solid = 0; 
		else solid = 1;
		// Creamos la entidad y la metemos en el vector
		// -1 -1 indican que no tienen idCollectable ni linkedTo
		EntityTiled* e = new EntityTiled(entityType::TILEDENTITY, x, y, -1, -1, (*itTile), solid);
		v.push_back(e);

		itTile++;
		itType++;
	}

*/	return v;
};

Decoration::DecorationData Decoration::getDecorationData()
{
	return data;
};