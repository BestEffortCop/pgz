#include "controller.h"

#include "CollisionTester.h"

Controller::Controller(Game* g)
{
	// Almacena los parámetros necesarios
	game = g;
	//width = game->getGameConfig()->gameWidth;
	width = 224;
	//height = game->getGameConfig()->gameHeight;
	height = 192;

	// Crea las imágenes que usará para el cambio de posición del mapa
	currentRoom = new Image(width, height, game->getGfxEngine(), false, true);
	nextRoom = new Image(width, height, game->getGfxEngine(), false, true);

	screenMap = NULL;

	// Crea Data
	data = new DataPersistence();
	gamePlayState = NULL;
	dbi = new DataBaseInterface();
	state = NORMAL;

	entityReader = NULL;
}
	
Controller::~Controller()
{
	if (hudController != NULL)
		delete hudController, hudController = NULL;
	if (toolController != NULL)
		delete toolController, toolController = NULL;
	if (eventController != NULL)
		delete eventController, eventController = NULL;
	
	if (dbi != NULL)
		delete dbi, dbi = NULL;
	if (entityReader != NULL)
		delete entityReader, entityReader = NULL;

	if (data != NULL)
		delete data, data = NULL;

	if (currentRoom != NULL)
		delete currentRoom, currentRoom = NULL;
	if (nextRoom != NULL)
		delete nextRoom, nextRoom = NULL;

	for (int i = 0; i < numPlayers; i++)
		if (players[i] != NULL)
			delete players[i], players[i] = NULL;
}
	


