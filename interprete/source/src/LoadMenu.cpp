#include "LoadMenu.h"

LoadMenu::LoadMenu(int x, int y, Game* game, GameState* gstate, DataBaseInterface* dbi) : GameMenuController(x, y, game, gstate) {
	numSaves = ((PGZGame*)game)->controller->getMaxSaves();
	setGraphic(new Stamp("data/graphics/load_menu.png" /*dbi->getLoadMenu()*/, game->getGfxEngine()));
	setCursorImage(new Stamp(dbi->getCursor(), game->getGfxEngine()));

	Color colorEnabled = Color(38,38,38);

	menuFont = new TileFont(dbi->getFont(), game->getGfxEngine());

	loadBlocks = new vector<LoadBlock*>();
	char buffer[33];
	char str[80];

	FILE * f = NULL; LoadBlock* block;
	for (int i = 0; i < numSaves; i++){
		strcpy(str,"data/save");
		strcat(str,itoa(i,buffer,10));
		f = fopen(str, "r");
		if (f != NULL){
			/*crear bloque de carga*/
			block = new LoadBlock(i, f, menuFont, 30, 45*i, game, gstate);
			loadBlocks->push_back(block);
			block->setCursorLocation(LEFT);
		}
	}
	cancel = new GameMenuTextItemS("Cancel ", menuFont, 85, 200, game, gstate);
	cancel->setCursorLocation(LEFT);
	cancel->getText()->setColor(colorEnabled);
}

LoadMenu::~LoadMenu() {
	delete menuFont;
}

void LoadMenu::launch() {
	for (int i = 0; i < loadBlocks->size(); i++){
		addMenuItem(loadBlocks->at(i));
	}
	addMenuItem(cancel);
	GameMenuController::launch();
}

void LoadMenu::onStep() {
	GameMenuController::onStep();
}

void LoadMenu::onChosen(iSelectable* selectable) {
	int i = 0;
	bool selected = false;

	if (selectable == cancel){
		// Volver al mainMenu
		((PGZGame*)game)->resetGame();
	}

	while (!selected && i < numSaves){
		selected = selectable == loadBlocks->at(i);
		i++;
	}
	// Si se ha seleccionado algún bloque...
	if (selected){
		i--;
		((PGZGame*)game)->loadGame(loadBlocks->at(i)->getID());
	}

}