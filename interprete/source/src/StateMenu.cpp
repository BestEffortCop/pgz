#include "StateMenu.h"


StateMenu::StateMenu(int x, int y, Game* game, GameState* gstate) : GameMenuController(x, y, game, gstate)
{
	((GamePlayState*) world)->pauseGameEntities();

	//Creamos el grafico del fondo y el del cursor---------------Pedirla a la base de datos
	setGraphic(new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getStateMenuBorders(), game->getGfxEngine()));

	//Elijo el grafico del cursor--------------------Pedirlo a la base de datos
	setCursorImage(new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getCursorStateSave(), game->getGfxEngine()));

	//Defino el color que usaremos para tintar las piezas de corazon o objetos clave no conseguidos
	Color colorDisabled = Color(90,90,90);

	//inicio el focus a la pantalla general
	focus = MAIN;

	//-------------------------------------------------------------------------------------------------
	//Aqui se crea el item para el save y para el exit

	saveExit = new GameMenuItemS(3*game->getGfxEngine()->getGameScreenWidth()/4 + 8,
								3*game->getGfxEngine()->getGameScreenWidth()/4 - 7, game, gstate);



	//Creamos la fuente para los textos del menu ------------------Hay que pedirla de la base de datos
	menuFont = new TileFont(((PGZGame*)game)->controller->getDataBaseInterface()->getFont(),game->getGfxEngine());

	save = new GameMenuTextItemS("Save", menuFont, 3*game->getGfxEngine()->getGameScreenWidth()/4 + 20,
								3*game->getGfxEngine()->getGameScreenWidth()/4, game, gstate);
	save->setCursorLocation(LEFT);

	exit = new GameMenuTextItemS("Exit", menuFont, 3*game->getGfxEngine()->getGameScreenWidth()/4 + 20,
								3*game->getGfxEngine()->getGameScreenWidth()/4 + 8, game, gstate);
	exit->setCursorLocation(LEFT);
	//--------------------------------------------------------------------------------------------------
	//Aqui se crea el array de objetos clave
	//Creo el array de objetos clave y un iterador para el mismo, asi como un auxiliar
	keyItems = new vector<GameMenuItem*>;
	std::vector<GameMenuItem*>::iterator it = keyItems->begin();
	GameMenuItem* keyItem = NULL;
	
	//Pido el grafico del objeto clave, por ahora me lo invento
	//Pido el numero maximo de objetos clave, que por ahora, tambien me lo invento
	//Y pido el numero de objetos clave conseguidos que tambien me lo invento
	int nKeyObj = 22;/////////////////////Pedir a gameStatus creo
	int nKeyObjObt = ((PGZGame*)game)->controller->getData()->getGameData()->getGameStatus()->getNumKeyItems();

	//Posicion del primer objeto clave
	int a = 10;
	int b = 3*game->getGfxEngine()->getGameScreenHeight()/4;

	//Ahora añado los objetos clave
	for (int i = 0; i < nKeyObj;i++)
	{
		keyItem = new GameMenuItem(a, b, game, gstate);
		//Metemos el grafico --------------Pedir el grafico a dataBaseInterface
		keyItem->graphic = (new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getImagePath(((PGZGame*)game)->controller->getDataBaseInterface()->getKeyObjData().gfxId), game->getGfxEngine()));
		//Si la no tenemos el objeto clave entonces saldrá griseado
		if (i >= nKeyObjObt)
			keyItem->graphic->setColor(colorDisabled);
		//La añadimos
		keyItems->insert(it,keyItem);
		it = keyItems->end();

		//Calculamos la posicion del nuevo objeto clave
		a = a + ((3*game->getGfxEngine()->getGameScreenWidth()/4) - keyItem->graphic->getWidth())/nKeyObj;
	}
	//Ahora pongo a NULL el auxiliar de antes
	keyItem = NULL;
	//------------------------------------------------------------------------------------------------------
	// Aqui se añade siempre, si se pinta o no ya depende de launch()

		bossKey = new GameMenuItem((3*game->getGfxEngine()->getGameScreenWidth()/4) + 16 , 30, game, gstate);
		bossKey->graphic = (new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getBossKeyData(), game->getGfxEngine()));
		bossKey->graphic->setScale(2.f,2.f);
		//Si no la tiene se oscurece
		MapLocation currentMap = ((PGZGame*)game)->controller->getData()->getGameData()->getGameStatus()->getCurrentMapLocation();
		if (! ((DungeonMapStatus*) ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getMapStatus())->isBossKeyGot())
			bossKey->graphic->setColor(colorDisabled);
		
	//-------------------------------------------------------------------------------------------------------
	//Aqui se añaden las pidgeons y su texto

	pidgeons = new GameMenuItem(bossKey->x, bossKey->y + bossKey->graphic->getHeight() + 40, game, gstate);
	pidgeons->graphic = (new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getImagePath(((PGZGame*)game)->controller->getDataBaseInterface()->getPigeonData().gfxId), game->getGfxEngine()));
	pidgeons->graphic->setScale(2.0f,2.0f);

	//Aqui habria que pedir el numero de pidgeons y concatenar x con numPidgeons para escribir el texto
	int numPidgeons = ((PGZGame*)game)->controller->getData()->getGameData()->getGameStatus()->getNumPigeons();
	int maxPidgeons = ((PGZGame*)game)->controller->getData()->getGameData()->getGameStatus()->getMaxPigeons();
	char buf[256];
	string tmp  = "";

	tmp += itoa(numPidgeons, buf, 10);
	tmp += "/";
	tmp += itoa(maxPidgeons, buf, 10);

	tPidgeons = new GameMenuTextItem(tmp, menuFont, pidgeons->x + pidgeons->graphic->getWidth()*pidgeons->graphic->getScaleV(),
								pidgeons->y + pidgeons->graphic->getHeight()*pidgeons->graphic->getScaleH(), game, gstate);

	tPidgeons->setPos(tPidgeons->x - (tPidgeons->graphic->getWidth()*tPidgeons->graphic->getScaleV()), tPidgeons->y);// - (tPidgeons->graphic->getHeight()*tPidgeons->graphic->getScaleH()));
	tPidgeons->graphic->setScale(2.f, 2.f);
	//-------------------------------------------------------------------------------------------------------------------
	//Aqui creo el minimapa que corresponda y su fondo
		backgroundMiniMap = new GameMenuItem(0, 0, game, gstate);
		bgImage = new Image(176,176,game->getGfxEngine());
		game->getGfxEngine()->renderRectangle(0,0, 176, 176, Color::Black,false,bgImage);
		backgroundMiniMap->graphic = new Stamp(bgImage,game->getGfxEngine());
		backgroundMiniMap->depth = 299;
		
		miniMap = new GameMenuItemS(0, 0, game, gstate);
		FriendlyTileMap* mp = getMiniMap();
		miniMap->graphic = mp;
		miniMap->setPos(88 - (miniMap->graphic->getWidth() / 2), 80 - (miniMap->graphic->getHeight() / 2));
		miniMap->depth = 300;
}