bool Controller::initData(std::string path)
{
	// Se obtienen punteros a DataPersistence para facilitar el trabajo
	GameData* gdata = data->getGameData();
	GameStatus* gstatus = gdata->getGameStatus();

	// Se obtienen el número de players (debe venir de algún sitio del PGZGame [r1])
	numPlayers = 1; // Default

	/* ** Se inician los datos de los mapas ** */
	
	// Variables temporales
	int numMaps, mapId, w, h, numPuzzles, numDoors, numMinibosses, numCollectables;
	char type;
	int** layout;

	// Se carga el número de mapas ¿de la DBI? [r2]
	numMaps = 1; // Default

	// Se cargan todas las cabeceras de los mapas preparando los datos
	for (int i = 0; i < numMaps; i++)
	{
		mapId = i;
		// Se carga de archivo
		// Archivo
		FILE* file = NULL;

		// Primero, se prepara el nombre del archivo a cargar
		// Buffer para convertir ints a chars
		char buf[5];
		// Nombre de archivo a cargar
		std::string fname = "";
		
		// Formato "h<idMap>
		// Se prepara
		// Primero, la ruta de datos (changeable)
		fname.append("data/map/");
		fname.append("m");
		fname.append(itoa(i, buf, 10));
		fname.append("h");

		// Se abre el archivo para lectura
		file = fopen(fname.c_str(), "r");

		if (file == NULL)
			return false; // Fail, abortar, returnear

		// Comenzamos

		// 0. Tipo de mapa (0 - overworld, 1 - dungeon)
		short* tipo = (short*) malloc(sizeof(short));
		if (fread(tipo, sizeof(tipo), 1, file) < 1)
			return false; // fallar, avisar, volver

		// Se almacena el tipo de mapa
		type = (char) *tipo;

		// Se libera el buffer
		free(tipo);

		// 1. Ancho y alto en pantallas del mapa
		// Buffer para el ancho, alto
		short whBuf[2];
		// Se lee 
		if (fread(whBuf, sizeof(whBuf), 1, file) < 1)
			return false; // Fail, abortar, returnear

		// Se almacena el ancho y alto
		w = whBuf[0];
		h = whBuf[1];
	
		// 2. Se carga el layout

		// Se reserva memoria para el layout
		// [r3] No creo que necesitemos int para el layout, short o algo vale
		// [Extra] Por ahora se guardan bools, meh
		
		// buffer layout
		bool** lbuf = new bool*[w];
		for (int i = 0; i < w; i++)
			lbuf[i] = new bool[h];

		// Se lee el layout entero por filas
		for (int i = 0; i < w; i++)
		{
			if (fread(lbuf[i], sizeof(lbuf[i]), 1, file) < 1)
				return false; // fallar, avisar, salir
		}

		// Se reserva memoria para el layout
		layout = (int**) malloc(sizeof(int*)*w);
		for (int i = 0; i < w; i++)
			layout[i] = (int*) malloc(sizeof(int)*h);

		// Se prepara el layout y se almacenan los datos
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				if (lbuf[i][j])
					layout[i][j] = 1;
				else layout[i][j] = 0;
			}
		}

		// Se libera el buffer
		for (int i = 0; i < w; i++) 
		{
			delete lbuf[i];
			lbuf[i] = NULL;
		}
		delete lbuf; lbuf = NULL;

		// 3. Se carga la pantalla inicial de la mazmorra
		// Buffer de almacenamiento
		short initScreen[2];

		// Se lee de archivo
		if (fread(initScreen, sizeof(initScreen), 1, file) < 1)
			return false; // Fallor, avisar, volver

		// Se almacena la info más tarde

		// Se carga de archivo el nº de puzzles, puertas, minibosses y collectables
		// Buffers
		short persistentItemBuffer[4];
		// Variables temporales
		numPuzzles = 0;
		numDoors = 0;
		numMinibosses = 0;
		numCollectables = 0;

		if (fread(persistentItemBuffer, sizeof(persistentItemBuffer), 1, file) < 1)
			//return false; // fallar, avisar, salir
		
		numPuzzles = persistentItemBuffer[0];
		numCollectables = persistentItemBuffer[1];
		numDoors = persistentItemBuffer[2];
		numMinibosses = persistentItemBuffer[3];

		numPuzzles = 0;
		numDoors = 0;
		numMinibosses = 0;
		numCollectables = 0;

		// Se añade la info de mapa a la persistencia de datos
		data->addMapData(mapId, type, w, h, (const int**) layout, numPuzzles, numDoors, numMinibosses, numCollectables);
		data->getMapData(mapId)->setStartScreen(initScreen[0], initScreen[1]);

		// Se puede borrar el layout, ya que en MapData se clona
		for (int i = 0; i < w; i++) 
		{
			delete layout[i];
			layout[i] = NULL;
		}
		delete layout;

		fclose(file);
		file = NULL;
	}

	/* ** Se inicializan los datos del juego ** */

	// Variables temporales
	int neededHeartPieces;

	// Se carga el número de piezas de corazón necesarias a partir de la DBJ
	neededHeartPieces = 4;
	// Se indica a la persistencia de datos
	gdata->init(neededHeartPieces);


	/* ** Se inicializa el estado del juego ** */

	// Variables temporales
	int numKeyItems, maxLife, actualMoney, numPidgeons, numHeartPieces, barterProgress, gameProgress;
	MapLocation actualScreen;
	std::map<int,ToolInfo> tools;
	std::pair<int,int> lastPos;

	// Si no se indica archivo de carga, se inicializan los datos por defecto
	// Si se indica el archivo de carga, se cargan de allí
	if (path != "")
	{
		// Se obtienen los datos del archivo de guardado
		// Cargado de archivo
		numKeyItems = 0;
		maxLife = 0;
		actualMoney = 0;
		numPlayers = 0;
		numPidgeons = 0;
		numHeartPieces = 0;
		barterProgress = 0;
		gameProgress = 0;
		actualScreen.id = 0;
		actualScreen.screenX = 0;
		actualScreen.screenY = 0;
		tools;
		lastPos;
	}
	else
	{
		// Se obtienen los datos por defecto de la BDJ
		maxLife = 3;			//DataBaseInterface->initialMaxLife();
		tools.clear();			//DataBaseInterface->initialTools();
		actualScreen.id = 0;	//DataBaseInterface->initialMap();

		// Los datos sobre la posición en el mapa se obtienen de:
		//	MapData (screenInicial) y
		//  La propia pantalla ya cargada (not yet) [r4]
		actualScreen.positionX = 0; // Default
		actualScreen.positionY = 0; // Default
		
		std::pair<int, int> tmpScreen = data->getMapData(actualScreen.id)->getStartScreen(); // Default
		actualScreen.screenX = tmpScreen.first;
		actualScreen.screenY = tmpScreen.second; // Default

		// Los datos de dinero inicial y numKey items se obtienen de la database
		actualMoney = 0; //DataBaseInterface->initialMoney();
		numKeyItems = 0; //DataBaseInterface->initialKeyItems();

		// El resto se inician por defecto siempre
		numPidgeons = 0;
		numHeartPieces = 0;
		barterProgress = 0;
		gameProgress = 0;
		lastPos.first = actualScreen.positionX; // Hey! Originalmente lastPos se refería al tile de aparición, no a la pantalla
		lastPos.second = actualScreen.positionY;
	}

	// Se inician los datos en el estado del juego
	gstatus->init(	numKeyItems, 
					maxLife,
					tools, 
					actualMoney,
					actualScreen, 
					lastPos, 
					numPlayers,
					numPidgeons,
					numHeartPieces, 
					barterProgress, 
					gameProgress
				);


	/* ** Se inicia el estado del mapa ** */
	// Datos comunes a todos los mapas
	std::map<int, bool> collectables, doors, puzzles, minibosses;
	
	// Datos sólo de mazmorras
	bool bossDefeated, gotBossKey, gotCompass, gotMap, gotPowerUp;

	// Punteros para facilitar el desarrollo
	MapData* mapData;
	MapStatus* mapStatus;

	// Si no se indica archivo de guardado, se inicializan los datos por defecto
	// Si se indica el archivo de guardado, se cargan de allí
	if (path != "")
	{
		// Se cargan los datos del archivo de guardado indicado
		for (int i = 0; i < numMaps; i++)
		{
			// Obtenidos de archivo de guardado
			// Datos comunes a todos los mapas
			collectables;
			doors;
			puzzles;
			minibosses;

			// Se inician los datos en la persistencia
			mapData = data->getMapData(i);
			mapStatus = mapData->getMapStatus();

			mapStatus->setCollectables(collectables);
			mapStatus->setDoors(doors);
			mapStatus->setPuzzles(puzzles);
			mapStatus->setMinibosses(minibosses);

			// Si se trata de una mazmorra, se necesitan más datos
			if (mapData->getType() == 1)
			{
				// FROM FILE
				bossDefeated;
				gotBossKey;
				gotCompass;
				gotMap;
				gotPowerUp;

				// Se actualizan los datos en la persistencia
				((DungeonMapStatus*) mapStatus)->setBossDefeated(bossDefeated);
				((DungeonMapStatus*) mapStatus)->setBossKeyGot(gotBossKey);
				((DungeonMapStatus*) mapStatus)->setCompassGot(gotCompass);
				((DungeonMapStatus*) mapStatus)->setMapGot(gotMap);
				((DungeonMapStatus*) mapStatus)->setPowerUpGot(gotPowerUp);

			}
		}
	}
	else
	{
		// Si no se provee archivo de guardado, se inician los datos por defecto
		for (int i = 0; i < numMaps; i++)
		{
			// Se obtienen los elementos de persistencia
			mapData = data->getMapData(i);
			mapStatus = mapData->getMapStatus();

			/*
			Todo esto se inicia por defecto a vacío, no tendría sentido comenzar habiendo derrotado un boss
			y esta inicialización ya se hace al construir mapData
			
			// FROM DB & FILE
			collectables;
			doors;
			puzzles;
			minibosses;


			mapStatus->setCollectables(collectables);
			mapStatus->setDoors(doors);
			mapStatus->setPuzzles(puzzles);
			mapStatus->setMinibosses(minibosses);
			*/

			// Si es una mazmorra, se inicalizan los datos extra
			if (mapData->getType() == 1)
			{
				bossDefeated = false;
				gotBossKey = false;
				gotCompass = false;
				gotMap = false;
				gotPowerUp = false;

				((DungeonMapStatus*) mapStatus)->setBossDefeated(bossDefeated);
				((DungeonMapStatus*) mapStatus)->setBossKeyGot(gotBossKey);
				((DungeonMapStatus*) mapStatus)->setCompassGot(gotCompass);
				((DungeonMapStatus*) mapStatus)->setMapGot(gotMap);
				((DungeonMapStatus*) mapStatus)->setPowerUpGot(gotPowerUp);

			}
		}
	}

	// Los fallos aquí vienen por la carga, hasta que no haya carga nada
	return true;
}

