#include "DunDecorator.h"

DunDecorator::DunDecorator(DBManager* db) : Decorator(db){}

DunDecorator::~DunDecorator(){}

void DunDecorator::init(string zone, short tileSetId){
	Decorator::init(zone, tileSetId);

	info.terrainId = -1;
	info.statueId = -1;
	info.torchId = -1;

	if (autoTiler != NULL) delete autoTiler; // si había un autotiler anterior lo borramos
	autoTiler = new DungeonAutoTiler(db->getPath("TileSet", tileSetId));	 // creamos el nuevo
}

void DunDecorator::decorate(Screen* screen){

	screen->setIdTileset(idTileset);

// Terrenos y muros
	place_terrains(screen);

// DECORACIONES ---------------------------------------------------------------------------------------------------------------

	// colocamos objetos en las paredes (antorchas o lo que toque)
	place_torchs(screen);

	// colocamos elementos pisables en cualquier sitio de la mazmorra
	place_walkables(screen);

	// colocamos las estatuas por la pantalla si es posible
	place_statues(screen);

	// Recorremos la lista de decoraciones conviertiéndolas en entidades (guardándolas en la screen)
	list<Decoration*>::iterator it;
	for (it = decorationList.begin(); it != decorationList.end(); it++)
		if (*it != NULL)
			screen->addEntity((*it)->toEntities());

	// Borramos la lista de decoraciones
	clearDecorations();

// Fin decoraciones ---------------------------------------------------------------------------------------------
}

void DunDecorator::place_terrains(Screen* screen){
	// TERRENOS ----------------------------------------------------------------------------------------------------------

	int terrainVar; // variación del terreno principal que puede aparecer en ciertas pantallas de la mazmorra

	// Cambiamos o mantenemos los terrenos con los que estamos decorando
	if (changedZone) // tenemos que cambiar de terrenos
	{
		info.wallId = ((DungeonAutoTiler*) autoTiler)->getTerrainId(Terrain::TerrainType::dungeonWall);
		info.terrainId = autoTiler->getTerrainId(Terrain::TerrainType::floor);
		changedZone = false;

	}
	else // cogemos una variación para el suelo
	{
		terrainVar = autoTiler->getVariation(info.terrainId, Terrain::TerrainType::floor);
		if (terrainVar != -1)	// si hay variaciones, intentamos variar el terreno principal
		{
			// damos un 33% de posibilidades de que se ponga la variación
			int r = rand() % 3;
			if (r == 0)
				info.terrainId = terrainVar;
		}
	}

	// colocación de los terrenos en la mazmorra
	terrainIdMatrix = (int**) malloc(sizeof(int*)*SCREEN_WIDTH);
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		terrainIdMatrix[i] = (int*) malloc(sizeof(int)*SCREEN_HEIGHT);
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			short type = screen->getSolid(i, j);
			if (type == 1)
				terrainIdMatrix[i][j] = info.wallId;
			else if (type != 25) // si no es un tile de entrada a mazmorra
				terrainIdMatrix[i][j] = info.terrainId;
		}
	}

	// Ahora se guarda en screen (los terrenos)
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			((DungeonAutoTiler*) autoTiler)->getTerrain(terrainIdMatrix[i][j])->toTiles(terrainIdMatrix, screen, SCREEN_WIDTH, SCREEN_HEIGHT, i, j);
		}
	}

	// colocamos suelo debajo de las entidades (muros) para cosas de perspectiva del player
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			if (screen->isThereAnyEntityAt(screen->getEntities(), j*SCREEN_WIDTH + i)){
				screen->setSolid(i, j, 0);
				((DungeonAutoTiler*) autoTiler)->getTerrain(info.terrainId)->toTiles(terrainIdMatrix, screen, SCREEN_WIDTH, SCREEN_HEIGHT, i, j);
			}
		}
	}

	// limpiamos la matriz de terrenos
	clearTerrains();
}

