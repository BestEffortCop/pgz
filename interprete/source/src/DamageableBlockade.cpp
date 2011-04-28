#include "DamageableBlockade.h"


DamageableBlockade::DamageableBlockade(int x, int y, Game* game, GameState* gameState):Entity(x,y,game,gameState)
{
}

void DamageableBlockade::init(short typeWeakness, Graphic* graphic, int xColision, int yColision)
{
	iDamageable::init(1,1,0,typeWeakness);
	this->graphic = graphic;
	this->mask = new MaskBox(x, y, xColision, yColision, "DamageableBlockade");
	this->solid = true;
}

void DamageableBlockade::onDeath()
{
	instance_destroy();
}

void DamageableBlockade::onCollision(CollisionPair other, Entity* e)
{
	if (other.b == "tool")
	{
		// Si algun arma nos colisiona nos hace daño
		onDamage(1, 0x1);
	}
}