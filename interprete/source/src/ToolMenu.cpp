#include "ToolMenu.h"


ToolMenu::ToolMenu(int x, int y, Game* game, GameState* gstate, int centroX, int centroY, int radio) : GameMenuController(x, y, game, gstate)
{
	((GamePlayState*) world)->pauseGameEntities();
	
	//Creamos la fuente para el texto que se pintará debajo
	menuFont = new TileFont(((PGZGame*) game)->controller->getDataBaseInterface()->getFont(), game->getGfxEngine());

	//Creamos el grafico del fondo y el del cursor
	setGraphic(new Stamp(((PGZGame*) game)->controller->getDataBaseInterface()->getToolMenuBackground(), game->getGfxEngine()));
	graphic->setAlpha(0.7f);
	setCursorImage(new Stamp(((PGZGame*) game)->controller->getDataBaseInterface()->getToolCursor(), game->getGfxEngine()));
	
	//Pido las herramientas que posee el player a toolController
	idTools = ((PGZGame*)game)->controller->getToolController()->getEquippableTools();	

	if (idTools.size()	== 0)
	{
		//Incicializamos los atributos del circulo sobre el que se dibujarán las cosas
		this->centroX = centroX;
		this->centroY = centroY;
		this->radio = radio;

		//Defino el color que usaremos para tintar las herramientas en uso
		Color colorDisabled = Color(138,138,138);

		//Creamos un GameMenuItem auxiliar par ir añadiendolos al vector, inicializo el vector y un iterador que necesitaré
		GameMenuItemS* iTool = NULL;
		iTools = new vector<GameMenuItemS*>;
		std::vector<GameMenuItemS*>::iterator it = iTools->begin();
	
		//Calculo de los angulos y con ello los puntos en los que se pintarán las cosas
		//Centro = 112, 96
		//Radio = 92
		//Ecuación en coordenadas parametricas, con funciones trigonometricas
		//x = centro.x + radio*cos(angulo)
		//y = centro.y + radio*sen(angulo)

		//Numero de herramientas que nos ha dado toolController
		int numElem = idTools.size();
		//360º
		float angulo = (float) (2*Pi);

		//El angulo de diferencia entre elemento y elemento son 360 entre el numero de elementos
		float fraccion;
		if (numElem == 0)
			fraccion = 0;
		else 
			fraccion = angulo/(numElem);

		//Creo las variables que serán el punto x y el punto y de colocación de las herramientas 
		int a = 0;
		int b = 0;

		//Angulo inicial para que el primer elemento salga arriba en el medio
		angulo = (float) (3*Pi/2);

		//Ahora toca añadir las herramientas que hemos pedido antes a ToolController una por una
		for (int i = 0; i < numElem;i++)
		{
			//Calculamos la posicion de la nueva herramienta
			a = (int) (centroX + radio*cos(angulo));
			b = (int) (centroY + radio*sin(angulo));

			iTool = new GameMenuItemS(a, b, game, gstate);
			//Metemos el grafico que me diga ToolController
			iTool->graphic = ((PGZGame*)game)->controller->getToolController()->getToolGraphic(idTools.at(i));
			//Colocamos el cursor
			iTool->setCursorLocation(NONE);
			//Si la herramienta está equipada por algun player la tintamos oscura para que se sepa que no se puede equipar
			if (((PGZGame*)game)->controller->getToolController()->findEquippedTool(idTools.at(i % numElem)) != -1)
				iTool->graphic->setColor(colorDisabled);
			//La añadimos
			iTools->insert(it,iTool);
			it = iTools->end();

			angulo = angulo + fraccion;
		}
		//Y ahora añado el texto que irá debajo

		iText = new GameMenuTextItem(((PGZGame*)game)->controller->getToolController()->getToolName(idTools.at(0)), menuFont, 
										0, 170, game, gstate);
		iText->x = game->getGfxEngine()->getGameScreenWidth()/2 - (((FriendlyTileMap*) (iText->graphic))->getWidth() / 2);


		iTool = NULL;
	}
	else
	{
	iTools = NULL;

	iText = new GameMenuTextItem( "No Weapon Aviable", menuFont, 0, 170, game, gstate);
	iText->x = game->getGfxEngine()->getGameScreenWidth()/2 - (((FriendlyTileMap*) (iText->graphic))->getWidth() / 2);
	}
}

ToolMenu::~ToolMenu()
{
	if (menuFont)
		delete menuFont,menuFont = NULL;

	//No hay que borrar el contenido de el vector porque lo borra el padre
	if (iTools)
		delete iTools, iTools = NULL;
}

void ToolMenu::launch()
{
	//Añadimos todos los elementos al menu
	if (iTools)
		for (unsigned int i = 0; i < iTools->size(); i++)
			addMenuItem(iTools->at(i));

	//Añadimos el texto del nombre del arma
	addMenuItem(iText);

	//Lanzamos el menu
	GameMenuController::launch();
}

void ToolMenu::onStep()
{
	GameMenuController::onStep();
}