void DunDecorator::place_walkables(Screen* screen)
{
	int pos;
	// intentamos poner hasta NWALKABLES decoraciones
	for (int i = 0; i < NWALKABLES; i++)
	{
		// elegimos una posición al azar
		pos = rand() % (SCREEN_WIDTH * SCREEN_HEIGHT);
		// pedimos una decoración
		Decoration* d = autoTiler->getDecoration(Decoration::DecorationType::walkable, Decoration::DecorationSize::small,
			info.terrainId);
		// Si no existen decoraciones walkables-> salimos!!
		if (d == NULL)
			return;
		// Inicializamos la decoración
		d->init(pos % SCREEN_WIDTH, pos / SCREEN_HEIGHT);
		// La añadimos a la lista de decoraciones
		if (checkDecoCollision(d) && isInBounds(d, screen) && checkSolidCollision(d, screen) && checkWallCollision(d, screen))
			decorationList.push_back(d);
	}
}

void DunDecorator::place_statues(Screen* screen){

	int idStatue1, idStatue2;

	Decoration* decoStatueAux = autoTiler->getDecoration(Decoration::dungeonStatue, Decoration::small, info.terrainId);
	// si no existen estatuas...
	if (decoStatueAux == NULL)
		return;

	idStatue1 = decoStatueAux->getDecorationData().idDeco;
	delete decoStatueAux; decoStatueAux = NULL;

	decoStatueAux = autoTiler->getDecoration(Decoration::dungeonStatue, Decoration::small, info.terrainId);
	idStatue2 = decoStatueAux->getDecorationData().idDeco;
	delete decoStatueAux; decoStatueAux = NULL;

	// colocamos estatuas (o lo que toque) en las posiciones indicadas por el generador
	for (int i = 0; i < SCREEN_WIDTH; i++)	
		for (int j = 0; j < SCREEN_HEIGHT; j++){
			// Si leemos un sólido (ponemos estatua)
			if (screen->getSolid(i, j) == 2){	// Identificar que hay un solido (estatua)
				// cogemos una estatua diferente dependiendo de la simetría
				Decoration* decoStatue;
				if (i <= SCREEN_WIDTH / 2)
					decoStatue = autoTiler->getDecoration(idStatue1);
				else
					decoStatue = autoTiler->getDecoration(idStatue2);

				// Si no existen decoraciones walkables-> salimos!!
				if (decoStatue == NULL)
					return;
				// Inicializamos la decoración
				decoStatue->init(i, j - (decoStatue->getDecorationData().height - 1));
				// Cambiamos el sólido para que sea pasable por detrás
				screen->setSolid(i, j, 0);
				// La añadimos a la lista de decoraciones
				if (checkDecoCollision(decoStatue) && isInBounds(decoStatue, screen) && checkSolidCollision(decoStatue, screen))
					decorationList.push_back(decoStatue);
			}
		}
}

bool DunDecorator::checkWallCollision(Decoration* d, Screen* screen)
{
	int w =  d->getDecorationData().width;
	int h = d->getDecorationData().height;
	int x = d->x;
	int y = d->y;

	// miramos si chocamos con alguna entidad
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			if (screen->isThereAnyEntityAt(screen->getEntities(), (y + j) * SCREEN_WIDTH + x + i))
				return false;

	// no chocamos con ninguna entidad
	return true;
}

