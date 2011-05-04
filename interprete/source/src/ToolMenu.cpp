#include "ToolMenu.h"


ToolMenu::ToolMenu(int x, int y, Game* game, GameState* gstate) : GameMenuController(x, y, game, gstate)
{
	((GamePlayState*) world)->pauseGameEntities();
	
	setGraphic(new Stamp("data/graphics/menuBackground.png", game->getGfxEngine()));
	graphic->setAlpha(0.7);
	setCursorImage(new Stamp("data/graphics/cursor.png", game->getGfxEngine()));

	Color colorDisabled = Color(138,138,138);

	menuFont = new TileFont("data/graphics/sprFont_strip94.png", game->getGfxEngine());

	GameMenuItemS* iTool = NULL;
	iTools = new vector<GameMenuItemS*>;
	std::vector<GameMenuItemS*>::iterator it = iTools->begin();


	//Aqui habria que pedir las herramientas a Tool controler para saber cuales son,
	//Y pintar solo las que estubieran disponibles, por ahora mierdas

	idTools = ((PGZGame*)game)->controller->getToolController()->getEquippableTools();	

	//Calculo de los angulos y con ello los puntos en los que se pintarán las cosas
	//Centro = 112, 96
	//Radio = 92
	//Ecuación en coordenadas parametricas, con funciones trigonometricas
	//x = centro.x + radio*cos(angulo)
	//y = centro.y + radio*sen(angulo)


	//Numero de herramientas que nos ha dado toolController
	int numElem = idTools.size();
	//360º
	float angulo = 2*Pi;	
	//El angulo de diferencia entre elemento y elemento son 360 entre el numero de elementos
	float fraccion = angulo/numElem;

	//Creo las variables que serán el punto x y el punto y de colocación de las herramientas 
	int a = 0;
	int b = 0;

	//Angulo inicial para que el primer elemento salga arriba en el medio
	angulo = 3*Pi/2;

	//Ahora toca añadir las herramientas que hemos pedido antes a ToolController una por una

	for (int i = 0; i < numElem;i++)
	{
		a = CentroX + Radio*cos(angulo);
		b = CentroY + Radio*sin(angulo);

		iTool = new GameMenuItemS(a, b, game, gstate);
		//Aqui meterle el grafico que me diga ToolController
		iTool->graphic = ((PGZGame*)game)->controller->getToolController()->getToolGraphic(idTools.at(i));
		iTool->setCursorLocation(LEFT);
		//iTool->graphic->setColor(colorEnabled);
		if (((PGZGame*)game)->controller->getToolController()->findEquippedTool(idTools.at(i)) != -1)
			iTool->graphic->setColor(colorDisabled);
		iTools->insert(it,iTool);
		it = iTools->end();

		angulo = angulo + fraccion;
	}

	iTool = NULL;
}

ToolMenu::~ToolMenu()
{
	if (menuFont)
		delete menuFont, menuFont=NULL;
	if (iTools)
		delete iTools, iTools = NULL;
}

void ToolMenu::launch()
{
	for (int i = 0; i < iTools->size(); i++)
		addMenuItem(iTools->at(i));

	GameMenuController::launch();
}

void ToolMenu::onStep()
{
	GameMenuController::onStep();
}

void ToolMenu::onChosen(iSelectable* selectable)
{
	GameMenuItemS* elem = ((GameMenuItemS*)selectable);
	int i = 0;

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
	int i = 0;

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
	GameMenuItemS* elem = ((GameMenuItemS*)slc);
	int selectedToolPos;

	for (int i = 0; i < iTools->size(); i++)
	{
		if(elem == iTools->at(i))
			selectedToolPos = i + iTools->size();
	}
	
	if (elem->x >= CentroX - 1)
	{
		if (elem->y <= CentroY - 1)
		{
			if (dir==RIGHT)
				return iTools->at((selectedToolPos + 1) % (idTools.size()));
			if (dir==LEFT)
				return iTools->at((selectedToolPos - 1) % (idTools.size()));
			if (dir==DOWN)
				return iTools->at((selectedToolPos + 1) % (idTools.size()));
			if (dir==UP)
				return iTools->at((selectedToolPos - 1) % (idTools.size()));
		}
		else
		{
			if (dir==LEFT)
				return iTools->at((selectedToolPos + 1) % (idTools.size()));
			if (dir==RIGHT)
				return iTools->at((selectedToolPos - 1) % (idTools.size()));
			if (dir==DOWN)
				return iTools->at((selectedToolPos + 1) % (idTools.size()));
			if (dir==UP)
				return iTools->at((selectedToolPos - 1) % (idTools.size()));
		}
	}
	else 
	{
		if (elem->y <= CentroY - 1)
		{
			if (dir==RIGHT)
				return iTools->at((selectedToolPos + 1) % (idTools.size()));
			if (dir==LEFT)
				return iTools->at((selectedToolPos - 1) % (idTools.size()));
			if (dir==UP)
				return iTools->at((selectedToolPos + 1) % (idTools.size()));
			if (dir==DOWN)
				return iTools->at((selectedToolPos - 1) % (idTools.size()));
		}
		else
		{
			if (dir==LEFT)
				return iTools->at((selectedToolPos + 1) % (idTools.size()));
			if (dir==RIGHT)
				return iTools->at((selectedToolPos - 1) % (idTools.size()));
			if (dir==UP)
				return iTools->at((selectedToolPos + 1) % (idTools.size()));
			if (dir==DOWN)
				return iTools->at((selectedToolPos - 1) % (idTools.size()));
		}
	}
	return NULL;
}

iSelectable* ToolMenu::getAlternativeSelectable(iSelectable* slc, Direction dir)
{
	return NULL;
}