bool Controller::shortInitData(std::string path){

	GameStatus* gstatus = data->getGameData()->getGameStatus();

	int numKeyItems, maxLife, actualMoney, numPidgeons, numHeartPieces, barterProgress, gameProgress;
	MapLocation actualScreen;
	std::map<int,ToolInfo> tools;
	std::pair<int,int> lastPos;

	if (path != "")
	{
		// FROM FILE
		numKeyItems;
		maxLife;
		actualMoney;
		numPlayers;
		numPidgeons;
		numHeartPieces;
		barterProgress;
		gameProgress;
		actualScreen;
		tools;
		lastPos;
	}
	else
	{
		// FROM DB
		maxLife = 3;			//DataBaseInterface->initialMaxLife();
		tools;					//DataBaseInterface->initialTools();
		actualScreen.id = 0;	//DataBaseInterface->initialMap();

		// FROM MAPDATA

		actualScreen;

		// POSSIBLY FROM DB
		
		actualMoney = 0; //DataBaseInterface->initialMoney();
		numKeyItems = 0; //DataBaseInterface->initialKeyItems();

		// NOT FROM DB
		numPidgeons = 0;
		numHeartPieces = 0;
		barterProgress = 0;
		gameProgress = 0;
		lastPos.first = actualScreen.screenX;
		lastPos.second = actualScreen.screenX;
	}

	gstatus->init(	numKeyItems, 
					maxLife,
					tools, 
					actualMoney,
					actualScreen, 
					lastPos, 
					numPlayers,
					numPidgeons,
					numHeartPieces, 
					barterProgress, 
					gameProgress
				);

	return true;
}

