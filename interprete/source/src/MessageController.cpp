#include "MessageController.h"

MessageController::MessageController(Controller* c){
	this->controller = c;
	flag = false;
	this->init("data/textos.txt", "data/graphics/sprFont_strip94.png", "data/graphics/system.png");
}

MessageController::~MessageController(){
	delete font; font = NULL;
}

void MessageController::init(string textsPath, string fontPath, string backgroundPath){
	font = new TileFont(fontPath, controller->game->getGfxEngine());
	background = new TileSet(backgroundPath, 8, 8, controller->game->getGfxEngine());
	this->getText(textsPath);
}

void MessageController::onStep(){
	/* Si ya ha acabado de mostrar el texto */ 
	if ((flag) && (m->isFinished())){
		// Desbloqueamos el mundo
		controller->gamePlayState->unpauseGameEntities();
		// Avisamos al npc para que siga haciendo sus cosas
		this->npc->onEndInteract();
	}
}

/* Carga los textos desde archivo */
bool MessageController::getText(string path){
	int numTextos = 0;
	texts = new vector<string>();
	// Carga el archivo y lee
	FILE* f = fopen(path.c_str(), "r");

	// Si el archivo es inválido, no se puede hacer nada
	if (f == NULL)
		return false;

	// 1. Número de textos
	fscanf(f, "%d", &numTextos);

	if (numTextos == 0)
		return false;
	
	int words = 0; string text = ""; char aux[80];
	for (int i = 0; i < numTextos; i++){
		text = "";
		fscanf(f, "%d", &words);
		for (int j = 0; j < words; j++){
			fscanf(f, "%s", aux);
			if (j == words - 1)
				text += aux; 	
			else{
				strcat(aux, " ");
				text += aux;
			}
		}
		texts->push_back(text);
	}

	fclose(f);

	return true;
}

void MessageController::showMessageDialog(int idText, NPC* npc){
	flag = true;
	this->npc = npc;
	m = new MessageDialog(font, 26,4, background, controller->game->getGfxEngine(), 8, 152, controller->game->getGameState(), controller->game);
	controller->gamePlayState->pauseGameEntities();
	string aux = "";
	aux = texts->at(idText);
	m->setText(aux);
	controller->gamePlayState->add(m);
}