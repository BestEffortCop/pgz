#include "ToolMenu.h"


ToolMenu::ToolMenu(int x, int y, Game* game, GameState* gstate) : GameMenuController(x, y, game, gstate)
{
	((GamePlayState*) world)->pauseGameEntities();
	
	setGraphic(new Stamp("data/graphics/menuBackground.png", game->getGfxEngine()));
	graphic->setAlpha(0.8);
	setCursorImage(new Stamp("data/graphics/cursor.png", game->getGfxEngine()));

	Color colorEnabled = Color(38,38,38);
	Color colorDisabled = Color(138,138,138);

	menuFont = new TileFont("data/graphics/sprFont_strip94.png", game->getGfxEngine());

	GameMenuTextItemS* iTool = NULL;
	iTools = new vector<GameMenuTextItemS*>;
	std::vector<GameMenuTextItemS*>::iterator it = iTools->begin();

	//Aqui habria que pedir las herramientas a Tool controler para saber cuales son,
	//Y pintar solo las que estubieran disponibles, por ahora mierdas



	//Calculo de los angulos y con ello los puntos en los que se pintarán las cosas
	//Centro = 112, 96
	//Radio = 92
	//Ecuación en coordenadas parametricas, con funciones trigonometricas
	//x = centro.x + radio*cos(angulo)
	//y = centro.y + radio*sen(angulo)

	float pi = 3.1415;		//Solo para el ejemplo, luego ponerlo como constante o algo

	int numElem = 4;		//Por ejemplo
	float angulo = 2*pi;	//360º

	float fraccion = angulo/numElem;

	angulo = 3*pi/2;
	int a = 112 + 92*cos(angulo);
	int b = 96 + 92*sin(angulo);

	//Ahora toca añadir las herramientas que hemos pedido antes a ToolController una por una

	iTool = new GameMenuTextItemS("Espada", menuFont, a, b, game, gstate);
	iTool->setCursorLocation(LEFT);
	iTool->getText()->setColor(colorDisabled);
	iTools->insert(it,iTool);
	it = iTools->end();

	angulo = angulo + fraccion;
	a = 112 + 92*cos(angulo);
	b = 96 + 92*sin(angulo);

	iTool = new GameMenuTextItemS("Arco", menuFont, a, b, game, gstate);
	iTool->setCursorLocation(LEFT);
	iTool->getText()->setColor(colorDisabled);
	iTools->insert(it,iTool);
	it = iTools->end();

	angulo = angulo + fraccion;
	a = 112 + 92*cos(angulo);
	b = 96 + 92*sin(angulo);

	iTool = new GameMenuTextItemS("Boomerang", menuFont, a, b, game, gstate);
	iTool->setCursorLocation(LEFT);
	iTool->getText()->setColor(colorDisabled);
	iTools->insert(it,iTool);
	it = iTools->end();

	angulo = angulo + fraccion;
	a = 112 + 92*cos(angulo);
	b = 96 + 92*sin(angulo);

	iTool = new GameMenuTextItemS("Salir", menuFont, a, b, game, gstate);
	iTool->setCursorLocation(LEFT);
	iTool->getText()->setColor(colorDisabled);
	iTools->insert(it,iTool);
	it = iTools->end();

	iTool = NULL;

}

ToolMenu::~ToolMenu()
{
	delete menuFont;
}

void ToolMenu::launch()
{
	addMenuItem(iTools->at(0));
	addMenuItem(iTools->at(1));
	addMenuItem(iTools->at(2));
	addMenuItem(iTools->at(3));
	GameMenuController::launch();
}

void ToolMenu::onStep()
{
	GameMenuController::onStep();
}

void ToolMenu::onChosen(iSelectable* selectable)
{
	if (selectable == iTools->at(3))
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