bool Controller::initGamePlayState(GamePlayState* gpst)
{
	// Se prepara el GamePlayState, instanciando los elementos necesarios y preparando el juego para funcionar

	// Se libera el antiguo GamePlayState si lo había
	if (gamePlayState != NULL)
		delete gamePlayState;

	// Se guarda el nuevo gpstate
	gamePlayState = gpst;

	// Se instancia la familia de Controller
	hudController = new HUDController(game, gamePlayState);
	toolController = new ToolController(this);
	eventController = new EventController(game, gamePlayState, this);
	
	entityReader = new EntityReader();

	// Se añade el listener de eventos de controller
	gamePlayState->_add(eventController);

/* ---------------------------------------------------------------------
1.	Localiza el mapa actual y la pantalla vía data
--------------------------------------------------------------------- */

	MapLocation location = data->getGameData()->getGameStatus()->getCurrentMapLocation();

/* ---------------------------------------------------------------------
2.	Carga la pantalla actual en su totalidad, y por cada entidad que
	cargue, la envía a GameState al add sobrecargado. Al final
	se llama al init de ScreenMap con todos los datos cargados.
--------------------------------------------------------------------- */

	loadScreen(location);
	location.positionX = 7;
	location.positionY = 6;

/* ---------------------------------------------------------------------
3.	Crea los players en la posición configurada de la pantalla del
	mapa actual.
--------------------------------------------------------------------- */

	DataBaseInterface::HeroData heroData;
	for (int i = 0; i < numPlayers; i++)
	{
		heroData = dbi->getHeroData();
		if (i == 0)
			players[i] = new Player(location.positionX*16, location.positionY*16, game, gamePlayState);
		else
			players[i] = new Player(location.positionX*16+16*3, location.positionY*16+16*2, game, gamePlayState);

		players[i]->init(heroData.gfxPath, 4, 44, heroData.hpMax, heroData.mpMax, this);
		gamePlayState->_add(players[i]);
	}

/* ---------------------------------------------------------------------
4.	Crea el hud adecuado a la cantidad de players.
--------------------------------------------------------------------- */

	// for each player
	// hud controller->addhud(player[i])

/* ---------------------------------------------------------------------
7.	Playea todos los elementos que ha creado de la nueva pantalla.
--------------------------------------------------------------------- */

	return true;
}

std::string Controller::getMapScreenFileName(MapLocation map)
{
	// Buffer de caracteres
	char buf[5];

	if (map.id < 0 && map.id >= data->getMapNumber()
		|| !data->getMapData(map.id)->hasScreen(map.screenX, map.screenY))
		return ""; // fallar, avisar, salir

	std::string fname = "";
	// Map files path
	fname.append("data/map/");
	fname.append("m");
	fname.append(itoa(map.id, buf, 10));
	fname.append("r");
	fname.append(itoa(map.screenX, buf, 10));
	fname.append("_");
	fname.append(itoa(map.screenY, buf, 10));

	return fname;
}