void DunDecorator::place_torchs(Screen* screen)
{
	int row;
	int col;

	// intentamos poner antorchas ARRIBA -----------------------------------------------

	// ponemos la de la izq.
	row = 1;
	col = SCREEN_WIDTH / 4;
	place_upperTorchs(screen, col, row);

	// ponemos la antorcha de la der.
	row = 1;
	col =  3 * (SCREEN_WIDTH / 4);
	place_upperTorchs(screen, col, row);

	// intentamos poner antorchas A LA IZQUIERDA ---------------------------------------------

	// ponemos la de la arriba
	row = SCREEN_HEIGHT / 4;
	col = 1;
	place_leftTorchs(screen, col, row);

	// ponemos la antorcha de la abajo
	row = 3 * (SCREEN_HEIGHT / 4);
	col = 1;
	place_leftTorchs(screen, col, row);

	// intentamos poner antorchas A LA DERECHA -----------------------------------------------

	// ponemos la de la arriba
	row = SCREEN_HEIGHT / 4;
	col = SCREEN_WIDTH - 2;
	place_rightTorchs(screen, col, row);

	// ponemos la antorcha de la abajo
	row = 3 * (SCREEN_HEIGHT / 4);
	col = SCREEN_WIDTH - 2;
	place_rightTorchs(screen, col, row);
}

bool DunDecorator::place_upperTorchs(Screen* screen, int col, int row)
{
	bool placed = false;
	// intentamos ponerla en las dos primeras filas
	while (!placed && row < 3)
	{
		if (!(placed = place_upperTorch(screen, col, row)))
			// si no lo conseguimos probamos una posición más a la izq.
			if (!(placed = place_upperTorch(screen, col -1, row)))
				// si no lo conseguimos probamos una más a la der.
				placed = place_upperTorch(screen, col +1, row);
		row++;
	}
	return placed;
}

bool DunDecorator::place_upperTorch(Screen* screen, int col, int row)
{
	if (screen->getSolid(col, row) == 1 && screen->getSolid(col, row + 1) != 1 
		&& screen->getSolid(col - 1, row) == 1 && screen->getSolid(col + 1, row) == 1)
	{
		Decoration* decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonDeco(DunDecorationPos::top, info.wallId, Decoration::DecorationType::hangable);
		if (decoTorch != NULL)
		{
			// Inicializamos la decoración
			decoTorch->init(col, row);
			// La añadimos a la lista de decoraciones
			decorationList.push_back(decoTorch);
			return true;
		}
	}

	// si algo ha salido mal
	return false;
}

bool DunDecorator::place_leftTorchs(Screen* screen, int col, int row)
{
	bool placed = false;
	// intentamos ponerla en las dos primeras columnas
	while (!placed && col < 3)
	{
		if (!(placed = place_siderTorch(screen, col, row, DunDecorationPos::left)))
			// si no lo conseguimos probamos una posición más a la izq.
			if (!(placed = place_siderTorch(screen, col, row -1, DunDecorationPos::left)))
				// si no lo conseguimos probamos una más a la der.
				placed = place_siderTorch(screen, col, row +1, DunDecorationPos::left);
		col++;
	}
	return placed;
}

bool DunDecorator::place_rightTorchs(Screen* screen, int col, int row)
{
	bool placed = false;
	while (!placed && col > SCREEN_WIDTH - 4)
	{
		if (!(placed = place_siderTorch(screen, col, row, DunDecorationPos::right)))
			// si no lo conseguimos probamos una posición más a la izq.
			if (!(placed = place_siderTorch(screen, col, row -1, DunDecorationPos::right)))
				// si no lo conseguimos probamos una más a la der.
				placed = place_siderTorch(screen, col, row +1, DunDecorationPos::right);
		col--;
	}
	return placed;
}

bool DunDecorator::place_siderTorch(Screen* screen, int col, int row, DunDecorationPos pos)
{
	// comprobamos que tanto el tile de arriba como el de abajo sean paredes
	if (screen->getSolid(col, row) == 1	&& screen->getSolid(col, row - 1) == 1 && screen->getSolid(col, row + 1) == 1)
		// En función de si es izq. o der. comprobamos que estamos en una pared y no dentro del muro
		if ((pos == DunDecorationPos::left && screen->getSolid(col + 1, row) != 1 && (!screen->isThereAnyEntityAt(screen->getEntities(), row * SCREEN_WIDTH + col+1)))
			 || (pos == DunDecorationPos::right && screen->getSolid(col - 1, row) != 1 && (!screen->isThereAnyEntityAt(screen->getEntities(), row * SCREEN_WIDTH + col-1))))
		{
			Decoration* decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonDeco(pos, info.wallId, Decoration::DecorationType::hangable);
			if (decoTorch != NULL)
			{
				// Inicializamos la decoración
				decoTorch->init(col, row);
				// La añadimos a la lista de decoraciones
				decorationList.push_back(decoTorch);
				return true;
			}
		}

	// si algo ha salido mal
	return false;
}

