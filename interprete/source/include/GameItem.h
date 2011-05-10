#pragma once
#ifndef __GAMEITEM__H__
#define __GAMEITEM__H__

#include "GameEntity.h"
#include "Stamp.h"

class GameItem : public GameEntity
{
public:
	// Tipos de efecto de items (modificar hp, modificar mp, modificar dinero...)
	enum ItemType { ieNONE, ieHP, ieMP, ieMONEY, ieKEY, ieMAXHP, ieMAXMP, ieBOSSKEY, ieKEYITEM, ieTOOL, iePIGEON };
protected:
	// Efecto del item
	ItemType effect;
	// Potencia del efecto
	int power;

	// Realiza la modificación de atributos pertinente en la entidad dada
	virtual void applyEffect(Entity* target);
public:
	GameItem(int x, int y, Game* g, GameState* gs);

	virtual void init(std::string gfxPath, ItemType t, int pow);

	virtual void onStep();
	virtual void onCollision(CollisionPair pair, Entity* other);
};

#endif