bool Controller::loadScreen(MapLocation m)
{
	// Al cargar una nueva pantalla, hay que almacenar los datos de la antigua
	if (screenMap != NULL)
		; // a la cola (tbimplemented)
	
	// Se comprueba que exista la pantalla
	if (!data->getMapData(m.id)->hasScreen(m.screenX, m.screenY))
		return false; // fallar, avisar, salir

	// Primero, calcular el nombre de archivo a partir del mapLocation
	std::string fname = getMapScreenFileName(m);
	// Archivo
	FILE* file = NULL;

	// Cargamos
	file = fopen(fname.c_str(), "r");

	// Si se carga mal...
	if (file == NULL)
		return false; // fallar, avisar, salir

	// Variables temporales
	int** solids;
	int** tiles;
	int screenW;
	int screenH;
	int tilew = 16;
	int tileh = 16;
	// Estos para pedir a DBI
	short idTileset;
	short idBackground;

	/* ** Comienza la carga de la pantalla ** */

	// 0. Ancho y alto de la pantalla en tiles
	short whBuf[2];
	if (fread(whBuf, sizeof(whBuf), 1, file) < 1)
		return false; // fallar, avisar, salir

	// Se apuntan los nuevos valores
	screenW = whBuf[0];
	screenH = whBuf[1];

	// 0.5. Ancho y alto de los tiles
	short tileDim[2];

	if (fread(tileDim, sizeof(tileDim), 1, file) < 1)
		return false; // fallar, avisar, salir

	// Se guardan
	tilew = tileDim[0];
	tileh = tileDim[1];

	// 1. Id del tileset, id del gráfico del bg
	short idTsetBg[2];

	if (fread(idTsetBg, sizeof(idTsetBg), 1, file) < 1)
		return false; // fallar, avisar, salir

	// Se guardan
	idTileset = idTsetBg[0];
	idBackground = idTsetBg[1];

	// 2. Leer tiles

	// Buffers
	short** mapTiles;
	short** mapSolids;

	// Se reserva memoria para los tiles
	mapTiles = (short**) malloc(sizeof(short*)*screenW);
	tiles = (int**) malloc(sizeof(int*)*screenW);
	for (int i = 0; i < screenW; i++)
		mapTiles[i] = (short*) malloc(sizeof(short)*screenH),
		tiles[i] = (int*) malloc(sizeof(int)*screenH);

	// Se reserva memoria para los solids
	mapSolids = (short**) malloc(sizeof(short*)*screenW);
	solids = (int**) malloc(sizeof(int*)*screenW);
	for (int i = 0; i < screenW; i++)
		mapSolids[i] = (short*) malloc(sizeof(short)*screenH),
		solids[i] = (int*) malloc(sizeof(int)*screenH);

	// Se cargan los tiles por filas, ajustando a int**, que es lo que usa TileMap
	for (int i = 0; i < screenW; i++)
	{
		for (int j = 0; j < screenH; j++)	
			if (fread(&(mapTiles[i][j]), sizeof(mapTiles[i][j]), 1, file) < 1)
				return false; // fallar, avisar, salir
	}
	
	// Se prepara el layout y se almacenan los datos
	for (int i = 0; i < screenW; i++)
	{
		for (int j = 0; j < screenH; j++)
		{
			tiles[i][j] = mapTiles[i][j];
		}
	}

	// Se cargan los sólidos por filasajustando a int**, que es lo que usa TileMap
	for (int i = 0; i < screenW; i++)
	{
		for (int j = 0; j < screenH; j++)
		{
			if (fread(&(mapSolids[i][j]), sizeof(mapSolids[i][j]), 1, file) < 1)
				return false; // fallar, avisar, salir
			
			solids[i][j] = (int) mapSolids[i][j];
		}
	}

	// Se libera la memoria de los tiles y sólidos temporales
	for (int i = 0; i < screenW; i++)
		delete mapSolids[i], delete mapTiles[i];
	delete mapSolids;
	delete mapTiles;

	gamePlayState->removeMap(false);

	// Se prepara el ScreenMap
	if (screenMap != NULL)
		delete screenMap;

	screenMap = new ScreenMap(tilew*screenW, tileh*screenH, tilew, tileh, 0, 0, game->getGfxEngine());
	screenMap->setSolids(0, 0, solids, screenW, screenH);
	screenMap->setTiles(tiles, screenW, screenH);
	if (m.id == 0)
		screenMap->setTileset("./data/graphics/tset.png"); // setTileset(DBI->getTileset(idTileset))
	else if (m.id == 1)
		screenMap->setTileset("./data/graphics/tset2.png"); // setTileset(DBI->getTileset(idTileset))
	else
		screenMap->setTileset("./data/graphics/tset3.png"); // setTileset(DBI->getTileset(idTileset))

	/* ********************************************** */
	/* FALTA TODA LA CARGA DE ENEMIGOS; ENTITIES; ... */
	/* ********************************************** */

	// TILES

	short nfgBuf[1];
	if (fread(nfgBuf, sizeof(nfgBuf), 1, file) < 1)
		return false; // fallar, avisar, salir

	short nfgTiles = nfgBuf[0];
	
	short fgBuf[3];
	for (int i = 0; i < nfgTiles; i++)
	{
		if (fread(fgBuf, sizeof(fgBuf), 1, file) < 1)
			return false;

		// Use them if needed
	}

	// PUZZLES

	short npuzzlesBuf[1];
	if (fread(npuzzlesBuf, sizeof(npuzzlesBuf), 1, file) < 1)
		return false; // fallar, avisar, salir

	short npuzzles = npuzzlesBuf[0];
	
	short puzzlesBuf[2];
	for (int i = 0; i < npuzzles; i++)
	{
		if (fread(puzzlesBuf, sizeof(puzzlesBuf), 1, file) < 1)
			return false;

		// Use them if needed
	}

	// ENTITIES

	vector<Entity*>* screenEntities = new vector<Entity*>();
	entityReader->readEntities(file, screenEntities);
	// se libera el vector hasta que veamos qué se hace con él.
	delete screenEntities;

	// ENEMIES

	short nenenemiesBuf[1];
	if (fread(nenenemiesBuf, sizeof(nenenemiesBuf), 1, file) < 1)
		return false; // fallar, avisar, salir

	short nenenemies = nenenemiesBuf[0];
	
	short enenemiesBuf[3];
	for (int i = 0; i < nenenemies; i++)
	{
		if (fread(enenemiesBuf, sizeof(enenemiesBuf), 1, file) < 1)
			return false;

		// Use them if needed
	}


	fclose(file);

	/* Se quitan las entidades necesarias */
	//gamePlayState->removeAll();
	/* Se añaden los players */

	screenMap->getMapImage();
	// Esto no haría falta si se hace sobre la nueva pantalla va sobre el antiguo puntero
	gamePlayState->addMap(screenMap);

	return true;
}

