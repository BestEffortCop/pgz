#pragma once

#ifndef __SCREENMAP_H__
#define __SCREENMAP_H__

#include "Map.h"
#include "Entity.h"
#include "HelperTypes.h"
#include <vector>

using namespace std;

class ScreenMap: public Map
{
private:

	vector<Entity*>* entidades;	//Vector de las entidades iniciales que contendrá la pantalla
	int width;					//Ancho de la pantalla
	int height;					//Alto de la pantalla
	int x;						//Coordenada x absoluta del ScreenMap
	int y;						//Coordenada y absoluta del ScreenMap

public:

	//Constructora parametrizada
	ScreenMap(int width, int height, int tileW, int tileH, int x, int y, GfxEngine* gfxEngine);
	
	//Destructora por defecto
	~ScreenMap();

	//Comprueba si la entidad que le pasan colisiona con su solidGrid
	vector<CollisionPair>* checkColision(Entity* e);

	//Comprueba si la entidad que le han pasado está dentro de los limites del mapa
	bool isInBounds(Entity* e);  

	//Actualiza su lista de entidades con la que le psan en la función
	void setEntities(vector<Entity*>* entidades);
	 
	//Función de actualización
	void update();

	//Función de pintado
	void render();

	//Devuelve la dirección del mapa por la que se está saliendo el player en caso
	//de que esté aún dentro de la pantalla devuelve NONE
	Dir relative_position(Entity* p);
};

#endif __SCREENMAP_H__