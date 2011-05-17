#include "LoadMenu.h"

LoadMenu::LoadMenu(int x, int y, Game* game, GameState* gstate, DataBaseInterface* dbi) : GameMenuController(x, y, game, gstate) {
	numSaves = ((PGZGame*)game)->getNumSaves();
	setGraphic(new Stamp(dbi->getMainMenu(), game->getGfxEngine()));
	setCursorImage(new Stamp(dbi->getCursor(), game->getGfxEngine()));

	Color colorEnabled = Color(38,38,38);

	menuFont = new TileFont(dbi->getFont(), game->getGfxEngine());

	loadBlocks = new vector<LoadBlock*>();

	/*FILE * f = NULL; LoadBlock* block;
	for (int i = 0; i < numSaves; i++){
		f = fopen("data/save" + i, "r");
		if (f != NULL){
			/*crear bloque de carga*/
	/*		block = new LoadBlock(i + 1, ((PGZGame*)game)->controller,f, menuFont, 30, 75*i, game, gstate);
			loadBlocks->push_back(block);
			block->setCursorLocation(LEFT);
		}
	}
	cancel = new GameMenuTextItemS("Cancel ", menuFont, 85, 400, game, gstate);
	cancel->setCursorLocation(LEFT);
	cancel->getText()->setColor(colorEnabled);*/
}

LoadMenu::~LoadMenu() {
	delete menuFont;
}

void LoadMenu::launch() {
	/*for (int i = 0; i < loadBlocks->size(); i++){
		addMenuItem(loadBlocks->at(i));
	}
	addMenuItem(cancel);
	GameMenuController::launch();*/
}

void LoadMenu::onStep() {
	GameMenuController::onStep();
}

void LoadMenu::onChosen(iSelectable* selectable) {
	int i = 0;
	bool selected = false;

	if (selectable == cancel){
		// Volver al mainMenu
	}

	while (!selected && i < numSaves){
		//selected = selectable == loadBlocks->at(i);
		i++;
	}
	// Si se ha seleccionado algún bloque...
	if (i < numSaves){
		//((PGZGame*)game)->loadGame(loadBlocks->at(i-1)->getID());
	}

}