bool Controller::moveScreen(Direction dir)
{

/* ---------------------------------------------------------------------
1. Preguntar a Data por la pantalla destino. Recibe lista de propiedades
	1.1. Preguntar si la pantalla destino existe
--------------------------------------------------------------------- */
	
	// Obtenemos la pantalla destino del cambio
	int up; int left;
	up = left = 0;
	switch (dir) 
	{
		case UP:	up = -1; break;
		case DOWN:	up = 1; break;
		case LEFT:	left = -1; break;
		case RIGHT:	left = 1; break;
		default:	break;
	}

	// A partir del desplazamiento desde la actual
	MapLocation m = data->getGameData()->getGameStatus()->getCurrentMapLocation();
	m.screenX += left;
	m.screenY += up;
				
	if (!changeLocation(m))
		return false; // fail, avisar, fallar

/* ---------------------------------------------------------------------
9. Colocación del player + preparación para la transición
	9.1. Colocación del player
--------------------------------------------------------------------- */
	
		// PONER OFFSET A LOS MAPAS

		// Stupid code test (y tan stupid Ò_ó)
		int x, y;
		x = players[0]->x;
		y = players[0]->y;
		switch (dir) 
		{
			case UP: 
				// Mantenemos la x y cambiamos la y
				y = height-16-8; 
				break;
			case DOWN:
				// Mantenemos la x y cambiamos la y
				y = 8; 
				break;
			case LEFT:
				// Mantenemos la y y cambiamos la x
				x = width-16-8;
				break;
			case RIGHT: 
				// Mantenemos la y y cambiamos la x
				x = 8;
				break;
		};

//		for (int i = 0; i < numPlayers; i++)
//			players[i]->x = x, players[i]->y = y;

/* ---------------------------------------------------------------------
	9.2. Aplicación de efectos y preparación de la transición.
--------------------------------------------------------------------- */
		
		// Se prepara la transición
		EventController::TransitionProperties trans;
		trans.effect = EventController::SCROLL;
		trans.speed = 8;
		trans.direction = dir;

		eventController->initTransition(trans, currentRoom, nextRoom);

/* ---------------------------------------------------------------------
10. Finalización
--------------------------------------------------------------------- */
		return true;
}