StateMenu::~StateMenu()
{
	if (menuFont)
		delete menuFont,menuFont = NULL;

	if (keyItems)
		delete keyItems, keyItems = NULL;

	delete bgImage;
}


FriendlyTileMap* StateMenu::getMiniMap()
{
	MapLocation currentMap = ((PGZGame*)game)->controller->getData()->getGameData()->getGameStatus()->getCurrentMapLocation();
	if (((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getType() == 0)
	{
		FriendlyTileMap* mp = new FriendlyTileMap(8,8,game->getGfxEngine());

		//Asigno el tileset
		mp->setTileSet(((PGZGame*)game)->controller->getDataBaseInterface()->getRoom());
	
		//Creo el mapa del tileset
		int**map = (int**) malloc((((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth())*sizeof(int*));
		for (int i = 0; i < (((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth());i++)
			map[i] = (int*) malloc((((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getHeight())*sizeof(int));

		const int** miLayout = ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getLayout();
		for (int i = 0; i < ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getHeight();i++)
			for (int j = 0; j < ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth();j++)
			{
				if (miLayout[j][i] != 0)
					map[j][i] = miLayout[j][i] - 1;
				else
					map[j][i] = 39;
				if ((currentMap.screenX == j) && (currentMap.screenY == i))
					map[j][i] = 19;
			}
		mp->setMap(map, ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth(),
						((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getHeight());

		return mp;
	}else 
	{
		//Aqui van los mapas de mazmorra
		FriendlyTileMap* mp = new FriendlyTileMap(8,8,game->getGfxEngine());

		//Asigno el tileset
		mp->setTileSet(((PGZGame*)game)->controller->getDataBaseInterface()->getRoom());
	
		//Creo el mapa del tileset
		int**map = (int**) malloc((((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth())*sizeof(int*));
		for (int i = 0; i < (((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth());i++)
			map[i] = (int*) malloc((((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getHeight())*sizeof(int));

		const int** miLayout = ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getLayout();
		for (int i = 0; i < ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getHeight();i++)
			for (int j = 0; j < ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth();j++)
			{
				if (miLayout[j][i] != 0)
					map[j][i] = miLayout[j][i] + 19;
				else
					map[j][i] = 39;
				if ((currentMap.screenX == j) && (currentMap.screenY == i))
					map[j][i] = 19;
			}
		mp->setMap(map, ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth(),
						((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getHeight());

		return mp;
	}
}


void StateMenu::moveMap(Direction dir)
{
	if (dir == RIGHT || dir == UPRIGHT || dir == DOWNRIGHT)
	{
		if ((miniMap->x - 8) < 0)
			miniMap->x = miniMap->x + 8;
	}
	if (dir == LEFT || dir == UPLEFT || dir == DOWNLEFT)
	{
		if ((miniMap->x + 8 + miniMap->graphic->getWidth()) > 176)
			miniMap->x = miniMap->x - 8;
	}
	if (dir == UP || dir == UPRIGHT || dir == UPLEFT)
	{
		if ((miniMap->y + 8 + miniMap->graphic->getHeight()) > 160)
			miniMap->y = miniMap->y - 8;
	}
	if (dir == DOWN || dir == DOWNLEFT || dir == DOWNRIGHT)
	{
		if ((miniMap->y - 8) < 0)
			miniMap->y = miniMap->y + 8;
	}
}


void StateMenu::launch()
{
	//Añadimos todos los elementos al menu
	for (int i = 0; i < (int) keyItems->size(); i++)
		addMenuItem(keyItems->at(i));
	
	//Añadimos el boton de guardar y el de salir
	addMenuItem(saveExit);
	addMenuItem(save);
	addMenuItem(exit);

	//Añadimos el minimapa
	addMenuItem(backgroundMiniMap);
	addMenuItem(miniMap);


	//Añadimos la llave del boss, la brujula y el mapa
	MapLocation currentMap = ((PGZGame*)game)->controller->getData()->getGameData()->getGameStatus()->getCurrentMapLocation();
	if (((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getType() == 1)
		addMenuItem(bossKey);
	else
		delete bossKey;


	//Añadimos las pidgeons y su texto
	addMenuItem(pidgeons);
	addMenuItem(tPidgeons);


	//Lanzamos el menu
	GameMenuController::launch();
}

void StateMenu::onCancelled(iSelectable* selectable)
{
	if (focus == MAIN )
	{
		quit();
		((GamePlayState*) world)->unpauseGameEntities();
	}
	else 
	{
		if (focus == MAP)
		{
			setCursorImage(new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getCursorStateMap(), game->getGfxEngine()));
			setSelected(miniMap);
		}
		else 
		{
			setSelected(saveExit);
			setCursorImage(new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getCursorStateSave(), game->getGfxEngine()));
		}
	focus = MAIN;
	}
}


void StateMenu::onChosen(iSelectable* selectable)
{
	if (selectable)
	{
		if (focus == MAIN)
		{
			GameMenuItemS* elem = ((GameMenuItemS*)selectable);
			if (elem == saveExit)
			{
				focus = SAVEEXIT;
				setCursorImage(new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getCursor(), game->getGfxEngine()));
				setSelected(save);
			}
			if (elem == miniMap)
			{
				focus = MAP; 
				setCursorImage(new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getCursorMiniMap(), game->getGfxEngine()));
				setSelected(miniMap);
			}
		}
		else if (focus == SAVEEXIT)
		{
			GameMenuTextItemS* elem = ((GameMenuTextItemS*)selectable);
			if (elem == save)
			{
				((PGZGame*)game)->controller->save();
			}
			if (elem == exit)
			{
				((PGZGame*)game)->controller->changeGameStateTo(Controller::TITLE);
			}
		}
	}
}

void StateMenu::onSelectPressed(iSelectable* selectable)
{
	quit();
	((GamePlayState*) world)->unpauseGameEntities();
}

void StateMenu::onRender()
{
	if (visible)
	{
		//game->getGfxEngine()->renderRectangle(0,0,176,176,Color::Black,false);
		Entity::onRender();
		if (cursorImage)
			cursorImage->render(cursorPosX + ((GamePlayState*) world)->getOffset().first, cursorPosY + ((GamePlayState*) world)->getOffset().second);
	}
}

iSelectable* StateMenu::getMandatorySelectable(iSelectable* slc, Direction dir)
{
	if (focus == MAIN )
	{
		if (slc == saveExit)
		{
			setCursorImage(new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getCursorStateMap(), game->getGfxEngine()));
			return miniMap;
		}
		else if (slc == miniMap)
		{
			setCursorImage(new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getCursorStateSave(), game->getGfxEngine()));
			return saveExit;
		}
		else return NULL;
	}
	else if (focus == SAVEEXIT)
	{
		if (slc == save)
			return exit;
		else if (slc == exit)
			return save;
		else 
			return save;
	}
	else if (focus == MAP)
	{
		moveMap(dir);
		return slc;
	}
	else return NULL;
}