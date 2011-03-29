#pragma once

#ifndef __SCREENMAP_H__
#define __SCREENMAP_H__

#include <map>

#include "Map.h"
#include "Entity.h"
#include "HelperTypes.h"
#include <vector>

using namespace std;

class ScreenMap: public Map
{
private:

	map<int,bool>* enemies;		//Mapa de id de enemigos de la pantalla y si han de ser creados o no cuando se cargue la pantalla
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

	//Actualiza su lista de entidades con el vector de IDs de enemigo que le pasan
	void setEnemies(vector<int>* enemies);
	 
	//Decvuelve el map de enemigos y si han de ser o no creados
	map<int,bool>* getEnemies();

	//Actualiza el estado de un enemigo para indicar que no debe volver a ser creado
	void deadEnemy(int idEnemy);

	//Función de actualización
	void update();

	//Función de pintado
	void render();

	//Devuelve la dirección del mapa por la que se está saliendo el player en caso
	//de que esté aún dentro de la pantalla devuelve NONE
	Dir relative_position(Entity* p);

	void setRows(int row);

	void setCols(int col);
};

#endif __SCREENMAP_H__