bool Controller::changeLocation(MapLocation target)
{
	// Preguntamos si la pantalla existe
	if (data->getMapData(target.id)->hasScreen(target.screenX, target.screenY))
	{
			
/* ---------------------------------------------------------------------
	1.2. Obtenemos las propiedades de la pantalla destino.
--------------------------------------------------------------------- */
	
			// Ya están en target, lala(8)
			   
/* ---------------------------------------------------------------------
2. Desvisivilizar player y hud
	2.1. Desvisibilizar player
--------------------------------------------------------------------- */

		for (int i = 0; i < numPlayers; i++)
		{
			players[i]->setVisible(false);
		}
				
/* ---------------------------------------------------------------------
	2.2. Desvisibilizar hud
--------------------------------------------------------------------- */

//		hud->setVisible(false);       

/* ---------------------------------------------------------------------
3. Hace foto y la guarda
--------------------------------------------------------------------- */

		// Limpiar las imágenes antes de empezar
		game->getGfxEngine()->clearImage(currentRoom, Color::Black);
		game->getGfxEngine()->clearImage(nextRoom, Color::Black);

		// Limpiar currentRoom si es necesario
		game->getGfxEngine()->setRenderTarget(currentRoom);
		gamePlayState->onRender();
		game->getGfxEngine()->resetRenderTarget();
		
		currentRoom->refresh();
		   
/* ---------------------------------------------------------------------
4. Mapa, cárgame los datos del nuevo mapa y borra los anteriores ( o buffer ). 
El nuevo mapa sustituirá al actual, contendrá a los players y el hud y además
las entidades cargadas deberán estar disabled (de eso me ocupo yo, Controller).
--------------------------------------------------------------------- */

		// think, qué pasa si no se carga, etc...
		if (!loadScreen(target))
			return false; // fallar, avisar, salir
				
/* ---------------------------------------------------------------------
5. Hazle foto al nuevo mapa.
--------------------------------------------------------------------- */

		// Limpiar nextRoom si es necesario
		game->getGfxEngine()->setRenderTarget(nextRoom);
		gamePlayState->onRender();
		game->getGfxEngine()->resetRenderTarget();
		
		nextRoom->refresh();

/* ---------------------------------------------------------------------
6. Junta fotos.
--------------------------------------------------------------------- */
		
		// No es necesario si pintamos las 2 directamente en la pantalla de juego
		// Nos ahorramos una pantalla auxiliar

/* ---------------------------------------------------------------------
7. Visibiliza player y hud
	7.1 Hace visible el player. Será necesario además disablearlo para 
	que no pueda moverse durante la transición
--------------------------------------------------------------------- */
	
		for (int i = 0; i < numPlayers; i++)
		{
			players[i]->setVisible(true);
			players[i]->freeze();
		}
	
/* ---------------------------------------------------------------------
	7.2. Hace visible el Hud y lo disablea por el mismo motivo.
--------------------------------------------------------------------- */
	
		/*hud->setVisible(true);
		hud->disable();*/

/* ---------------------------------------------------------------------
8. Actualiza los datos con la nueva pos del player en el mapa.
--------------------------------------------------------------------- */

		// Igual ha de hacerse antes de cargar el nuevo ScreenMap
		data->getGameData()->getGameStatus()->setCurrentMapLocation(target);

		return true;
	};
	return false;
};