void DunDecorator::decorateDunEntrance(Screen* screen, int col, int row)
{
	DunDecorationPos pos;
	int colFloor = col;		// columna donde irá la decoración de suelo de entrada
	int rowFloor = row;		// fila donde irá la decoración de suelo de entrada
	
	// miramos cuál es la posición en la que hay que poner la entrada
	if (col == 0)
	{
		row--;
		pos = DunDecorationPos::left;
	}
	else if (col == SCREEN_WIDTH - 2)
	{
		row--;
		pos = DunDecorationPos::right;
	}
	else if (row == 0)
	{
		col--;
		pos = DunDecorationPos::top;
	}
	else if (row == SCREEN_HEIGHT - 2)
	{
		col--;
		pos = DunDecorationPos::bottom;
	}
	else // algo ha fallado
		return;

	// Cogemos una decoración de entrada en función de la posición que nos pasen
	Decoration* decoEntrance = ((DungeonAutoTiler*) autoTiler)->getDungeonDeco(pos, info.wallId, Decoration::DecorationType::dungeonEntrance);

	// Cogemos una decoración de suelo entrada en función de la posición que nos pasen
	Decoration* decoFloor = ((DungeonAutoTiler*) autoTiler)->getDungeonDeco(pos, info.wallId, Decoration::DecorationType::dunFloorEntrance);

	if (decoEntrance == NULL || decoFloor == NULL)
		return;

	// colocamos las decoraciones
	decoEntrance->init(col, row);
	decoFloor->init(colFloor, rowFloor);

	// las metemos en la lista (no comprobamos que choque...)
	decorationList.push_back(decoFloor);
	decorationList.push_back(decoEntrance);
}

