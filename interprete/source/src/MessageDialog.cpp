#include "MessageDialog.h"


MessageDialog::MessageDialog(Font* font, int col, int row, TileSet* tileSetBackground, GfxEngine* gfxEngine,int x, int y, GameState* gameState, Game* game):Entity(x, y, game, gameState)
{
	//Nos guardamos el motor grafico
	this->gfxEngine = gfxEngine;

	//Ponemos el charMap a NULL hasta que alguien llame al setText
	charMap = NULL;
	
	//Creamos el TileMap de fondo con el marco y el fondo que tendrá el texto
	marco = new TileMap(tileSetBackground->getTileW(),tileSetBackground->getTileH(),gfxEngine);
	marco->setTileSet(tileSetBackground);

	//Con el tileMap de fondo ya creado le creamos el fondo entero
	this->initBackgrount(row,col);

	//Creamos aún el tileTextLabel en el que irá el texto
	texto = new TileTextLabel(font,gfxEngine);

	//Inicializamos variables de control
	paused = false;
	restart = false;
	step = 0;
	nextFrame = 0;
	color = new Color(Color::White);
}


MessageDialog::~MessageDialog()
{
	//Si se habia creado el marco lo borro
	/*if (marco)
	{
		delete marco;
		marco = NULL;
	}*/

	//Si se habia creado el texto lo borro
	if (texto)
	{
		delete texto;
		texto = NULL;
	}
	//Si se habia creado el charMap lo borro
	if (charMap)
	{
		delete charMap;
		charMap = NULL;
	}
}



bool MessageDialog::setText(string texto)
{
	//Debe encargarse tambien de fijar a partir del tamaño que le deja el marco y de la escala el numero de filas y columnas del texto
	int cols;
	int fils;

	//Mido la distancia en pixeles de ancho y alto del marco
	fils = marco->getRows()*marco->getTileset()->getTileH();
	cols = marco->getCols()*marco->getTileset()->getTileW();

	//Le quito tanto al ancho como al alto lo que ocupa el marco en si
	fils -= marco->getTileset()->getTileH()*2;
	cols -= marco->getTileset()->getTileW()*2;

	//Ahora hago la division entera entre la distancia y el tamaño de tile del texto por su escala
	fils = fils / (this->texto->getScaleV()*this->texto->getTileH());
	cols = cols / (this->texto->getScaleH()*this->texto->getTileW());

	//Los numeros resultantes son el numero de filas y columnas que tendrá el texto interior
	this->texto->setSize(fils,cols);

	//Ahora creo el vector que usará el onStep para ir escribiendo el texto
	charMap = new vector<int>;
	std::vector<int>::iterator it = charMap->begin();
	int i = 0;
	int nChar = 0;
	while (i < texto.size())
	{
		if ((nChar % (fils * cols) == 0) && (nChar != 0) && (charMap->back() != -4))
		{
			//Insertamos un -4 que el onStep considerará una pausa que borra el texto al presionar una tecla
			charMap->insert(it,-4);
			it = charMap->end();
		}
		//Si lo siguiente es $ significa que lo siguiente es una función especial
		else if (texto[i] == '$')
		{
			i++;
			//Si el texto acaba en $ se considerá erroneo y no se pintará
			if (i == texto.size())
			{
				delete charMap;
				charMap = NULL;
				return false;
			}
			//Si lo siguiente es un digito cambiamos de color
			else if ((texto[i] > 47) && (texto[i] < 56))
			{	
				//Insertamos un -1 que el onStep considerará un cambio de color
				charMap->insert(it,-1);
				it = charMap->end();
				//Insertamos el color al que deberá cambiar
				charMap->insert(it,((int) texto[i] - 48));
				it = charMap->end();
			}
			//Si lo siguiente es una p es una pausa, aún queda ver de que tipo
			else if (texto[i] == 'p')
			{
				i++;
				//Si acaba en pausa sin indicar el si es por tiempo o por pulsación será erroneo
				if (i == texto.size())
				{
					delete charMap;
					charMap = NULL;
					return false;
				}
				//Si lo siguiente es un digito indica el numero de segundos de la misma
				else if ((texto[i] > 47) && (texto[i] < 56))
				{	
					//Insertamos un -2 que el onStep considerará una pausa por tiempo
					charMap->insert(it,-2);
					it = charMap->end();
					//Insertamos el tiempo en segundos que deberá esperar
					charMap->insert(it,((int) texto[i] - 48));
					it = charMap->end();
				}
				//Si lo siguiente es otra p se considera que la pausa dura hasta que el jugador pulse una tecla
				else if (texto[i] == 'p')
				{
					//Insertamos un -3 que el onStep considerará una pausa por pulsación
					charMap->insert(it,-3);
					it = charMap->end();
				}
			}
		}
		//Si no es un $, se considera que el caracter es normal y solo se quiere escribir el mismo
		else 
		{
			charMap->insert(it,(int) texto[i]);
			it = charMap->end();
			nChar++;
		}
		i++;
	}
	return true;
}



