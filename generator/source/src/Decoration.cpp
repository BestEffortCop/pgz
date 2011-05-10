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

Entity* Decoration::toEntities()
{
	std::vector<int>::iterator itTile, itType;

	if (data.tiles.size() != data.tileTypes.size())
		return NULL;	// error al cargar no coinciden el nº de tiles con sus tipos

	// creamos los vectores para la entidad tileEntity
	short* tiles = new short[data.tiles.size()];
	short* tilesType = new short[data.tileTypes.size()];

	// iniciamos los iteradores
	itTile = data.tiles.begin();
	itType = data.tileTypes.begin();

	int i = 0;

	while (itTile != data.tiles.end())
	{
		// cogemos cada tile y lo metemos en el vector
		tiles[i] = (*itTile);

		// cogemos el tipo de cada tile y lo metemos en el vector
		tilesType[i] = (*itType);

		itTile++;
		itType++;
		i++;
	}
			
	// Creamos la entidad y la metemos en el vector
	// -1 -1 indican que no tienen idCollectable ni linkedTo
	return new EntityTiled(entityType::TILEDENTITY, x , y, -1, -1, data.tiles.size(), tiles, tilesType, data.width);
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
	}*/
};

Decoration::DecorationData Decoration::getDecorationData()
{
	return data;
};