void DunDecorator::decorateLS(Screen* screen){
	
	screen->setIdTileset(idTileset);
	
	// Este tile está en sólido no sé por qué
	screen->setSolid(6, 10, 0);
	screen->setSolid(7, 10, 0);

// Terrenos y muros
	place_terrains(screen);

// Decoraciones 

	// Puerta de abajo
	Decoration* decoEntrance = autoTiler->getDecoration(7);
	// si no existen puertas...
	if (decoEntrance == NULL)
		return;
	// Inicializamos la decoración
	decoEntrance->init(5, 10);
	decorationList.push_back(decoEntrance);

	// colocamos objetos en las paredes (antorchas o lo que toque)
	place_torchs(screen);

	// Estatua Izquierda
	Decoration* decoLeft = autoTiler->getDecoration(22);
	// si no existen estatuas...
	if (decoLeft == NULL)
		return;
	// Inicializamos la decoración
	decoLeft->init(3, 4);
	// La añadimos a la lista de decoraciones
	//if (checkDecoCollision(decoLeft) && isInBounds(decoLeft, screen) && checkSolidCollision(decoLeft, screen))
	decorationList.push_back(decoLeft);


	// Estatua derecha
	Decoration* decoRight = autoTiler->getDecoration(23);
	// si no existen estatuas...
	if (decoRight == NULL)
		return;
	// Inicializamos la decoración
	decoRight->init(8, 4);
	// La añadimos a la lista de decoraciones
	//if (checkDecoCollision(decoRight) && isInBounds(decoRight, screen) && checkSolidCollision(decoRight, screen))
	decorationList.push_back(decoRight);


	// Metemos el portón
	Decoration* decoDoor = autoTiler->getDecoration(8);
	/*short* buffer = new short[autoTiler->getDecoration(8)->getDecorationData().tileTypes.size()];
	for (int i = 0; i < (int)autoTiler->getDecoration(8)->getDecorationData().tileTypes.size(); i++)
		buffer[i] = autoTiler->getDecoration(8)->getDecorationData().tileTypes.at(i);

	screen->addEntity(new EntityFinalDoor(FINAL_DOOR, 5, 0, -1, -1, autoTiler->getDecoration(8)->getDecorationData().tiles.size(), autoTiler->getDecoration(8)->getDecorationData().tiles.at(0), buffer, autoTiler->getDecoration(8)->getDecorationData().width)); */
	
	// si no existen estatuas...
	if (decoDoor == NULL)
		return;
	// Inicializamos la decoración
	decoDoor->init(6, 0);
	// La añadimos a la lista de decoraciones
	//if (checkDecoCollision(decoDoor) && isInBounds(decoDoor, screen) && checkSolidCollision(decoDoor, screen))
	decorationList.push_back(decoDoor);

	// Alfombra
	for (int i = 2; i < 15; i++){
		// Colocamos la alfombra
		Decoration* decoCarpet = autoTiler->getDecoration(6);
		// Si no existen alfombras...
		if (decoCarpet == NULL)
			return;
		// Inicializamos y añadimos a la lista todas las decoraciones
		decoCarpet->init(6, i);
		decorationList.push_back(decoCarpet);
	}
	
	
	// Recorremos la lista de decoraciones conviertiéndolas en entidades (guardándolas en la screen)
	list<Decoration*>::iterator it;
	for (it = decorationList.begin(); it != decorationList.end(); it++)
		if (*it != NULL)
			screen->addEntity((*it)->toEntities());

	// Borramos la lista de decoraciones
	clearDecorations();
}

void DunDecorator::decorateFS(Screen* screen){

	screen->setIdTileset(idTileset);

	// Terrenos y muros
	place_terrains(screen);

	// Decoraciones 
	
	// Puerta de abajo
	Decoration* decoEntrance = autoTiler->getDecoration(7);
	// si no existen puertas...
	if (decoEntrance == NULL)
		return;
	// Inicializamos la decoración
	decoEntrance->init(5, 10);
	// La añadimos a la lista de decoraciones
	decorationList.push_back(decoEntrance);

	// Colocamos las banderas
	Decoration* decoFlagL = autoTiler->getDecoration(12);
	Decoration* decoFlagR = autoTiler->getDecoration(13);
	// Si no existen banderas...
	if (decoFlagL == NULL | decoFlagR == NULL)
		return;
	// Inicializamos las decoraciones
	decoFlagL->init(4, 1);
	decoFlagR->init(9, 1);
	// Las añadimos a la lista de decoraciones
	decorationList.push_back(decoFlagL);
	decorationList.push_back(decoFlagR);

	// colocamos objetos en las paredes (antorchas o lo que toque)
	place_torchsFS(screen);

	// Colocamos la plataforma
	place_Stage(screen);

	// Alfombra
	for (int i = 2; i < 15; i++){
		// Colocamos la alfombra
		Decoration* decoCarpet;
		if (i == 4) decoCarpet = autoTiler->getDecoration(5);
		else decoCarpet = autoTiler->getDecoration(6);
		// Si no existen alfombras...
		if (decoCarpet == NULL)
			return;
		// Inicializamos y añadimos a la lista todas las decoraciones
		decoCarpet->init(6, i);
		decorationList.push_back(decoCarpet);
	}

	// Colocamos las 6 estatuas
	place_FinalStatues(screen);

	// Colocamos el altar
	Decoration* decoAltar = autoTiler->getDecoration(11);
	// si no existen altares...
	if (decoAltar == NULL)
		return;
	// Inicializamos la decoración
	decoAltar->init(6, 1);
	// La añadimos a la lista de decoraciones
	decorationList.push_back(decoAltar);

	// Recorremos la lista de decoraciones conviertiéndolas en entidades (guardándolas en la screen)
	list<Decoration*>::iterator it;
	for (it = decorationList.begin(); it != decorationList.end(); it++)
		if (*it != NULL)
			screen->addEntity((*it)->toEntities());

	// Borramos la lista de decoraciones
	clearDecorations();
}

