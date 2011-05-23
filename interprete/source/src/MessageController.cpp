#include "MessageController.h"

MessageController::MessageController(Controller* c){
	this->controller = c;
	flag = false;
	this->init("data/textos.txt", c->getDataBaseInterface()->getFont(), c->getDataBaseInterface()->getSystem());
	npc = NULL;
	currentType = NONE;
}

MessageController::~MessageController()
{
	delete font; font = NULL;
	delete background; background = NULL;
	delete texts;
}

void MessageController::init(string textsPath, string fontPath, string backgroundPath){
	font = new TileFont(fontPath, controller->game->getGfxEngine());
	background = new TileSet(backgroundPath, 8, 8, controller->game->getGfxEngine());
	this->getText(textsPath);
}

void MessageController::onStep(){
	/* Si ya ha acabado de mostrar el texto */ 
	if (m != NULL)
	{
		if ((flag) && (m->isFinished()))
		{
			m = NULL;
			// Desbloqueamos el mundo
			controller->gamePlayState->unpauseGameEntities();
			if (currentType == ITEM)
			{
				// Notificamos al player
				controller->getPlayer(0)->endGetItem();
			}
			// Avisamos al npc para que siga haciendo sus cosas
			else if (currentType == DIALOG)
			{
				if (npc != NULL)
				{
					this->npc->onEndInteract();
					npc = NULL;
				}
			}
			else if (currentType == NORMALMESSAGE)
			{
				if (interact != NULL)
				{
					this->interact->onEndInteract();
					interact = NULL;
				}
			}
		}
	}
}

/* Carga los textos desde archivo */
bool MessageController::getText(string path){
	int numTextos = 0;
	texts = new vector<string>();
	// Carga el archivo y lee
	FILE* f = fopen(path.c_str(), "rb");

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

void MessageController::showMessageDialog(int idText, NPC* npc)
{
	currentType = DIALOG;
	flag = true;
	this->npc = npc;
	m = new MessageDialog(font, 26,4, background, controller->game->getGfxEngine(), 8, 152, controller->game->getGameState(), controller->game);
	controller->gamePlayState->pauseGameEntities();
	string aux = "";
	aux = texts->at(idText);
	m->setText(aux);
	controller->gamePlayState->add(m);
}

void MessageController::showItemMessage(string itemName)
{
	currentType = ITEM;
	flag = true;
	m = new MessageDialog(font, 26,4, background, controller->game->getGfxEngine(), 8, 152, controller->game->getGameState(), controller->game);
	controller->gamePlayState->pauseGameEntities();
	string aux = "You have taken " + itemName + ".";
	m->setText(aux);
	controller->gamePlayState->add(m);
}


void MessageController::showMessage(string message, iInteractable* i)
{
	this->interact = i;
	currentType = NORMALMESSAGE;
	flag = true;
	m = new MessageDialog(font, 26,4, background, controller->game->getGfxEngine(), 8, 152, controller->game->getGameState(), controller->game);
	controller->gamePlayState->pauseGameEntities();
	m->setText(message);
	controller->gamePlayState->add(m);
}