#include "StateMenu.h"


StateMenu::StateMenu(int x, int y, Game* game, GameState* gstate) : GameMenuController(x, y, game, gstate)
{
	((GamePlayState*) world)->pauseGameEntities();

	//Creamos el grafico del fondo y el del cursor---------------Pedirla a la base de datos
	setGraphic(new Stamp("data/graphics/StateMenuBackground.png", game->getGfxEngine()));

	//Elijo el grafico del cursor--------------------Pedirlo a la base de datos
	setCursorImage(new Stamp("data/graphics/cursor.png", game->getGfxEngine()));

	//Defino el color que usaremos para tintar las piezas de corazon o objetos clave no conseguidos
	Color colorDisabled = Color(20,20,20);

	//-------------------------------------------------------------------------------------------------
	//Aqui se crea el item para el save y para el exit

	//Creamos la fuente para los textos del menu ------------------Hay que pedirla de la base de datos
	menuFont = new TileFont("data/graphics/sprFont_strip94.png",game->getGfxEngine());

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
		keyItem->graphic = (new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getKeyItemData().gfxPath, game->getGfxEngine()));
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
	//-------------------------------------------------------------------------------------------------------
	//Aqui se crean las piezas de corazon
	//Se mira a ver cuantas piezas de corazón tiene el player, por ahora me lo invento
	/*int numPieces = 3;

	GameMenuItem* heartPiece = new GameMenuItem((3*game->getGfxEngine()->getGameScreenWidth()/4) + 18 , 30, game, gstate);
	heartPiece->graphic = (new Stamp("data/graphics/bigHeartUL.png", game->getGfxEngine()));
	if(numPieces <= 0)
		heartPiece->graphic->setColor(colorDisabled);
	heartPieces[0] = heartPiece;

	heartPiece = new GameMenuItem(heartPieces[0]->x + heartPieces[0]->graphic->getWidth() , 30, game, gstate);
	heartPiece->graphic = (new Stamp("data/graphics/bigHeartUR.png", game->getGfxEngine()));
	if(numPieces <= 1)
		heartPiece->graphic->setColor(colorDisabled);
	heartPieces[1] = heartPiece;

	heartPiece = new GameMenuItem(heartPieces[0]->x + heartPieces[0]->graphic->getWidth() , heartPieces[0]->y + heartPieces[0]->graphic->getHeight(), game, gstate);
	heartPiece->graphic = (new Stamp("data/graphics/bigHeartDR.png", game->getGfxEngine()));
	if(numPieces <= 2)
		heartPiece->graphic->setColor(colorDisabled);
	heartPieces[2] = heartPiece;

	heartPiece = new GameMenuItem((3*game->getGfxEngine()->getGameScreenWidth()/4) + 18 , heartPieces[0]->y + heartPieces[0]->graphic->getHeight(), game, gstate);
	heartPiece->graphic = (new Stamp("data/graphics/bigHeartDL.png", game->getGfxEngine()));
	if(numPieces <= 3)
		heartPiece->graphic->setColor(colorDisabled);
	heartPieces[3] = heartPiece;*/

	//------------------------------------------------------------------------------------------------------
	// Aqui se añade siempre, si se pinta o no ya depende de launch()

		bossKey = new GameMenuItem((3*game->getGfxEngine()->getGameScreenWidth()/4) + 18 , 30, game, gstate);
		bossKey->graphic = (new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getBossKeyData(), game->getGfxEngine()));
		//Si no la tiene se oscurece
		
	//-------------------------------------------------------------------------------------------------------
	//Aqui se añaden las pidgeons y su texto

	pidgeons = new GameMenuItem(bossKey->x, bossKey->y + bossKey->graphic->getHeight() + 35, game, gstate);
	pidgeons->graphic = (new Stamp(((PGZGame*)game)->controller->getDataBaseInterface()->getPigeonData().gfxPath, game->getGfxEngine()));

	//Aqui habria que pedir el numero de pidgeons y concatenar x con numPidgeons para escribir el texto
	int numPidgeons = 0;//((PGZGame*)game)->controller->getData()->getGameData()->getGameStatus()->getNumPidgeons();
	char buf[256];
	string tmp  = "";

	tmp += "x";
	tmp += itoa(numPidgeons, buf, 10);

	tPidgeons = new GameMenuTextItem(tmp, menuFont, pidgeons->x + pidgeons->graphic->getWidth(),
								pidgeons->y + pidgeons->graphic->getHeight(), game, gstate);

	tPidgeons->setPos(tPidgeons->x - tPidgeons->graphic->getWidth(), tPidgeons->y - tPidgeons->graphic->getHeight());
	//-------------------------------------------------------------------------------------------------------------------
	//Aqui creo el minimapa que corresponda
		miniMap = new GameMenuItem(0, 0, game, gstate);
		FriendlyTileMap* mp = getMiniMap();
		miniMap->graphic = mp;
}

StateMenu::~StateMenu()
{
	if (menuFont)
		delete menuFont,menuFont = NULL;

	if (keyItems)
		delete keyItems, keyItems = NULL;
}


FriendlyTileMap* StateMenu::getMiniMap()
{
	MapLocation currentMap = ((PGZGame*)game)->controller->getData()->getGameData()->getGameStatus()->getCurrentMapLocation();
	if (((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getType() == 0)
	{
		FriendlyTileMap* mp = new FriendlyTileMap(8,8,game->getGfxEngine());

		//Asigno el tileset
		mp->setTileSet("data/graphics/room.png");
	
		//Creo el mapa del tileset
		int**map = (int**) malloc((((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth())*sizeof(int*));
		for (int i = 0; i < (((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth());i++)
			map[i] = (int*) malloc((((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getHeight())*sizeof(int));

		const int** miLayout = ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getLayout();
		for (int i = 0; i < ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getHeight();i++)
			for (int j = 0; j < ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth();j++)
			{
				if (miLayout[i][j] == 1)
					map[i][j] = 0;
				else 
					map[i][j] = 1;
			}
		mp->setMap(map, ((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getWidth(),
						((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getHeight());

		return mp;
	}
}


void StateMenu::launch()
{
	//Añadimos todos los elementos al menu
	for (int i = 0; i < keyItems->size(); i++)
		addMenuItem(keyItems->at(i));
	
	//Añadimos el boton de guardar y el de salir
	addMenuItem(save);
	addMenuItem(exit);

	//Añadimos el minimapa
	addMenuItem(miniMap);


	//Añadimos la llave del boss, la brujula y el mapa
	MapLocation currentMap = ((PGZGame*)game)->controller->getData()->getGameData()->getGameStatus()->getCurrentMapLocation();
	if (((PGZGame*)game)->controller->getData()->getMapData(currentMap.id)->getType() == 1)
		addMenuItem(bossKey);


	//Añadimos las pidgeons y su texto
	addMenuItem(pidgeons);
	addMenuItem(tPidgeons);


	//Lanzamos el menu
	GameMenuController::launch();
}

void StateMenu::onCancelled(iSelectable* selectable)
{
	quit();
	((GamePlayState*) world)->unpauseGameEntities();
}


void StateMenu::onRender()
{
	if (visible)
	{
		Entity::onRender();
		cursorImage->render(cursorPosX + ((GamePlayState*) world)->getOffset().first, cursorPosY + ((GamePlayState*) world)->getOffset().second);
	}
}