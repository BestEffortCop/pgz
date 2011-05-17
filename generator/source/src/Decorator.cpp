#include "Decorator.h"

Decorator::Decorator(DBManager* db)
{
	this->db = db;
	theme = "";
	zone = "";
	autoTiler = NULL;
	terrainIdMatrix = NULL;
}

Decorator::~Decorator()
{
	if (autoTiler != NULL) delete autoTiler;

	clearDecorations();
}

void Decorator::init(string zone, string theme, short tileSetId)
{
	this->zone = zone;
	this->theme = theme;
	idTileset = tileSetId;
}

void Decorator::terrainsToTiles(Screen* screen)
{
	// Ahora se guarda en screen
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			autoTiler->getTerrain(terrainIdMatrix[i][j])->toTiles(terrainIdMatrix, screen, SCREEN_WIDTH, SCREEN_HEIGHT, i, j);
		}
	}
}

void Decorator::clearDecorations()
{
	// borramos las decoraciones que no hayan sido borradas
	list<Decoration*>::iterator it;
	for (it = decorationList.begin(); it != decorationList.end(); it++){
		if (*it != NULL) delete (*it);
	}

	decorationList.clear();
}

void Decorator::clearTerrains()
{
	if (terrainIdMatrix == NULL) return;

	for (int i = 0; i < SCREEN_WIDTH; i++)
		if (terrainIdMatrix[i] != NULL) delete (terrainIdMatrix[i]);

	delete (terrainIdMatrix);
}

short Decorator::gimmeTile() {
	// To be implemented
	return 0;
}

short Decorator::gimmeFloorButton() {
	return 0;
}

bool Decorator::isInBounds(Decoration* d, Screen* s)
{
	// comprobamos que no se salga de la pantalla
	if (d->x + d->getDecorationData().width > SCREEN_WIDTH || d->y + d->getDecorationData().height > SCREEN_HEIGHT)
		return false;
	else
		return true;
}

bool Decorator::checkDecoCollision(Decoration* d)
{
	// variables auxiliares para trabajar más cómodamente
	int itx, ity, itw, ith;
	int dw = d->getDecorationData().width;	// ancho de la decoración con la que se comprueba
	int dh = d->getDecorationData().height;	// alto de la decoración con la que se comprueba
	int dx = d->x;	
	int dy = d->y;

	// recorremos la lista de decoraciones para ver si colisiona con alguna
	list<Decoration*>::iterator it;
	for (it = decorationList.begin(); it != decorationList.end(); it++)
		if (*it != d) // si no es la propia decoración (que podría estar dentro de la lista)
		{
			// guardamos los valores de la decoración de la lista para trabajar más cómodamente
			itx = (*it)->x;
			ity = (*it)->y;
			itw = (*it)->getDecorationData().width;
			ith = (*it)->getDecorationData().height;
			
			// comprobamos colisión entre los cuadrados de las decoraciones
			if (dx + dw <= itx || dy + dh <= ity)
				continue;	// no colisionan y seguimos evaluando con otras decoraciones

			if (dx >= itx + itw || dy >= ity + ith)
				continue;	// no colisionan y seguimos evaluando con otras decoraciones

			// ha habido colisión
			return false;
		}
	// hemos recorrido toda la lista sin ninguna colisión
	return true;
}

bool Decorator::checkSolidCollision(Decoration* d, Screen* s){
	
	// Recocrremos la decoración
	for (int i = 0; i < d->getDecorationData().height; i++)
		for (int j = 0; j < d->getDecorationData().width; j++)
			// Si en la posición de la decoración hay algo que no sea libre devolvemos false
			if (s->getSolid(d->y + j, d->x + i) != 0)
				return false;
	return true;
}