void MessageDialog::onStep()
{
	if ((charMap != NULL) && (nextFrame < charMap->size()) && (!paused) && (step == 0))
	{
		int nextChar = charMap->at(nextFrame);
		while ((nextChar < 0) && (nextFrame < charMap->size()))
		{
			switch (nextChar)
			{
				//Si es un -1 significa cambio de color
				case -1: 
				{
					nextFrame ++;
					//Si es 0 blanco si no lo pongo a un color cualquiera, ya se verá
					if (charMap->at(nextFrame) == 0)
						color = new Color(Color::White);
					else
					//Evidentemente esto es temporal
						color = new Color(Color::Cyan);
					break;
				}
				//Si es -2 significa pausa por tiempo por lo que deberemos poner un timer con el tiempo indicado
				case -2:
				{
					nextFrame++;
					paused = true;
					this->setTimer(1, charMap->at(nextFrame)*30);
					break;
				}
				//-3 significa pausa por pulsación, que por ahora será una pausa por tiempo de un par de segundos
				case -3:
				{
					paused = true;
					this->setTimer(1, 2*30);
					break;
				}
				//-4 significa que deberá esperar hasta que se pulse una tecla y cuando se haga borrar el texto y empezar desde el principio
				case -4:
				{
					//Por ahora lo único que hará será borrar el texto y esperar un segundo
					this->texto->setText("");
					paused = true;
					this->setTimer(1, 30);
				}

			}
			//Paso al siguiente caracter y veo si vuelve a ser alguna funcion especial o toca escribir
			nextFrame++;
			//Leo el siguiente caracter solo si lo hay
			if (nextFrame < charMap->size())
				nextChar = charMap->at(nextFrame);
		}
		//Si me he pasado es posible que charMap tenga un valor erroneo, compruebo por si acaso
		if ((nextFrame < charMap->size()) && (!paused))
		{
			this->texto->addCharacter(nextChar,*(this->color));
			nextFrame++;
		}
		step++;
	}
	else if(step !=0)
	{
		step++;
		if (step == 5)
			step =0;
	}
}


//Cuando el timer acabe es que ha acabado la pausa y se debe seguir escribiendo
void MessageDialog::onTimer(int n)
{
	if (n == 1)
		paused = false;
}


//Contruye totalmente el fondo sobre el que se pintará el texto
void MessageDialog::initBackgrount(int row, int col){

	//Me creo el mapa de tiles que le voy a pasar al tileMap
	int** mapa = (int **) malloc(col *sizeof(int));
	for(int i = 0; i < col; i++)
		mapa[i] = (int *) malloc(row * sizeof(int));

	//Voy rellenando el mapa
	for (int j = 0; j < row ; j++)
		for (int i = 0; i < col; i++)
		{
			//Si estamos en la primera fila
			if (j == 0)
			{
				//Si estamos en la esquina superior izquierda
				if (i == 0)
					mapa[i][j] = 0;
				//Si estamos en la esquina superior derecha
				else if (i == col - 1)
					mapa[i][j] = 2;
				//Si estamos en el borde superior
				else 
					mapa[i][j] = 1;
			}
			else if (j == row - 1)
			{
				//Si estamos en la esquina inferior izquierda
				if (i == 0)
					mapa[i][j] = 6;
				//Si estamos en la esquina inferior derecha
				else if (i == col - 1)
					mapa[i][j] = 8;
				//Si estamos en el borde inferior
				else 
					mapa[i][j] = 7;
			}
			else
			{
				//Si estamos en el borde izquierdo
				if (i == 0)
					mapa[i][j] = 3;
				//Si estamos en el borde derecho
				else if (i == col - 1)
					mapa[i][j] = 5;
				//Si estamos en el sitio sobre el que se situará el texto
				else 
					mapa[i][j] = 4;
			}
		}
	//Le paso al tileMap su nuevo mapa de tiles, y sus filas y columnas
	marco->setMap(mapa, col, row);

	//Le digo que cree su nueva imagen
	marco->getMapImage();

	//Le digo que el grafico de esta entidad es el susodicho marco para que lo pinte siempre que esta esté en pantalla
	graphic = marco;

	//Reinicializamos variables de control
	paused = false;
	restart = false;
	nextFrame = 0;
	step = 0;
	color = new Color(Color::White);

	//Si habia un texto guardado en charMap lo borro
	if (charMap)
	{
		delete charMap;
		charMap = NULL;
	}
}

//Pinto el fondo y el texto por encima, contando con el espacio del marco
void MessageDialog::onRender()
{
	if (charMap)
	{
		Entity::onRender();
		texto->render( x + marco->getWidth(), y + marco->getHeight());
	}
}


//Cambiamos el tileSet de background
void MessageDialog::setBackgroundTileSet(TileSet* background)
{
	marco->setTileSet(background);
}

//Cambiamos la fuente del texto, esto implica necesariamente que si habia texto se destruye
void MessageDialog::setFont(Font* font)
{
	//Creo un tileTextLbel con la nueva fuente
	texto = new TileTextLabel(font,gfxEngine);

	//Reseteo todos los parametros
	paused = false;
	restart = false;
	nextFrame = 0;
	step = 0;
	color = new Color(Color::White);

	//Si habia un texto guardado en charMap lo borro
	if (charMap)
	{
		delete charMap;
		charMap = NULL;
	}
}

//Cambio la escala del texto
void MessageDialog::setScale(int scale)
{
	texto->setScale(scale);

	//Reseteo todos los parametros
	paused = false;
	restart = false;
	nextFrame = 0;
	step = 0;
	color = new Color(Color::White);

	//Si habia un texto guardado en charMap lo borro
	if (charMap)
	{
		delete charMap;
		charMap = NULL;
	}
}