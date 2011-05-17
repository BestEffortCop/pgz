#include "ComponentTiledMovement.h"

ComponentTiledMovement::ComponentTiledMovement(Game* g, Controller* c) : Component()
{
	game = g;
	cont = c;
	tileW = 16;
	tileH = 16;
	locked = false;
};

ComponentTiledMovement::~ComponentTiledMovement()
{

};

void ComponentTiledMovement::initSettings(int tilew, int tileh, int speed)
{
	tileW = tilew;
	tileH = tileh;
	sp = speed;
};

int ComponentTiledMovement::getSpeed()
{
	return sp;
}

void ComponentTiledMovement::setSpeed(int speed)
{
	sp = speed;
}

void ComponentTiledMovement::onCInit(Enemy* e)
{
	locked = false;
	snapToGrid(e);
};

void ComponentTiledMovement::lock()
{
	locked = true;
};

void ComponentTiledMovement::unlock()
{
	locked = false;
};

bool ComponentTiledMovement::isLocked()
{
	return locked;
}

bool ComponentTiledMovement::isSnapped(Enemy* e)
{
	return (e->x % tileW == 0 && e->y % tileH == 0);
};

void ComponentTiledMovement::snapToGrid(Enemy* e)
{
	int modX = e->x % tileW;
	int modY = e->y % tileH;
	// Se alinea a la cuadrícula hacia arriba a la izda
	e->x -= modX;
	e->y -= modY;
	// Y si estaba más cerca de abajo o derecha, se ajusta
	if (modX >= tileW/2) e->x += tileW;
	if (modY >= tileH/2) e->y += tileH;
}

void ComponentTiledMovement::move(Direction d, Enemy* e)
{
	// Para moverse hay que estar alineado a la cuadrícula
	
	// Si está bloqueado y no está alienado, se está moviendo
	if (locked && !isSnapped(e))
		return;
	else if (!locked && !isSnapped(e))
		snapToGrid(e);

	// No está bloqueado, está alineado y quiere moverse
	targetX = e->x; targetY = e->y;
	switch (d)
	{
		case LEFT: targetX -= tileW; break;
		case RIGHT: targetX += tileW; break;
		case UP: targetY -= tileH; break;
		case DOWN: targetY += tileH; break;
		default: break;
	};

	// Si se sale, no moverse
	bool out = false;
	
	int tempX = e->mask->x, tempY = e->mask->y;
	e->mask->x = targetX; e->mask->y = targetY;
	cont->getScreenMap()->relative_position(e, out);
	e->mask->x = tempX;
	e->mask->y = tempY;

	if (!out)
	{
		e->mask->x = tempX;
		e->mask->y = tempY;

		Player* player;
		for (int i= 0; i<cont->getNumPlayers(); i++){
			player = cont->getPlayer(i);
			player->solid = false;
			player->collidable = false;
		}

		if ((targetX != e->x || targetY != e->y) && e->world->place_free(targetX, targetY, e))
		{
			originX = e->x;
			originY = e->y;
			once = false;
			lock();
		}

		for (int i= 0; i<cont->getNumPlayers(); i++){
			player = cont->getPlayer(i);
			player->solid = true;
			player->collidable = true;
		}
	}
};

void ComponentTiledMovement::goBack()
{
	// Sólo se puede regresar si está moviéndose
	if (locked && !once)
	{
		int tmpx, tmpy;
		tmpx = targetX;
		tmpy = targetY;
		targetX = originX;
		targetY = originY;
		originX = tmpx;
		originY = tmpy;
		once = true;
	};
};

void ComponentTiledMovement::onCStep(Enemy* e)
{
	if (!locked)
		return;

	// Si está bloqueado debe moverse hasta targetx, y
	if (targetX < e->x)
		e->x = max(e->x - sp, targetX);
	else if (targetX > e->x)
		e->x = min(e->x + sp, targetX);

	if (targetY < e->y)
		e->y = max(e->y - sp, targetY);
	else if (targetY > e->y)
		e->y = min(e->y + sp, targetY);

	if (targetX == e->x && targetY == e->y)
		snapToGrid(e), unlock(), once = false;
};