#include "ScreenMap.h"

ScreenMap::ScreenMap(int width, int height, int tileW, int tileH, int x, int y, GfxEngine* gfxEngine) : Map(tileW, tileH, gfxEngine)
{
	//Llamo a la constructora de Map con los parametros que me pasan
	//Pongo los atributos de la clase al valor que me dan
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	//this->enemies = NULL;
}

ScreenMap::~ScreenMap()
{
	// Eliminamos lista de EnemySpawnData
	std::list<EnemySpawnData*>::iterator it = enemies.begin();
	while (it != enemies.end())
	{
		if ((*it) != NULL)
			delete (*it), (*it) = NULL;
		it++;
	};
};

vector<CollisionPair>* ScreenMap::checkColision(Entity* e)
{
	//Cojo el solidGrid de mi Map, y le pido que me de el par de colision con la entidad que me han pasado
	return this->solidGrid->collide(e->mask);
}

bool ScreenMap::isInBounds(Entity* e)
{
	//Cojo el solidGrid de mi Map y le pregunto si la entidad se encuentra dentro del mismo
	return this->solidGrid->isMaskInbounds(e->mask);
}

void ScreenMap::notify(ChangeType change, Entity* e)
{/*
	// Creamos un iterador para map
	map<int, bool>::iterator it;
	//Pido que busque el enemigo solicitado
	it = this->enemies->find(idEnemy);
	//Compruebo si está
	if (it == this->enemies->end())
        //Si no está hemos acabado
        return;
	else
		this->enemies->find(idEnemy)->second = false;*/

	switch (change) {
		case eNONE:
			break;
		case eMODIFY:
			break;
		case eCREATE:
			if (Enemy* enemy = dynamic_cast<Enemy*>(e))
			{
				EnemySpawnData * data = new EnemySpawnData();
				data->id = enemy->spawnData.id;
				data->x = enemy->spawnData.x;
				data->y = enemy->spawnData.y;

				enemies.push_back(data);
			}
			break;
		case eDESTROY:
			if (Enemy* enemy = dynamic_cast<Enemy*>(e))
			{
				bool found = false;
				list< EnemySpawnData * >::iterator it = enemies.begin();
				while ((it != enemies.end()) && !found)
				{
					if ((((*it)->id == enemy->spawnData.id) && ((*it)->x == enemy->spawnData.x)) && ((*it)->y == enemy->spawnData.y))
						found = true;
					else
						it++;
				}

				if (found)
				{
					EnemySpawnData * data = (*it);
					enemies.remove(*it);
					delete data;
				}
			}
			break;
	}
}

ScreenMapConstructor* ScreenMap::getConstructor()
{
	ScreenMapConstructor* s = new ScreenMapConstructor();
	s->zip(this);

	return s;
}

//Su funcion seria la de mantener actualizados los tiles animados, pero por ahora no hay
void ScreenMap::update(){};

//
void ScreenMap::render()
{
	//Avisa al tileMap de que se renderize
	//this->tileMap->render(x,y);
}

void ScreenMap::setCols(int cols){
	tileMap->setCols(cols);
}

void ScreenMap::setRows(int rows){
	tileMap->setRows(rows);
}

void ScreenMap::setScreenLocation(MapLocation screenLocation)
{
	this->screenLocation = screenLocation;
}

Direction ScreenMap::relative_position(Entity* p, bool & out)
{
	out = true;

	//Calculamos los vertices superior izquierdo e inferior derecho
	// Vértice superior izquierdo
	int x1 = p->mask->x + p->mask->xoffset;
	int y1 = p->mask->y + p->mask->yoffset;
	// Vértice inferior derecho
	int x2 = p->mask->x + p->mask->xoffset + p->mask->width;
	int y2 = p->mask->y + p->mask->yoffset + p->mask->height;

	if (x1 <= x) return LEFT;				// Se sale por la izquierda
	if (x2 >= x + width) return RIGHT;		// Se sale por la derecha
	if (y1 <= y) return UP;					// Se sale por la izquierda
	if (y2 >= y + height) return DOWN;		// Se sale por la izquierda

	out = false;
	return NONE;							// No se está saliendo
}


/*
void ScreenMap::setEnemies(vector<int>* entities)
{
	//Para cada id de enemigo que me pasan en el vector lo inserto en el map con un true
	vector<int>::iterator it;
	for (it = entities->begin(); it < entities->end(); it++)
		this->enemies->insert(make_pair(*it,true));
}


//Devuelvo el atributo enemies
map<int,bool>* ScreenMap::getEnemies(){return this->enemies;}

*/