void ToolMenu::onChosen(iSelectable* selectable)
{
	GameMenuItemS* elem = ((GameMenuItemS*)selectable);
	unsigned int i = 0;
	
	//Si el elemento existe lo busco, y si lo encuentro y no está equipado lo equipo donde me digan
	if (selectable)
	{
		while ((i < iTools->size()) && (elem != iTools->at(i)))
			i++;
		if (((PGZGame*)game)->controller->getToolController()->findEquippedTool(idTools.at(i)) == -1)
			((PGZGame*)game)->controller->getToolController()->equip(idTools.at(i), ((PGZGame*)game)->controller->getPlayer(0), 0);
		quit();
		((GamePlayState*) world)->unpauseGameEntities();
	}
}

void ToolMenu::onCancelled(iSelectable* selectable)
{
	GameMenuItemS* elem = ((GameMenuItemS*)selectable);
	unsigned int i = 0;

	//Si el elemento existe lo busco, y si lo encuentro y no está equipado lo equipo donde me digan
	if (selectable)
	{
		while ((i < iTools->size()) && (elem != iTools->at(i)))
			i++;
		if (((PGZGame*)game)->controller->getToolController()->findEquippedTool(idTools.at(i)) == -1)
			((PGZGame*)game)->controller->getToolController()->equip(idTools.at(i), ((PGZGame*)game)->controller->getPlayer(0), 1);
		quit();
		((GamePlayState*) world)->unpauseGameEntities();
	}
}

void ToolMenu::onRender()
{
	if (visible)
	{
		Entity::onRender();
		cursorImage->render(cursorPosX + ((GamePlayState*) world)->getOffset().first, cursorPosY + ((GamePlayState*) world)->getOffset().second);
	}
}

iSelectable* ToolMenu::getMandatorySelectable(iSelectable* slc, Direction dir)
{
	if (iTools != NULL)
	{
	
		GameMenuItemS* elem = ((GameMenuItemS*)slc);
		int selectedToolPos;

		//Busco que elemento es el que me han dicho que es desde el que se está moviento el cursor
		for (unsigned int i = 0; i < iTools->size(); i++)
		{
			if(elem == iTools->at(i))
				selectedToolPos = i + iTools->size();
		}
		//Si está a la derecha del centro del circulo
		if (elem->x >= centroX - 1)
		{
			//Si está encima del centro del circulo
			if (elem->y <= centroY - 1)
			{
				if (dir == RIGHT || dir == DOWN || dir == DOWNRIGHT)
					elem = iTools->at((selectedToolPos + 1) % (idTools.size()));
				else if (dir == LEFT ||dir == UP||dir == UPLEFT)
					elem = iTools->at((selectedToolPos - 1) % (idTools.size()));
				else if (dir==DOWNLEFT || dir == UPRIGHT)
					elem = iTools->at((selectedToolPos) % (idTools.size()));
			}
			//Si está debajo del centro del circulo
			else
			{
				if (dir == LEFT || dir == DOWN || dir==DOWNLEFT)
					elem = iTools->at((selectedToolPos + 1) % (idTools.size()));
				else if (dir == RIGHT || dir == UP || dir == UPRIGHT)
					elem = iTools->at((selectedToolPos - 1) % (idTools.size()));
				else if (dir == DOWNRIGHT ||dir == UPLEFT)
					elem = iTools->at((selectedToolPos) % (idTools.size()));
			}
		}
		//Si está a la izquierda del centro del circulo
		else 
		{
			//Si está encima del centro del circulo
			if (elem->y <= centroY - 1)
			{
				if (dir == RIGHT || dir == UP || dir == UPRIGHT)
					elem = iTools->at((selectedToolPos + 1) % (idTools.size()));
				else if (dir == LEFT || dir==DOWN || dir==DOWNLEFT)
					elem = iTools->at((selectedToolPos - 1) % (idTools.size()));
				else if (dir == UPLEFT || dir==DOWNRIGHT)
					elem = iTools->at((selectedToolPos) % (idTools.size()));
			}
			//Si está debajo del centro del circulo
			else
			{
				if (dir == LEFT || dir==UP || dir==UPLEFT)
					elem = iTools->at((selectedToolPos + 1) % (idTools.size()));
				else if (dir == RIGHT || dir==DOWN || dir==DOWNRIGHT)
					elem = iTools->at((selectedToolPos - 1) % (idTools.size()));
				else if (dir == UPRIGHT || dir==DOWNLEFT)
					elem = iTools->at((selectedToolPos) % (idTools.size()));
			}
		}
		//Miro a que herramienta me voy a mover
		unsigned int j = 0;
		while ((j < iTools->size()) && (elem != iTools->at(j)))
			j++;

		//Borro el anterior 
		removeMenuItem(iText);

		//Escribo el texto de la misma
		iText = new GameMenuTextItem(((PGZGame*)game)->controller->getToolController()->getToolName(idTools.at(j)),menuFont, 
									0, 170, game, world);
		iText->x = (game->getGfxEngine()->getGameScreenWidth()/2) - (((FriendlyTileMap*) (iText->graphic))->getWidth() / 2);

		//Lo añado de nuevo
		addMenuItem(iText);

		//Devuelvo el elemento al que me tengo que mover
		return elem;
	}
	else 
		return NULL;
}

iSelectable* ToolMenu::getAlternativeSelectable(iSelectable* slc, Direction dir)
{
	return NULL;
}