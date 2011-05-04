#include "ToolMenu.h"


ToolMenu::ToolMenu(int x, int y, Game* game, GameState* gstate) : GameMenuController(x, y, game, gstate)
{
	((GamePlayState*) world)->pauseGameEntities();
	
	setGraphic(new Stamp("data/graphics/menuBackground.png", game->getGfxEngine()));
	graphic->setAlpha(0.8);
	setCursorImage(new Stamp("data/graphics/cursor.png", game->getGfxEngine()));

	Color colorDisabled = Color(38,38,38);
	Color colorEnabled = Color(138,138,138);

	menuFont = new TileFont("data/graphics/sprFont_strip94.png", game->getGfxEngine());

	GameMenuTextItemS* iTool = NULL;
	iTools = new vector<GameMenuTextItemS*>;
	std::vector<GameMenuTextItemS*>::iterator it = iTools->begin();

	//Aqui habria que pedir las herramientas a Tool controler para saber cuales son,
	//Y pintar solo las que estubieran disponibles, por ahora mierdas

	vector<int> equippabletools = ((PGZGame*)game)->controller->getToolController()->getEquippableTools();		


	//Calculo de los angulos y con ello los puntos en los que se pintarán las cosas
	//Centro = 112, 96
	//Radio = 92
	//Ecuación en coordenadas parametricas, con funciones trigonometricas
	//x = centro.x + radio*cos(angulo)
	//y = centro.y + radio*sen(angulo)

	float pi = 3.1415;		//Solo para el ejemplo, luego ponerlo como constante o algo

	//Numero de herramientas que nos ha dado toolController
	int numElem = equippabletools.size();
	//360º
	float angulo = 2*pi;	
	//El angulo de diferencia entre elemento y elemento son 360 entre el numero de elementos
	float fraccion = angulo/numElem;

	//Creo las variables que serán el punto x y el punto y de colocación de las herramientas 
	int a = 0;
	int b = 0;

	//Angulo inicial para que el primer elemento salga arriba en el medio
	angulo = 3*pi/2;

	//Ahora toca añadir las herramientas que hemos pedido antes a ToolController una por una

	for (int i = 0; i < numElem;i++)
	{
		int a = 112 + 92*cos(angulo);
		int b = 96 + 92*sin(angulo);

		iTool = new GameMenuTextItemS("Mierda", menuFont, a, b, game, gstate);
		iTool->setCursorLocation(LEFT);
		iTool->getText()->setColor(colorEnabled);
		if (((PGZGame*)game)->controller->getToolController()->findEquippedTool(equippabletools.at(i)) != -1)
			iTool->getText()->setColor(colorDisabled);
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
	if (selectable)
	{
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
	return NULL;
}

iSelectable* ToolMenu::getAlternativeSelectable(iSelectable* slc, Direction dir)
{
	return NULL;
}