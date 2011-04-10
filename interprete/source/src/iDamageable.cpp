#include "iDamageable.h"

//Inicializa los valores por defecto, vida 2 defensa 0 debilidad todo.
iDamageable::iDamageable()
{
	init(2, 2, 0, 0xf);
}

iDamageable::iDamageable(int hp, int maxHp, int defense, short typeWeakness)
{
	init(hp,maxHp,defense,typeWeakness);
}

iDamageable::~iDamageable()
{
};

void iDamageable::init(int hp, int maxHp, int defense, short typeWeakness)
{
	this->hp = hp;
	this->maxHp = maxHp;
	this->defense = defense;
	this->typeWeakness = typeWeakness;
}

/*Comprueba si la entidad que implementa la interfaz es debil a ese tipo de daño y en caso
  afirmativo realiza el daño, a continuación si la vida es <= 0 llama a onDeath y pone la 
  vida a 0*/
void iDamageable::onDamage(int damage, short damageType)
{
	short aux = typeWeakness & damageType;
	if (aux != 0x0)
	{
		if(damage - defense > 0)
			hp = hp - (damage - defense);
		if (hp <= 0)
		{
			hp = 0;
			onDeath();
		}
	}
}