void DunDecorator::place_FinalStatues(Screen* screen){
	// Estatua Arriba-Izquierda
	Decoration* decoTopLeft = autoTiler->getDecoration(9);
	// si no existen estatuas...
	if (decoTopLeft == NULL)
		return;
	// Inicializamos la decoración
	decoTopLeft->init(3, 4);
	// La añadimos a la lista de decoraciones
	decorationList.push_back(decoTopLeft);

	// Estatua Arriba-Derecha
	Decoration* decoTopRight = autoTiler->getDecoration(9);
	// si no existen estatuas...
	if (decoTopRight == NULL)
		return;
	// Inicializamos la decoración
	decoTopRight->init(10, 4);
	// La añadimos a la lista de decoraciones
	decorationList.push_back(decoTopRight);

	// Estatua Medio-Izquierda
	Decoration* decoMidLeft = autoTiler->getDecoration(9);
	// si no existen estatuas...
	if (decoMidLeft == NULL)
		return;
	// Inicializamos la decoración
	decoMidLeft->init(5, 6);
	// La añadimos a la lista de decoraciones
	decorationList.push_back(decoMidLeft);

	// Estatua Medio-Derecha
	Decoration* decoMidRight = autoTiler->getDecoration(9);
	// si no existen estatuas...
	if (decoMidRight == NULL)
		return;
	// Inicializamos la decoración
	decoMidRight->init(8, 6);
	// La añadimos a la lista de decoraciones
	decorationList.push_back(decoMidRight);

	// Estatua Abajo-Izquierda
	Decoration* decoBotLeft = autoTiler->getDecoration(9);
	// si no existen estatuas...
	if (decoBotLeft == NULL)
		return;
	// Inicializamos la decoración
	decoBotLeft->init(3, 7);
	// La añadimos a la lista de decoraciones
	decorationList.push_back(decoBotLeft);

	// Estatua Abajo-Derecha
	Decoration* decoBotRight = autoTiler->getDecoration(9);
	// si no existen estatuas...
	if (decoBotRight == NULL)
		return;
	// Inicializamos la decoración
	decoBotRight->init(10, 7);
	// La añadimos a la lista de decoraciones
	decorationList.push_back(decoBotRight);
}

