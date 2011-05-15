#include "controller.h"

#include "CollisionTester.h"

#include "CollectableGameItem.h"
#include "TiledEntity.h"
#include "TiledPushable.h"
#include "Instantiator.h"
#include "DamageableBlockade.h"
#include "Teleporter.h"
#include "Door.h"
#include "FloorButton.h"
#include "ArenaEntity.h"
#include "GamePuzzle.h"

#include "ComponentAnimFlying.h"
#include "ComponentBatMovement.h"
#include "ComponentTackle.h"
#include "ComponentMelee.h"
#include "ComponentMeleeSimple.h"
#include "ComponentTest.h"

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

	hudController = NULL;
	toolController = NULL;
	messageController = NULL;
	eventController = NULL;
	screenMapList = NULL;

	active_teleports = NULL;

	InputConfig inputConfig;

	inputConfig.joyMode = false;
	inputConfig.gamePad = 0;
	inputConfig.xAxis = 0;
	inputConfig.yAxis = 1;
	inputConfig.joyA = 0;
	inputConfig.joyB = 1;
	inputConfig.joySTART = 2;
	inputConfig.joySELECT = 3;
	
	inputConfig.keyLeft = Input::kLEFT;
	inputConfig.keyRight = Input::kRIGHT;
	inputConfig.keyUp = Input::kUP;
	inputConfig.keyDown = Input::kDOWN;
	inputConfig.keyA = Input::kA;
	inputConfig.keyB = Input::kS;
	inputConfig.keySTART = Input::kENTER;
	inputConfig.keySELECT = Input::kSPACE;

	// Cargar la configuración de botones asignada, o cargar la configuración por defecto si la primera no existe
	if (!loadInputConfig(mainInputConfig, "data/config-p1"))
		mainInputConfig = inputConfig;

	currentScreen = TITLE;
}
	
Controller::~Controller()
{
	if (hudController != NULL)
		delete hudController, hudController = NULL;
	if (toolController != NULL)
		delete toolController, toolController = NULL;
	if (messageController != NULL)
		delete messageController, messageController = NULL;		
	if (eventController != NULL)
		delete eventController, eventController = NULL;
	
	if (dbi != NULL)
		delete dbi, dbi = NULL;

	if (data != NULL)
		delete data, data = NULL;

	if (currentRoom != NULL)
		delete currentRoom, currentRoom = NULL;
	if (nextRoom != NULL)
		delete nextRoom, nextRoom = NULL;

	for (int i = 0; i < numPlayers; i++)
		if (players[i] != NULL)
			delete players[i], players[i] = NULL;

	if (screenMapList != NULL)
	{
		std::deque<ScreenMapConstructor*>::iterator it = screenMapList->begin();
		while (it != screenMapList->end())
		{
			ScreenMapConstructor* s = (*it);
			if (s != NULL)
				delete s;
			it++;
		};
		delete screenMapList;
	}

	if (active_teleports != NULL)
		delete active_teleports, active_teleports = NULL;
}
	