bool Controller::teleportTo(MapLocation m, Player* p, EventController::TransitionEffect te, bool brute){

/* -----------------------
	STAAART!

	Tentativo de ir en otro método.

	Si brute está activado, ir a 1 directamente.

	A. Ir al map de portales activos y aumentar en 1 el contador de éste (el id del portal puede ser interno), si no existe se pone a 1.
	B. Si el contador aumentado es mayor que la mitad de los players
		B1. Hacer la correspondiente animación del player con el portal.
		B2. Desactivar al player.
		B3.ir a 1.
	C. Si el contador es menor, y es el primer portal que se toca (easy, si el mapa estaba vacío al entrar al método), poner un timer(0, n?)
		C1. Hacer la correspondiente animación del player con el portal.
		C2. Desactivar al player.
		C3. return (false?)
------------------------- */

	// Vamos con la carga de mapas
	/*
	1. Preguntar a la DBI si existe el mapa destino. (básicamente pedirle el archivo correspondiente al id y si le da caca pues caca no vale)
		1y. Si existe, obtener vía DBI el archivo del mapa (done en 1), cargarlo (loadmap) y meter la info Data (no incluído en loadmap, loadmap devuelve la info).
		1n. Si no existe, el portal no tiene efecto [return false]
	*/

	// Se comprueba el id del mapa, por si es inválido
	if (m.id < 0 || data->getMapNumber() <= m.id)
		return false; // fail, avisar, salir

	// Se obtienen los datos del mapa
	MapData* targetMap = data->getMapData(m.id);
	if (targetMap == NULL)
		return false; // fallar, avisar, salir

	// Se comprueba que exista la pantalla destino
	bool targetScreenGiven = targetMap->hasScreen(m.screenX, m.screenY);

	// Todo ok, se actualiza la info de teletransporte
	MapLocation target;
	target.id = m.id;
	// Si se indica la pantalla destino, también se indicará la posición destino
	if (targetScreenGiven)
	{
		target.screenX = m.screenX;
		target.screenY = m.screenY;
		target.positionX = m.positionX;
		target.positionY = m.positionY;
	};
	// Si no, positionX, positionY se obtienen de la pantalla

	// A partir de aquí, ídem al cambio de pantalla (¿reusar código?)
	/*
	2. Preguntar a Data si existe la pantalla dada (rezando que Data tenga esa función).
		2y. Si no, elegir la pantalla de inicio del mapa (cargada en 1a).
		2n. Si existe, ir a 3.
	3. Hacer invisibles a los player y al hud
	4. Hacer foto
	5. Cargar la pantalla destino.
	6. Dar la info cargada a ScreenMap y GameState. Las entidades que se carguen deberán disablearse.
	7. Foto
	8. Visibilizar players y hud; disablearlos para la transición.

	De esto se encarga changeLocation
	*/

	if (!changeLocation(target))
		return false; // fallar, avisar, salir

	// Falta fijar la posición del player para colocarle.
	eventController->xpos = target.positionX*16, eventController->ypos = target.positionY*16;

	/*
	9. Preparar los efectos de la transición
	*/

	// Se prepara la transición
	EventController::TransitionProperties trans;
	trans.effect = te;
	trans.speed = 2;
	trans.direction = NONE;

	eventController->initTransition(trans, currentRoom, nextRoom);
/*
	10. Fin! [return true]
 */
	return true;
}


Controller::State Controller::getState()
{
	return state;
}

void Controller::setState(State st)
{
	state = st;
}
		
int Controller::getNumPlayers()
{
	return numPlayers;
}

EventController::TransitionEffect Controller::getTransitionEffect()
{
	return transitionEffect;
}

ScreenMap* Controller::getScreenMap()
{
	return screenMap;
}
Player* Controller::getPlayer(int i)
{
	if ((i >= 0) && (i < numPlayers))
		return players[i];
	else
		return NULL;
}

HUDController* Controller::getHUDController()
{
	return hudController;
}

ToolController* Controller::getToolController()
{
	return toolController;
}

EventController* Controller::getEventController()
{
	return eventController;
}
		
bool Controller::addPlayer(/*params?*/)
{

	return true;
}

bool Controller::removePlayer(Player* p)
{
	return true;
}

bool Controller::removePlayer(int i)
{
	return true;
}

void Controller::endTransition()
{
	// Activamos al player
	for (int i = 0; i < getNumPlayers(); i++)
	{
		getPlayer(i)->setVisible(true);
		getPlayer(i)->unfreeze();
		// FailProofing
		while (!gamePlayState->place_free(getPlayer(i)->x, getPlayer(i)->y, getPlayer(i)))
		{
			int x = rand()%width;
			int y = rand()%height;
			getPlayer(i)->x = x; getPlayer(i)->y = y;
		};
	}
				
	getHUDController()->enableHUDs();
					
	// Activamos el resto de entidades
	// TO BE DONE
				
	setState(Controller::NORMAL);
};

DataPersistence* Controller::getData()
{
	return data;
};