void DunDecorator::place_Stage(Screen* screen){

	Decoration* decoStage = autoTiler->getDecoration(14);
	// Si no existen plataformas...
	if (decoStage == NULL)
		return;
	// Inicializamos y añadimos a la lista todas las decoraciones
	decoStage->init(3, 2);
	decorationList.push_back(decoStage);

	for (int i = 4; i < 10; i++){
		decoStage = autoTiler->getDecoration(19);
		// Si no existen plataformas...
		if (decoStage == NULL)
			return;
		// Inicializamos y añadimos a la lista todas las decoraciones
		decoStage->init(i, 2);
		decorationList.push_back(decoStage);
	}

	decoStage = autoTiler->getDecoration(15);
	// Si no existen plataformas...
	if (decoStage == NULL)
		return;
	// Inicializamos y añadimos a la lista todas las decoraciones
	decoStage->init(10, 2);
	decorationList.push_back(decoStage);
	

	decoStage = autoTiler->getDecoration(16);
	// Si no existen plataformas...
	if (decoStage == NULL)
		return;
	// Inicializamos y añadimos a la lista todas las decoraciones
	decoStage->init(3, 3);
	decorationList.push_back(decoStage);

	decoStage = autoTiler->getDecoration(20);
	// Si no existen plataformas...
	if (decoStage == NULL)
		return;
	// Inicializamos y añadimos a la lista todas las decoraciones
	decoStage->init(4, 3);
	decorationList.push_back(decoStage);

	for (int i = 5; i < 9; i++){
		decoStage = autoTiler->getDecoration(19);
		// Si no existen plataformas...
		if (decoStage == NULL)
			return;
		// Inicializamos y añadimos a la lista todas las decoraciones
		decoStage->init(i, 3);
		decorationList.push_back(decoStage);
	}

	decoStage = autoTiler->getDecoration(21);
	// Si no existen plataformas...
	if (decoStage == NULL)
		return;
	// Inicializamos y añadimos a la lista todas las decoraciones
	decoStage->init(9, 3);
	decorationList.push_back(decoStage);

	decoStage = autoTiler->getDecoration(17);
	// Si no existen plataformas...
	if (decoStage == NULL)
		return;
	// Inicializamos y añadimos a la lista todas las decoraciones
	decoStage->init(10, 3);
	decorationList.push_back(decoStage);


	decoStage = autoTiler->getDecoration(16);
	// Si no existen plataformas...
	if (decoStage == NULL)
		return;
	// Inicializamos y añadimos a la lista todas las decoraciones
	decoStage->init(4, 4);
	decorationList.push_back(decoStage);

	for (int i = 5; i < 9; i++){
		decoStage = autoTiler->getDecoration(18);
		// Si no existen plataformas...
		if (decoStage == NULL)
			return;
		// Inicializamos y añadimos a la lista todas las decoraciones
		decoStage->init(i, 4);
		decorationList.push_back(decoStage);
	}

	decoStage = autoTiler->getDecoration(17);
	// Si no existen plataformas...
	if (decoStage == NULL)
		return;
	// Inicializamos y añadimos a la lista todas las decoraciones
	decoStage->init(9, 4);
	decorationList.push_back(decoStage);
}

void DunDecorator::place_torchsFS(Screen* screen){

	// Ponemos las de arriba
	Decoration* decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonDeco(DunDecorationPos::top, info.wallId, Decoration::DecorationType::hangable);
	if (decoTorch != NULL)
	{
		// Inicializamos la decoración izq
		decoTorch->init(3, 1);
		// La añadimos a la lista de decoraciones
		decorationList.push_back(decoTorch);

		decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonDeco(DunDecorationPos::top, info.wallId, Decoration::DecorationType::hangable);
		// Inicializamos la decoración izq
		decoTorch->init(10, 1);
		// La añadimos a la lista de decoraciones
		decorationList.push_back(decoTorch);
	}

	// Ponemos las de la izquierda
	decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonDeco(DunDecorationPos::left, info.wallId, Decoration::DecorationType::hangable);
	if (decoTorch != NULL)
	{
		// Inicializamos la decoración izq
		decoTorch->init(1, 3);
		// La añadimos a la lista de decoraciones
		decorationList.push_back(decoTorch);

		decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonDeco(DunDecorationPos::left, info.wallId, Decoration::DecorationType::hangable);
		// Inicializamos la decoración izq
		decoTorch->init(1, 8);
		// La añadimos a la lista de decoraciones
		decorationList.push_back(decoTorch);
	}

	// Ponemos las de la derecha
	decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonDeco(DunDecorationPos::right, info.wallId, Decoration::DecorationType::hangable);
	if (decoTorch != NULL)
	{
		// Inicializamos la decoración izq
		decoTorch->init(12, 3);
		// La añadimos a la lista de decoraciones
		decorationList.push_back(decoTorch);

		decoTorch = ((DungeonAutoTiler*) autoTiler)->getDungeonDeco(DunDecorationPos::right, info.wallId, Decoration::DecorationType::hangable);
		// Inicializamos la decoración izq
		decoTorch->init(12, 8);
		// La añadimos a la lista de decoraciones
		decorationList.push_back(decoTorch);
	}
}