bool Controller::initData(std::string path)
{
	FILE* f = NULL;
	if (path != "")
	{
		f = fopen(path.c_str(), "r");
		if (!data->load(f, false)) return false;
	}
	// Se obtienen punteros a DataPersistence para facilitar el trabajo
	GameData* gdata = data->getGameData();
	GameStatus* gstatus = gdata->getGameStatus();

	// Se obtienen el número de players (debe venir de algún sitio del PGZGame [r1])
	numPlayers = 1; // Default
	if (path != "") gstatus->setNumPlayers(numPlayers);

	/* ** Se inician los datos de los mapas ** */
	
	// Variables temporales
	int numMaps, mapId, w, h, numPuzzles, numDoors, numMinibosses, numCollectables;
	char type;
	int** layout;

		
	// Variables temporales
	int numKeyItems, maxLife, actualMoney, numPigeons;
	MapLocation actualScreen;
	std::map<int,ToolInfo> tools;
	std::vector<int> toolIds;
	std::pair<int,int> lastPos;

	readMainInfo(numMaps, numKeyItems, maxLife, actualMoney, (&toolIds), numPigeons);



	// Se carga el número de mapas ¿de la DBI? [r2]
	if (path != "") numMaps = data->getMapNumber();
	else ;//numMaps = 1; // Default

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
		short tipo[1];
		if (fread(tipo, sizeof(short), 1, file) < 1)
			return false; // fallar, avisar, volver

		// Se almacena el tipo de mapa
		type = (char) tipo[0];


		// 1. Ancho y alto en pantallas del mapa
		// Buffer para el ancho, alto
		short whBuf[2];
		// Se lee 
		if (fread(whBuf, sizeof(short), 2, file) < 1)
			return false; // Fail, abortar, returnear

		// Se almacena el ancho y alto
		w = whBuf[0];
		h = whBuf[1];
	
		// 2. Se carga el layout

		// Se reserva memoria para el layout
		// [r3] No creo que necesitemos int para el layout, short o algo vale
		// [Extra] Por ahora se guardan bools, meh
		
		// buffer layout
		char** lbuf = new char*[w];
		for (int i = 0; i < w; i++)
			lbuf[i] = new char[h];

		// Se lee el layout entero por filas
		for (int i = 0; i < w; i++)
		{
			if (fread(lbuf[i], sizeof(char), h, file) < 1)
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
				layout[i][j] = lbuf[i][j];
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

		// Se almacena la info y se libera la memoria más tarde

		// Se carga de archivo el nº de puzzles, puertas, minibosses y collectables
		// Buffers
		short persistentItemBuffer[4];

		if (fread(persistentItemBuffer, sizeof(short), 4, file) < 1);
			//return false; // fallar, avisar, salir
		
		numPuzzles = persistentItemBuffer[0];
		numCollectables = persistentItemBuffer[1];
		numDoors = persistentItemBuffer[2];
		numMinibosses = persistentItemBuffer[3];


		// Se añade la info de mapa a la persistencia de datos
		if (path != ""){
			data->getMapData(mapId)->setWidth(w);
			data->getMapData(mapId)->setHeight(h);
			data->getMapData(mapId)->setNumCollectables(numCollectables);
			data->getMapData(mapId)->setLayout(layout);
			data->getMapData(mapId)->setNumDoors(numDoors);
			data->getMapData(mapId)->setNumMiniBosses(numMinibosses);
			data->getMapData(mapId)->setNumPuzzles(numPuzzles);
		}
		else{
			data->addMapData(mapId, type, w, h, (const int**) layout, numPuzzles, numDoors, numMinibosses, numCollectables);
		}
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
	/*int neededHeartPieces;

	// Se carga el número de piezas de corazón necesarias a partir de la DBJ
	neededHeartPieces = 4;*/
	// Se indica a la persistencia de datos
	if (path != "")gdata->setNeededHeartPieces(0);
	else gdata->init(0);


	/* ** Se inicializa el estado del juego ** */



	// Si no se indica archivo de carga, se inicializan los datos por defecto
	if (path == "")
	{
		// Se obtienen los datos por defecto de la BDJ
		//maxLife = 3;			//DataBaseInterface->initialMaxLife();
		//tools.clear();			//DataBaseInterface->initialTools();
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
		//actualMoney = 0; //DataBaseInterface->initialMoney();
		//numKeyItems = 0; //DataBaseInterface->initialKeyItems();

		// El resto se inician por defecto siempre
		//numPigeons = 0;
		lastPos.first = actualScreen.positionX; // Hey! Originalmente lastPos se refería al tile de aparición, no a la pantalla
		lastPos.second = actualScreen.positionY;

		std::pair<int,ToolInfo> aux;
		ToolInfo toolInfo;
		for (vector<int>::iterator it = toolIds.begin(); it != toolIds.end(); it++)
		{
			aux.first = (*it);
			toolInfo.idTool = (*it);
			toolInfo.ammoQuantity = 0;
			toolInfo.available = false;
			toolInfo.idAmmo = 0; // WHAT?
			aux.second = toolInfo;

			tools.insert(aux);
		}

		// Se inician los datos en el estado del juego
		gstatus->init(	numKeyItems, 
						maxLife,
						tools, 
						actualMoney,
						actualScreen, 
						lastPos, 
						numPlayers,
						0//numPigeons
					);
	}


	/* ** Se inicia el estado del mapa ** */
	// Datos comunes a todos los mapas
	std::map<int, bool> collectables, doors, puzzles, minibosses;
	
	// Datos sólo de mazmorras
	bool bossDefeated, gotBossKey, gotCompass, gotMap, gotPowerUp;

	// Punteros para facilitar el desarrollo
	MapData* mapData;
	MapStatus* mapStatus;

	// Si no se indica archivo de guardado, se inicializan los datos por defecto
	if (path == "")
	{
		// Si no se provee archivo de guardado, se inician los datos por defecto
		for (int i = 0; i < numMaps; i++)
		{
			// Se obtienen los elementos de persistencia
			mapData = data->getMapData(i);
			mapStatus = mapData->getMapStatus();

			/*
			Todo esto se inicia por defecto a vacío, no tendría sentido comenzar habiendo derrotado un boss
			y esta inicialización ya se hace al construir mapData*/
			
			// FROM DB & FILE
			/*collectables;
			doors;
			puzzles;
			minibosses;


			mapStatus->setCollectables(collectables);
			mapStatus->setDoors(doors);
			mapStatus->setPuzzles(puzzles);
			mapStatus->setMinibosses(minibosses);*/

			// Init Collectables
			for (int i = 0; i < mapData->getNumCollectables(); i++)
				mapStatus->setCollectableStatus(i, false);
			for (int i = 0; i < mapData->getNumDoors(); i++)
				mapStatus->setDoorStatus(i, false);
			for (int i = 0; i < mapData->getNumPuzzles(); i++)
				mapStatus->setPuzzleStatus(i, false);
			for (int i = 0; i < mapData->getNumMiniBosses(); i++)
				mapStatus->setMinibossStatus(i, false);

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


bool Controller::readMainInfo(int & numMaps, int & numKeyItems, int & initLife, int & initMoney, vector<int> * tools, int & numPigeons)
{
	// Carga el archivo y se lee
	FILE* f = fopen("./data/maininfo", "r");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	if (fscanf(f, "%d", &numMaps) < 1)
		return false;

	if (fscanf(f, "%d", &numKeyItems) < 1)
		return false;

	if (fscanf(f, "%d", &initLife) < 1)
		return false;

	if (fscanf(f, "%d", &initMoney) < 1)
		return false;

	int numTools = 0, idTool = 0;
	if (fscanf(f, "%d", &numTools) < 1)
		return false;

	for (int i = 0; i < numTools; i++)
	{
		if (fscanf(f, "%d", &idTool) < 1)
			return false;
		tools->push_back(idTool);
	}

	if (fscanf(f, "%d", &numPigeons) < 1)
		return false;

	fclose(f);
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
					numPidgeons
				);

	return true;
}

bool Controller::initGamePlayState(GamePlayState* gpst)
{
	// Se prepara el GamePlayState, instanciando los elementos necesarios y preparando el juego para funcionar
	currentScreen = GAMEPLAY;

	// Se libera el antiguo GamePlayState si lo había
	if (gamePlayState != NULL)
		delete gamePlayState;

	// Se guarda el nuevo gpstate
	gamePlayState = gpst;

	// Se instancia la familia de Controller
	hudController = new HUDController(game, gamePlayState);
	gamePlayState->hudController = hudController;
	toolController = new ToolController(this);
	messageController = new MessageController(this);
	eventController = new EventController(game, gamePlayState, this);

	// Se inicia a ToolController con las herramientas del juego
	std::vector<int> tools;
	std::map<int, ToolInfo> gameTools; // habrá que cogerlo de los datos del juego en un futuro
	gameTools = getData()->getGameData()->getGameStatus()->getTools();
	std::map<int, ToolInfo>::iterator it;

	for (it = gameTools.begin(); it != gameTools.end(); it++) 
		tools.push_back((*it).second.idTool); // de momento solo metemos 4 armas
	toolController->init(tools);
	for (int i = 1; i < tools.size(); i++) 
		toolController->setEquippable(i, true); // damos la posibilidad de equipar todas las armas

	screenMapList = new deque<ScreenMapConstructor*>();
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

	//InputConfig config1, config2;
	/*
	config1.joyMode = false;
	config1.gamePad = 0;
	config1.xAxis = 0;
	config1.yAxis = 1;
	config1.joyA = 0;
	config1.joyB = 1;
	
	config1.keyLeft = Input::kLEFT;
	config1.keyRight = Input::kRIGHT;
	config1.keyUp = Input::kUP;
	config1.keyDown = Input::kDOWN;
	config1.keyA = Input::kA;
	config1.keyB = Input::kS;

	config2.joyMode = true;
	config2.gamePad = 0;
	config2.xAxis = 0;
	config2.yAxis = 1;
	config2.joyA = 0;
	config2.joyB = 1;
	
	config2.keyLeft = Input::kLEFT;
	config2.keyRight = Input::kRIGHT;
	config2.keyUp = Input::kUP;
	config2.keyDown = Input::kDOWN;
	config2.keyA = Input::kA;
	config2.keyB = Input::kS;*/

	InputConfig config;

	std::string path = "data/config-p";
	char buffer [2];
	DataBaseInterface::HeroData heroData;
	for (int i = 0; i < numPlayers; i++)
	{
		heroData = dbi->getHeroData();
		path.append(itoa(i + 1, buffer, 10));

		if (i == 0)
		{
			players[i] = new Player(location.positionX*16, location.positionY*16, game, gamePlayState);
		}
		else
		{
			players[i] = new Player(location.positionX*16+16*3, location.positionY*16+16*2, game, gamePlayState);
		}

		loadInputConfig(config, path);
		players[i]->setInputConfig(config);

		players[i]->init(heroData.gfxPath, data->getGameData()->getGameStatus()->getMaxLife(), 0, this);
		gamePlayState->_add(players[i]);
		hudController->addHud(players[i]);
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
	if (fread(whBuf, sizeof(short), 2, file) < 1)
		return false; // fallar, avisar, salir

	// Se apuntan los nuevos valores
	screenW = whBuf[0]*2;
	screenH = whBuf[1]*2;

	// 0.5. Ancho y alto de los tiles
	short tileDim[2];
	if (fread(tileDim, sizeof(short), 2, file) < 1)
		return false; // fallar, avisar, salir

	// Se guardan
	tilew = tileDim[0]/2;
	tileh = tileDim[1]/2;

	// 1. Id del tileset, id del gráfico del bg
	short idTsetBg[2];
	if (fread(idTsetBg, sizeof(short), 2, file) < 1)
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
	mapSolids = (short**) malloc(sizeof(short*)*screenW/2);
	
	solids = (int**) malloc(sizeof(int*)*screenW);
	
	for (int i = 0; i < screenW/2; i++)
		mapSolids[i] = (short*) malloc(sizeof(short)*screenH/2);
	
	for (int i = 0; i < screenW; i++)
		solids[i] = (int*) malloc(sizeof(int)*screenH);

	// Se cargan los tiles por filas, ajustando a int**, que es lo que usa TileMap
	for (int i = 0; i < screenW; i++)
	{
		for (int j = 0; j < screenH; j++)	
			if (fread(&(mapTiles[i][j]), sizeof(short), 1, file) < 1)
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
	for (int i = 0; i < screenW/2; i++)
	{
		for (int j = 0; j < screenH/2; j++)
		{
			if (fread(&(mapSolids[i][j]), sizeof(short), 1, file) < 1)
				return false; // fallar, avisar, salir
			
			// Ahora un solid son 4 D:<
			solids[2*i][2*j] = (int) mapSolids[i][j];
			solids[2*i+1][2*j] = (int) mapSolids[i][j];
			solids[2*i][2*j+1] = (int) mapSolids[i][j];
			solids[2*i+1][2*j+1] = (int) mapSolids[i][j];
		}
	}

	// Se libera la memoria de los tiles y sólidos temporales
	for (int i = 0; i < screenW; i++)
		delete mapTiles[i];

	for (int i = 0; i < screenW/2; i++)
		delete mapSolids[i];

	delete mapSolids;
	delete mapTiles;

	gamePlayState->removeMap(false);

	// Se prepara el ScreenMap
	if (screenMap != NULL)
	{
		ScreenMapConstructor* screenConstr = screenMap->getConstructor();

		if (screenMapList->size() >= 6)
		{
			ScreenMapConstructor* tmp = screenMapList->back();
			screenMapList->pop_back();
			delete tmp;
		}

		screenMapList->push_front(screenConstr);

		delete screenMap;
	}

	screenMap = new ScreenMap(tilew*screenW, tileh*screenH, tilew, tileh, 0, 0, game->getGfxEngine());
	screenMap->setScreenLocation(m);
	screenMap->setSolids(0, 0, solids, screenW, screenH);
	screenMap->setTiles(tiles, screenW, screenH);
	screenMap->setTileset(dbi->getTilesetData(idTileset).gfxPath); // setTileset(DBI->getTileset(idTileset))
	screenMap->getMapImage();

	gamePlayState->addMap(screenMap);

	/* ********************************************** */
	/* FALTA TODA LA CARGA DE ENEMIGOS; ENTITIES; ... */
	/* ********************************************** */

	// TILES
	short nfgBuf[1];
	if (fread(nfgBuf, sizeof(short), 1, file) < 1)
		return false; // fallar, avisar, salir

	short nfgTiles = nfgBuf[0];
	
	short fgBuf[3];
	for (int i = 0; i < nfgTiles; i++)
	{
		if (fread(fgBuf, sizeof(short), 3, file) < 1)
			return false;

		// Use them if needed
	}

	// PUZZLES
	map<int, GamePuzzle*>* screenPuzzles = new map<int, GamePuzzle*>();

	short npuzzlesBuf[1];
	if (fread(npuzzlesBuf, sizeof(short), 1, file) < 1)
		return false; // fallar, avisar, salir

	short npuzzles = npuzzlesBuf[0];
	
	short puzzlesBuf[2];
	GamePuzzle* puzzle = NULL;
	MapStatus* ms = data->getMapData(data->getGameData()->getGameStatus()->getCurrentMapLocation().id)->getMapStatus();
	for (int i = 0; i < npuzzles; i++)
	{
		// puzzlesBuf: type, id
		if (fread(puzzlesBuf, sizeof(short), 2, file) < 1)
			return false;

		// Use them if needed
		screenPuzzles->insert(make_pair(puzzlesBuf[1], new GamePuzzle(puzzlesBuf[1], ms, game, gamePlayState)));
	}

	// ENTITIES
	map<int, Entity*>* screenEntities = new map<int, Entity*>();
	// se cargan las entidades
	readEntities(file, screenEntities, screenPuzzles);

	// ENEMIES
	vector<Enemy*>* screenEnemies = new vector<Enemy*>();
	// se leen los enemigos
	readEnemies(file, screenEnemies, screenEntities);

	// ------------------------------------------------------------------------------- NEW!
	// Apañad esto como sea, que no sé a qué variables/atributos corresponden

	// Posición inicial del personaje en la pantalla
	short initialPos[2];
	fread(initialPos, sizeof(short), 2, file);
	short posIniX = initialPos[0];
	short posIniY = initialPos[1];

	// Se actualizan los datos en mapLocation
	MapLocation tempLocation = screenMap->getScreenLocation();
	tempLocation.positionX = posIniX;
	tempLocation.positionY = posIniY;
	screenMap->setScreenLocation(tempLocation);

	// Id de la música que suena en la pantalla
	short music[1];
	fread(music, sizeof(short), 1, file);
	short idMusic = music[0];
	
	fclose(file);

	/* Se quitan las entidades necesarias */
	//gamePlayState->removeAll();
	/* Se añaden los players */

	// Esto no haría falta si se hace sobre la nueva pantalla va sobre el antiguo puntero

	// Se añaden las entidades
	map<int, Entity*>::iterator eIt = screenEntities->begin();
	while (eIt != screenEntities->end())
	{
		if ((*eIt).second != NULL)
		{
			// Se añade para la foto
			gamePlayState->_add((*eIt).second);
			// Y al buffer de locales
			gamePlayState->addLocal((*eIt).second);
		}
		eIt++;
	}
	// se libera el vector hasta que veamos qué se hace con él.
	delete screenEntities;

	// Se añaden los enemigos
	// ANTES DE MIRAR LOS ENEMIGOS EN EL ARCHIVO, CHECKEAR LA SCREENMAPLIST
	bool found = false;
	deque<ScreenMapConstructor*>::iterator it = screenMapList->begin();
	while ((it != screenMapList->begin()) && !found)
	{
		if ((((*it)->getMapLocation().id == m.id) && ((*it)->getMapLocation().screenX == m.screenX)) && ((*it)->getMapLocation().screenY == m.screenY))
			found = true;
		else
			it++;
	}

	if (found)
	{	
		list< EnemySpawnData * > enemylist = (*it)->getEnemiesData();
		list<EnemySpawnData*>::iterator elistIt;
		bool found = false;
		// Mirar los enemigos de esta lista
		vector<Enemy*>::iterator enemyIt = screenEnemies->begin();
		while (enemyIt != screenEnemies->end())
		{
			if ((*enemyIt) != NULL)
			{
				// Se busca el enemigo en la lista de spawn
				elistIt = enemylist.begin();
				while (elistIt != enemylist.end() && !found)
				{
					found = (((*elistIt)->id == (*enemyIt)->spawnData.id) &&
							((*elistIt)->x == (*enemyIt)->spawnData.x) &&
							((*elistIt)->y == (*enemyIt)->spawnData.y));
					elistIt++;
				}
				// Sólo se añade si está (si no, está muerto)
				if (found)
				{
					// Se añade para la foto
					gamePlayState->_add((*enemyIt));
					// Y al buffer de locales
					gamePlayState->addLocal((*enemyIt));
				}
			}
			eIt++;
		}
	}
	else
	{
		// Mirar los del archivo
		vector<Enemy*>::iterator enemyIt = screenEnemies->begin();
		while (enemyIt != screenEnemies->end())
		{
			if ((*enemyIt) != NULL)
			{
				// Se añade para la foto
				gamePlayState->_add((*enemyIt));
				// Y al buffer de locales
				gamePlayState->addLocal((*enemyIt));
			}
			enemyIt++;
		}
	}
	delete screenEnemies;

	delete screenPuzzles;

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
				y = 4; 
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
		trans.effect = SCROLL;
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
	
		/* Se actualiza la localización actual, guardando la anterior */
		MapLocation oldLocation = data->getGameData()->getGameStatus()->getCurrentMapLocation();
		data->getGameData()->getGameStatus()->setCurrentMapLocation(target);

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

		// Obtener el offset de render
		std::pair<int, int> oldoff = gamePlayState->getOffset();

		// Limpiar las imágenes antes de empezar
		game->getGfxEngine()->clearImage(currentRoom, Color::Black);
		game->getGfxEngine()->clearImage(nextRoom, Color::Black);

		// Limpiar currentRoom si es necesario
		game->getGfxEngine()->setRenderTarget(currentRoom);
		gamePlayState->setOffset(0, 0);
		gamePlayState->onRender();
		gamePlayState->setOffset(oldoff.first, oldoff.second);
		game->getGfxEngine()->resetRenderTarget();
		
		currentRoom->refresh();


/* ---------------------------------------------------------------------
4. Mapa, cárgame los datos del nuevo mapa y borra los anteriores ( o buffer ). 
El nuevo mapa sustituirá al actual, contendrá a los players y el hud y además
las entidades cargadas deberán estar disabled (de eso me ocupo yo, Controller).
--------------------------------------------------------------------- */

		// se borran las locales en el tick siguiente, por lo que debemos desvisibilizarlas
		gamePlayState->hideLocals();
		gamePlayState->removeLocals();
		
		// think, qué pasa si no se carga, etc...
		if (!loadScreen(target))
		{
			// Devolvemos la localización a la anterior
			data->getGameData()->getGameStatus()->setCurrentMapLocation(oldLocation);
			return false; // fallar, avisar, salir
		}
				
/* ---------------------------------------------------------------------
5. Hazle foto al nuevo mapa.
--------------------------------------------------------------------- */

		// Limpiar nextRoom si es necesario

		game->getGfxEngine()->setRenderTarget(nextRoom);
		gamePlayState->setOffset(0, 0);
		gamePlayState->onRender();

		game->getGfxEngine()->resetRenderTarget();
		gamePlayState->setOffset(oldoff.first, oldoff.second);
		nextRoom->refresh();

		// Se ocultan las entidades locales por ahora
		std::list<Entity*>::iterator localIt = gamePlayState->localEntities->begin();
		while (localIt != gamePlayState->localEntities->end())
		{
			if ((*localIt) != NULL)
				(*localIt)->disable();
			localIt++;
		};

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

		return true;
	};
	return false;
};

bool Controller::teleportTo(MapLocation m, Player* p, TransitionEffect te, bool brute){

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
	}
	else
	{
		target.screenX = targetMap->getStartScreen().first;
		target.screenY = targetMap->getStartScreen().second;
		target.positionX = -1;
		target.positionY = -1;
	}
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
	// Si no viene dada, se coge la que indique la screen
	if (target.positionX == -1)
		target.positionX = screenMap->getScreenLocation().positionX;
	if (target.positionY == -1)
		target.positionY = screenMap->getScreenLocation().positionY;

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

TransitionEffect Controller::getTransitionEffect()
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

DataBaseInterface* Controller::getDataBaseInterface()
{
	return dbi;
}


HUDController* Controller::getHUDController()
{
	return hudController;
}

ToolController* Controller::getToolController()
{
	return toolController;
}

MessageController* Controller::getMessageController(){
	return messageController;
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
	std::list<Entity*>::iterator localIt = gamePlayState->localEntities->begin();
	while (localIt != gamePlayState->localEntities->end())
	{
		if ((*localIt) != NULL)
			(*localIt)->enable();
		localIt++;
	};
	// TO BE DONE
				
	setState(Controller::NORMAL);
};

DataPersistence* Controller::getData()
{
	return data;
};

bool Controller::readEntities(FILE* file, map<int, Entity*>* screenEntities, map<int, GamePuzzle*>* screenPuzzles)
{
	short nentBuf[1];
	if (fread(nentBuf, sizeof(short), 1, file) < 1)
		return false; // fallar, avisar, salir

	short nentities = nentBuf[0];

	struct EntityInfo
	{
		int id;
		EntityTypes type;
		int x, y;
		int idCol;
		int linked2;
		//Entity* ent;
	};

	// lista<linked2, Entity*>
	std::list<pair<int, pair<EntityInfo, Entity*> > > specialEntities;
	// lista<idEntidad, <tipo, entidad>>
	std::multimap<int, pair<EntityInfo, Entity*> > tempScreenEntities;

	EntityInfo entInfo;

	short entitiesBuf[5];
	Entity* ent = NULL;

	for (int i = 0; i < nentities; i++)
	{
		if (fread(entitiesBuf, sizeof(short), 5, file) < 1)
			return false;

		ent = NULL;
		entInfo.id = i;
		entInfo.type = (EntityTypes) entitiesBuf[0];
		entInfo.x = entitiesBuf[1]*screenMap->getTileset()->getTileW()*2; // OMG HAXX0R! (el x2 este habrá que quitarlo, es por el autotile)
		entInfo.y = entitiesBuf[2]*screenMap->getTileset()->getTileH()*2;
		entInfo.idCol = entitiesBuf[3];
		entInfo.linked2 = entitiesBuf[4];

		// Use them if needed, add them to screenEntities
		switch (entInfo.type)
		{
		case entDoor:
			{
				short doorBuf[1]; // tileId
				if (fread(doorBuf, sizeof(short), 1, file) < 1)
					break;
				// Crear puerta con ese dato
				Direction dir = NONE;
				if (entInfo.x < gamePlayState->roomw/4) dir = RIGHT;
				else if (entInfo.x > gamePlayState->roomw - gamePlayState->roomw/4) dir = LEFT;
				else if (entInfo.y < gamePlayState->roomh/4) dir = DOWN;
				else if (entInfo.y < gamePlayState->roomh - gamePlayState->roomh/4) dir = UP;

				MapStatus* ms = data->getMapData(data->getGameData()->getGameStatus()->getCurrentMapLocation().id)->getMapStatus();
				
				ent = new Door(entInfo.x, entInfo.y, dir, game, gamePlayState);
				((Door*) ent)->init(entInfo.idCol, ms, dbi->getDoorPath());
				((Door*) ent)->setDoorType(Door::KEYDOOR);
				((Door*) ent)->closed = !(ms->getDoorStatus(entInfo.idCol));
			}
			break;
		case entBossDoor:
			{
				short doorBuf[1]; // tileId
				if (fread(doorBuf, sizeof(short), 1, file) < 1)
					break;
				// Crear puerta con ese dato
				Direction dir = NONE;
				if (entInfo.x < gamePlayState->roomw/4) dir = RIGHT;
				else if (entInfo.x > gamePlayState->roomw - gamePlayState->roomw/4) dir = LEFT;
				else if (entInfo.y < gamePlayState->roomh/4) dir = DOWN;
				else if (entInfo.y < gamePlayState->roomh - gamePlayState->roomh/4) dir = UP;

				DungeonMapStatus* ms = (DungeonMapStatus*) data->getMapData(data->getGameData()->getGameStatus()->getCurrentMapLocation().id)->getMapStatus();
				
				ent = new Door(entInfo.x, entInfo.y, dir, game, gamePlayState);
				((Door*) ent)->init(entInfo.idCol, ms, dbi->getBossDoorPath());
				((Door*) ent)->setDoorType(Door::BOSSDOOR);
				((Door*) ent)->closed = !(ms->getDoorStatus(entInfo.idCol));
			}
			break;
		case Item:
			{
			short itemBuf[4]; // idItem, idGfx, effect, power
			if (fread(itemBuf, sizeof(short), 4, file) < 3)
			{
				ent = NULL; break;
			}
			// Si hay idCollectable, es un Collectable

			std::string gfxPath;
			std::string name;
			int itemId =  itemBuf[0];
			if (itemBuf[2] == GameItem::iePIGEON)
			{
				gfxPath = dbi->getImagePath(dbi->getPigeonData().gfxId);
				name = dbi->getPigeonData().name;
			}
			else
			{
				gfxPath = dbi->getImagePath(itemBuf[1]);
				name = dbi->getItemName(itemId);
			}

			if (entInfo.idCol != -1)
			{
				ent = new CollectableGameItem(entInfo.x, entInfo.y, game, gamePlayState),
					((CollectableGameItem*) ent)->init(entInfo.idCol, data->getMapData(data->getGameData()->getGameStatus()->getCurrentMapLocation().id)->getMapStatus(), gfxPath, (GameItem::ItemType) itemBuf[2], itemBuf[3], this, name);
			}
			else
			{
				ent = new GameItem(entInfo.x, entInfo.y, game, gamePlayState),
				((GameItem*) ent)->init(gfxPath, (GameItem::ItemType) itemBuf[2], itemBuf[3]);
			}

			break;
			}
		case  entTiledEntity:
			{
				short width;
				short nTiles;
				short tile;
				short* tilesType;

				if (fread(&width, sizeof(short), 1, file) < 1)
					break;

				if (fread(&nTiles, sizeof(short), 1, file) < 1)
					break;

				if (fread(&tile, sizeof(short), 1, file) < 1)
					break;

				tilesType = new short[nTiles];
				if (fread(tilesType, sizeof(short), nTiles, file) < nTiles)
					break;

				ent = new TiledEntity(entInfo.x, entInfo.y, game, gamePlayState);
				((TiledEntity*) ent)->init(screenMap->getTileset(), tile, tilesType, nTiles, width);
			}
			break;
		case DmgBlockade:
			{
				short blckBuf[3]; // idGfx, typeBlock (bogus for now), idDMG (vector de daño que lo abre)
					if (fread(blckBuf, sizeof(short), 3, file) < 3)
						break;
					ent = new DamageableBlockade(entInfo.x, entInfo.y, game, gamePlayState);
					// Hardcoded alto y ancho
					//((DamageableBlockade*) ent)->init(blckBuf[2], dbi->getImagePath(blckBuf[0]), 16, 16);
					// Crear bloqueo
			}
			break;
		case entTiledPushable:
			{
				short tiledBuf[1]; // idTile
				if (fread(tiledBuf, sizeof(short), 1, file) < 1)
					break;

				ent = new TiledPushable(entInfo.x, entInfo.y, game, gamePlayState);
				((TiledPushable*) ent)->init(gamePlayState->getMap()->getTileset()->getImg()->getPath(), tiledBuf[0]);

				// Crear tiledPusable
			}
			break;
		case entFloorButton:
			{
				short fbutBuf[1];
				if (fread(fbutBuf, sizeof(short), 1, file) < 1)
					break;
				// Crear botón
				ent = new FloorButton(entInfo.x, entInfo.y, game, gamePlayState);
				// No se puede iniciar aún, es especial
			}
			break;
		case entInstantiator:
			{
				// Este no tiene datos propios, pero ojito con él que hay que tratarlo de forma especial
				ent = new Instantiator(game, gamePlayState);
			}
			break;
		case entAbreDoors:
			{
				// Same as before
				ent = new DoorOpener(game, gamePlayState);
			}
			break;
		case entArena:
			{
				// Same as before
				ent = new ArenaEntity(entInfo.x, entInfo.y, game, gamePlayState);
			}
			break;
		case entTeleporter:
			{
				short tlprtBuf[5]; // mapId, screenX,Y, tileX,Y (y falta la dirección)
				if (fread(tlprtBuf, sizeof(short), 5, file) < 5)
					break;
				// Crear teleport
				MapLocation target; target.id = tlprtBuf[0]; target.screenX = tlprtBuf[1]; target.screenY = tlprtBuf[2]; target.positionX = tlprtBuf[3];  target.positionY = tlprtBuf[4];
				ent = new Teleporter(target, entInfo.x, entInfo.y, game, gamePlayState);
				((Teleporter*) ent)->setTeleportType(Teleporter::INSIDE);
			}
			break;
		case PickableTool:
			{
				short toolBuf[1]; // toolId
				if (fread(toolBuf, sizeof(short), 1, file) < 1)
					break;
				// Crear tool
				ent = new CollectableGameItem(entInfo.x, entInfo.y, game, gamePlayState);
				((CollectableGameItem*) ent)->init(entInfo.idCol, data->getMapData(data->getGameData()->getGameStatus()->getCurrentMapLocation().id)->getMapStatus(),
					toolController->getToolGraphicPath(toolBuf[0]), GameItem::ieTOOL, toolBuf[0], this, toolController->getToolName(toolBuf[0]));
				if (ent->graphic != NULL)
					delete ent->graphic;
				ent->graphic = toolController->getToolGraphic(toolBuf[0]);
			}
			break;
		default:
			break;
		}

		if (ent != NULL)
		{
			if (entInfo.linked2 != -1)
			{
				// Si linked2 es -1, es una cosa normal
				specialEntities.push_back(make_pair(entInfo.linked2, make_pair(entInfo, ent)));
			}
			else
			{
				// Si no, está linkada o que se yo
				// ¿Y qué pasa si hay una entidad ahi ya?
				tempScreenEntities.insert(make_pair(entInfo.id, make_pair(entInfo, ent)));
			}
		}
	}

	// Se manejan las specialEntities (las de linked2)
	int linked2 = -1;
	Entity* Ent = NULL;
	EntityTypes type;
	// Trabajamos sobre un buffer de entidades especiales temporales por si el orden en que aparecen las entidades
	// en el archivo es inútil para el linkado
	list<pair<int, pair<EntityInfo, Entity*> > > tempSpecialEntities;

	list<pair<int, pair<EntityInfo, Entity*> > >::iterator it = specialEntities.begin();
	while (it != specialEntities.end())
	{
		if ((*it).second.second != NULL)
		{
			Ent = (*it).second.second;
			linked2 = (*it).first;
			type = (*it).second.first.type;

			//EntityTypes t = (EntityTypes) ((int) ((*it).second.first));
			// Se mira el tipo
			switch (type)
			{
			case entDoor:
				{
				// Estará linkada a otra entidad
				// se busca en tempScreenEntities
					multimap<int, pair<EntityInfo, Entity*> >::iterator sit = tempScreenEntities.find(linked2);
					// Encontramos el elemento en las tempScreenEntities
					if (sit != tempScreenEntities.end())
					{
						switch (sit->second.first.type)
						{
						case entAbreDoors:
							((DoorOpener*) (sit->second.second))->addDoor((Door*) Ent);
							break;
						default:
							break;
						}

						tempScreenEntities.insert(make_pair(linked2, make_pair(it->second.first, Ent)));
					}
					else 
					{
						/* Deprecated
						// No se encuentra la entidad (estará en las especiales, pero debemos esperar a que se inicie)
						// Se quita de la lista
						it = specialEntities.erase(it);
						// Y se añade al final
						specialEntities.push_back(make_pair(linked2, make_pair(type, Ent)));
						advance = false;*/

						// Se añade la entidad al ppio de la lista de especiales temporal para ser tratada después.
						tempSpecialEntities.push_front(make_pair(linked2, make_pair(it->second.first, Ent)));
					}
				}
				break;
			case entBossDoor:
				{
				// Estará linkada a otra entidad
				// se busca en screenEntities
				// si no está, en specialEntities (pero después?, en otra pasada?)
				int n = 2;
				}
				break;
			case Item:
				{
				// Estará linkada a otra entidad mediante un idEntity
				
				// si no está, en specialEntities (pero después?, en otra pasada?)

					// se busca en tempScreenEntities
					multimap<int, pair<EntityInfo, Entity*> >::iterator sit = tempScreenEntities.find(linked2);
					// Encontramos el elemento en las tempScreenEntities
					if (sit != tempScreenEntities.end())
					{
						switch (sit->second.first.type)
						{
						case entInstantiator:
							((Instantiator*) (sit->second.second))->addEntity(Ent);
							break;
						default:
							break;
						}
					}
					else 
					{
						/* Deprecated
						// No se encuentra la entidad (estará en las especiales, pero debemos esperar a que se inicie)
						// Se quita de la lista
						it = specialEntities.erase(it);
						// Y se añade al final
						specialEntities.push_back(make_pair(linked2, make_pair(type, Ent)));
						advance = false;*/

						// Se añade la entidad al ppio de la lista de especiales temporal para ser tratada después.
						tempSpecialEntities.push_front(make_pair(linked2, make_pair(it->second.first, Ent)));
					}
				}
				break;
			case entTiledEntity:
				{
				// Estará linkada a otra entidad
				// se busca en screenEntities
				// si no está, en specialEntities (pero después?, en otra pasada?)
				int n = 2;
				}
				break;
			case DmgBlockade:
				{
				// Estará linkada a otra entidad
				// se busca en screenEntities
				// si no está, en specialEntities (pero después?, en otra pasada?)
				int n = 2;
				}
				break;
			case entTiledPushable:
				{
					// Estará linkada a otra entidad
					// se busca en screenEntities
					// si no está, en specialEntities (pero después?, en otra pasada?)
					pair<multimap<int, pair<EntityInfo, Entity*> >::iterator,
						multimap<int, pair<EntityInfo, Entity*> >::iterator> range = tempScreenEntities.equal_range(linked2);
					multimap<int, pair<EntityInfo, Entity*> >::iterator sit;
					// Encontramos el elemento en las tempScreenEntities
					if (range.first != range.second)
					{
						for (sit = range.first; sit != range.second;  sit++)
						{
							switch (sit->second.first.type)
							{
							case entInstantiator:
								((Instantiator*) (sit->second.second))->addEntity(Ent);
								break;
							default:
								break;
							}
						}
					}
					else
					{
						/* Deprecated
						// No se encuentra la entidad (estará en las especiales, pero debemos esperar a que se inicie)
						// Se quita de la lista
						it = specialEntities.erase(it);
						// Y se añade al final
						specialEntities.push_back(make_pair(linked2, make_pair(type, Ent)));
						advance = false;*/

						// Se añade la entidad al ppio de la lista de especiales temporal para ser tratada después.
						tempSpecialEntities.push_front(make_pair(linked2, make_pair(it->second.first, Ent)));
					}
				}
				break;
			case entFloorButton: 
				{
					// Hay que iniciarlo con el puzzle
					// linked2 será un idPuzzle => se coge el puzzle de la lista de puzzles
					map<int, GamePuzzle*>::iterator pit = screenPuzzles->find(linked2);
					if (pit != screenPuzzles->end())
						((FloorButton*) Ent)->init(pit->second);
					else
						int n = 2; //?

					// Se añade a temporales
					tempScreenEntities.insert(make_pair(it->second.first.id, make_pair(it->second.first, Ent)));
				}
				break;
			case entInstantiator:
				{
					// Hay que iniciarlo con el puzzle
					// linked2 será un idPuzzle => se coge el puzzle de la lista de puzzles
					map<int, GamePuzzle*>::iterator pit = screenPuzzles->find(linked2);
					if (pit != screenPuzzles->end())
						((Instantiator*) Ent)->init(pit->second);
					else
						int n = 2; //?

					// Y se puede añadir aunque no tenga todas las entidades, a que sí!
					tempScreenEntities.insert(make_pair(it->second.first.id, make_pair(it->second.first, Ent)));
				}
				break;
			case entAbreDoors:
				{
					// Hay que iniciarlo con el puzzle
					// linked2 será un idPuzzle => se coge el puzzle de la lista de puzzles
					map<int, GamePuzzle*>::iterator pit = screenPuzzles->find(linked2);
					if (pit != screenPuzzles->end())
						((DoorOpener*) Ent)->init(pit->second);
					else
						int n = 2; //?

					tempScreenEntities.insert(make_pair(it->second.first.id, make_pair(it->second.first, Ent)));
				}
				break;
			case entArena:
				{
					// Hay que iniciarlo con el puzzle
					// linked2 será un idPuzzle => se coge el puzzle de la lista de puzzles
					map<int, GamePuzzle*>::iterator pit = screenPuzzles->find(linked2);
					if (pit != screenPuzzles->end())
						((ArenaEntity*) Ent)->init(pit->second);
					else
						int n = 2; //?

					tempScreenEntities.insert(make_pair(it->second.first.id, make_pair(it->second.first, Ent)));
				}
				break;
			case entTeleporter:
				{
					// Si está linkado a algo deberá ser un instantiator
				}
				break;
			case PickableTool:
				break;
			case entDoorCloser:
				{
					/* Not yet

					// Hay que iniciarlo con el puzzle
					// linked2 será un idPuzzle => se coge el puzzle de la lista de puzzles
					map<int, GamePuzzle*>::iterator pit = screenPuzzles->find(linked2);
					if (pit != screenPuzzles->end())
						((DoorCloser*) Ent)->init(pit->second);
					else
						int n = 2; //?

					tempScreenEntities.insert(make_pair(it->second.first.id, make_pair(it->second.first, Ent)));*/
				}
				break;
			default:
				break;
			}
		}
		it++;
		// Al terminar, si quedan cosas por trabajar, repetimos
		if (it == specialEntities.end())
		{
			// Si queda algo que tratar
			if (!tempSpecialEntities.empty())
			{
				// Podemos descargar la lista antigua y seguir con la temporal
				specialEntities = tempSpecialEntities;
				tempSpecialEntities.clear();
				it = specialEntities.begin();
			}
		}
	}

	// Recorremos tempScreenEntities y las que haya las añadimos al GamePlayState
	multimap<int, pair<EntityInfo, Entity*> >::iterator tempIt = tempScreenEntities.begin();
	while (tempIt != tempScreenEntities.end())
	{
		if ((*tempIt).second.second != NULL)
		{
			int id = (*tempIt).first;
			screenEntities->insert(make_pair(id, (*tempIt).second.second));
		}
		tempIt++;
	};

	return true;
};

bool Controller::readEnemies(FILE* file, vector<Enemy*>* screenEnemies, map<int, Entity*>* screenEntities)
{
	if (file == NULL)
		return false;

	// ENEMIES
	short nenenemiesBuf[1];
	if (fread(nenenemiesBuf, sizeof(short), 1, file) < 1)
		return false; // fallar, avisar, salir

	short nenenemies = nenenemiesBuf[0];

	//vector<Enemy*>* tempScreenEnemies = new vector<Enemy*>();
	
	short enemyBuf[4];
	int eneId;
	int eneX;
	int eneY;
	int linked2 = -1;

	Enemy* enemy = NULL;

	for (int i = 0; i < nenenemies; i++)
	{
		if (fread(enemyBuf, sizeof(short), 4, file) < 1)
			return false;

		// Use them if needed
		eneId = enemyBuf[0];
		eneX = enemyBuf[1]*screenMap->getTileset()->getTileW()*2; // Hax0r! (x2 del autotile)
		eneY = enemyBuf[2]*screenMap->getTileset()->getTileH()*2;
		linked2 = enemyBuf[3];

		// Coger datos de la database en funcion del id
		enemy = new Enemy(game, gamePlayState);
		EnemySpawnData spw;
		spw.id = eneId;
		spw.x = eneX;
		spw.y = eneY;
		vector<Component*>* components = new vector<Component*>();
		ComponentAnim* cAnim = NULL;
		/**/
		cAnim = readComponents(eneId, enemy, components);
		if (cAnim != NULL)
			enemy->init(spw, components, cAnim, 5, 5, 8, 0);
		else
		{
			vector<Component*>::iterator it = components->begin();
			while (it != components->end())
			{
				if ((*it) != NULL)
					delete (*it);
				it++;
			}
			delete components;
		}

		if (linked2 == -1)
		{
			// Es normal, va directo a screenEnemies
			screenEnemies->push_back(enemy);
		}
		else
		{
			// No es normal, habrá que gozarlo con él
			// Irá linkado a una entidad de nivel intermedio
			// Se busca la entidad en las de la pantalla:
			Entity* e = NULL;
			map<int, Entity*>::iterator entIt = screenEntities->find(linked2);

			if (entIt != screenEntities->end())
				 e = screenEntities->at(linked2);
			if (e == NULL)
			{
				// No se encuentra el linked2, ¿la borramos?
			}
			else
			{
				// Se ha encontrado, ahora checkeamos tipo
				ArenaEntity* ae = NULL;
				Instantiator* ins = NULL;
				if (ae = dynamic_cast<ArenaEntity*>(e))
				{
					// Se linka a la arena
					ae->addEnemy(enemy);
					// y se añade al gamestate
					screenEnemies->push_back(enemy);
				}
				else if (ins = dynamic_cast<Instantiator*>(e))
				{
					// se linka al instantiator y a correr
					ins->addEntity(enemy);
				}
				else
				{
					// Pero a qué narices se está intentando linkar?
					int n = 2;
				}
			}
		}
	}

	return true;
}

bool Controller::loadInputConfig(InputConfig& ic, std::string path)
{
	// Carga el archivo de config y lee
	FILE* f = fopen(path.c_str(), "r");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	// 1. Tipo de control (gamepad o teclado)
	if (fscanf(f, "%d", &ic.joyMode) < 1)
		return false;
	
	// Por teclado
	if (!ic.joyMode)
	{
		if (fscanf(f, "%d", &ic.keyLeft) < 1)
			return false;
		if (fscanf(f, "%d", &ic.keyRight) < 1)
			return false;
		if (fscanf(f, "%d", &ic.keyUp) < 1)
			return false;
		if (fscanf(f, "%d", &ic.keyDown) < 1)
			return false;

		if (fscanf(f, "%d", &ic.keyA) < 1)
			return false;
		if (fscanf(f, "%d", &ic.keyB) < 1)
			return false;
		if (fscanf(f, "%d", &ic.keySTART) < 1)
			return false;
		if (fscanf(f, "%d", &ic.keySELECT) < 1)
			return false;
	}
	// Por gamepad
	else
	{
		if (fscanf(f, "%d", &ic.gamePad) < 1)
			return false;
		if (fscanf(f, "%d", &ic.xAxis) < 1)
			return false;
		if (fscanf(f, "%d", &ic.yAxis) < 1)
			return false;

		if (fscanf(f, "%d", &ic.joyA) < 1)
			return false;
		if (fscanf(f, "%d", &ic.joyB) < 1)
			return false;
		if (fscanf(f, "%d", &ic.joySTART) < 1)
			return false;
		if (fscanf(f, "%d", &ic.joySELECT) < 1)
			return false;
	}

	fclose(f);

	return true;
}

void Controller::save(){
	data->save();
}

void Controller::changeGameStateTo(GameScreens target)
{
	switch (target)
	{
	case TITLE:
		if (currentScreen == GAMEPLAY)
		{
			((PGZGame*) game)->resetGame();
			currentScreen = TITLE;
		}
	}
}

ComponentAnim* Controller::readComponents(int idEnemy, Enemy* enemy, std::vector<Component*>* comps)
{
	ComponentAnim* anim;
	DataBaseInterface::EnemyData edata = dbi->getEnemyData(idEnemy);
	std::string fname = dbi->getEnemyComponentsPath(idEnemy);
	
	// Se abre el archivo y comienza la fiesta
	FILE* file = fopen(fname.c_str(), "r");
	if (file == NULL)
		return NULL;
	else
	{
		// Se lee el componentAnim
		int idAnim;
		if (fscanf(file, "%d", &idAnim) < 1)
			return NULL;
		switch ((Component::ComponentType) idAnim)
		{
		case Component::CompAnim:
			anim = new ComponentAnim(game, enemy, edata.gfxPath);
			break;
		case Component::CompAnimFlying:
			anim = new ComponentAnimFlying(game, enemy, edata.gfxPath);
			break;
		default:
			return NULL;
		}

		// Se lee el nº de componentes
		int numComps = 0, idComp = 0;
		if (fscanf(file, "%d", &numComps) < 1)
			return NULL;
		// Se lee cada componente
		for (int i = 0; i < numComps; i++)
		{
			if (fscanf(file, "%d", &idComp) < 1)
				return NULL;
			
			switch ((Component::ComponentType) idComp)
			{
			case Component::CompBat:
				comps->push_back(new ComponentBatMovement(game, this));
				break;
			case Component::CompMelee:
				comps->push_back(new ComponentMelee(game, this));
				break;
			case Component::CompMeleeSimple:
				comps->push_back(new ComponentMeleeSimple(game, this));
				break;
			case Component::CompTackle:
				comps->push_back(new ComponentTackle(game, this));
				break;
			case Component::CompTiledMovement:
				comps->push_back(new ComponentTiledMovement(game, this));
				break;
			case Component::CompTest:
				comps->push_back(new ComponentTester(game, this));
				break;
			default:
				break;
			}
		}
	}

	return anim;
}