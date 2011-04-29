#include "MessageDialog.h"


MessageDialog::MessageDialog(Font* font, int col, int row, TileSet* tileSetBackground, GfxEngine* gfxEngine,int x, int y, GameState* gameState, Game* game):Entity(x, y, game, gameState)
{
	//Nos guardamos el motor grafico
	this->gfxEngine = gfxEngine;

	//Ponemos el charMap a NULL hasta que alguien llame al setText
	charMap = NULL;
	
	//Inicializamos variables de control
	paused = false;
	restart = false;
	waiting = false;
	step = 0;
	nextFrame = 0;
	color = (Color::White);

	speed = 1;

	//Creamos el TileMap de fondo con el marco y el fondo que tendrá el texto
	marco = new FriendlyTileMap(tileSetBackground->getTileW(),tileSetBackground->getTileH(),gfxEngine);
	marco->setTileSet(tileSetBackground);
	tiledContinue = new FriendlyTileMap(tileSetBackground->getTileW(), tileSetBackground->getTileH(),gfxEngine);
	tiledContinue->setTileSet(tileSetBackground);

	//Con el tileMap de fondo ya creado le creamos el fondo entero
	this->initBackgrount(row,col);

	//Creamos aún el tileTextLabel en el que irá el texto
	texto = new TileTextLabel(font,gfxEngine);
}


MessageDialog::~MessageDialog()
{
	//Si se habia creado el marco lo borro
	if (marco)
	{
		//No lo borro porque el marco es el graphic de esta entidad, y el grafico lo borra la entidad
		//delete marco;
		marco = NULL;
	}
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

	if (tiledContinue)
		delete tiledContinue, tiledContinue = NULL;
}



bool MessageDialog::setText(string texto)
{
	//----------------------------------------------------------------------------------------------
	//Debe encargarse de fijar a partir del tamaño que le deja el marco y de la escala el numero de filas y columnas del texto
	
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

	//----------------------------------------------------------------------------------------------------
	//Hacemos una primera pasada leyendo y guardandonos en un vector de strings todas las palabras 
	//separadas por espacios, importante, nada de escribir mal. Para luego poder comprobar si cabe en la linea
	vector<string>* stringVector = new vector<string>;
	std::vector<string>::iterator iter = stringVector->begin();
	string aux;
	int j = 0;

	while  (j < texto.size())
	{
		//Debemos no considerar ningún caracter especial en el array de palabras
		if (texto[j] == '$')
		{
			j++;
			//Si el texto acaba en $ se considerá erroneo y no se pintará
			if (j == texto.size())
			{
				delete charMap;
				charMap = NULL;
				return false;
			}
			//Si lo siguiente es un digito es lo ultimo que debemos saltarnos debido a este $

			//Si lo siguiente es una p es una pausa, aún queda saltarse otro caracter
			else if (texto[j] == 'p')
			{
				j++;
				//Si acaba en pausa sin indicar el si es por tiempo o por pulsación será erroneo
				if (j == texto.size())
				{
					delete charMap;
					charMap = NULL;
					return false;
				}
				//Si lo siguiente es un digito o otra p, sera lo ultimo que debamos saltarnos
			}
		}
		//Si no es un $, se considera que el caracter es normal y debemos incluirlo
		else 
		{	
			//Si leo un espacio lo conidero un separador y en ese caso me guardo la palabra anterior tal y 
			//como estubiera y reinicio el string auxiliar
			if (texto[j] == ' ' || texto[j] == '\n')
			{
				stringVector->insert(iter,aux);
				iter = stringVector->end();
				aux.clear();
			}
			//Si no hay ni caracter especial ni espacio concateno el caracter a lo que llevo de palabra
			else
			{
				aux = aux.append(&texto[j],1);
			}
		}
		j++;
	}
	//Cuando salgo aun me falta por guardarme la palabra que está guardada en el string auxiliar, asique la guardo
	stringVector->insert(iter,aux);
	iter = stringVector->end();
	aux.clear();


	//----------------------------------------------------------------------------------------------------
	//Ahora creo el vector que usará el onStep para ir escribiendo el texto
	charMap = new vector<int>;
	std::vector<int>::iterator it = charMap->begin();
	//Lleva la cuenta de los int leidos
	int i = 0;
	//Lleva la cuenta de los caracteres escritos
	int nChar = 0;
	//Lleva la cuenta de las palabras escritas
	int nWords = 0;

	while (i < texto.size())
	{
		if ((nChar % (fils * cols) == 0) && (nChar != 0) && (charMap->back() != -4))
		{
			//Insertamos un -4 que el onStep considerará una pausa que borra el texto al presionar una tecla
			charMap->insert(it,-4);
			it = charMap->end();
			i--;
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
			//Si lo que acabo de escribir es un espacio compruebo si la siguiente palabra cabe en esta linea
			//si no cabe escribo espacios hasta llegar al final de la linea
			if (texto[i] == ' ')
			{
				//Añado uno a las palabras que llevo escritas
				nWords++;
				if (((nChar % cols) + stringVector->at(nWords).size()) >= cols)
				{
					while ((nChar % cols) != 0)
					{
						charMap->insert(it,(int) ' ');
						it = charMap->end();
						nChar++;
					}
				}
			}
			//Si toca escribir un espacio al comienzo de linea no lo escribo, que queda feo
			if ((texto[i] != ' ') || (nChar % cols != 0))
			{
				charMap->insert(it,(int) texto[i]);
				it = charMap->end();
				nChar++;
			}
		}
		i++;
	}
	//Al acabar borramos el vector auxiliar de strings
	if (stringVector)
		delete stringVector, stringVector= NULL;

	return true;
}



void MessageDialog::onStep()
{
	int sp;
	if (game->getInput()->key(Input::kC))
		sp = speed*5;
	else 
		sp = speed;

	if ((charMap != NULL) && (nextFrame < charMap->size()) && (!paused) && (step == 0))
	{
		int nextChar = charMap->at(nextFrame);
		while ((nextChar < 0) && (nextChar > -5) && (nextFrame < charMap->size()))
		{
			switch (nextChar)
			{
				//Si es un -1 significa cambio de color
				case -1: 
				{
					nextFrame ++;
					switch (charMap->at(nextFrame))
					{
						//Si es 0 blanco si no lo pongo a un color cualquiera, ya se verá
						case 0:	{color = Color::White;break;}
						case 1:	{color = Color::Black;break;}
						case 2:	{color = Color::Blue;break;}
						case 3:	{color = Color::Cyan;break;}
						case 4:	{color = Color::Green;break;}
						case 5:	{color = Color::Magenta;break;}
						case 6:	{color = Color::Red;break;}
						case 7:	{color = Color::Yellow;break;}
						/*Posiblidad de meter 2 colores mas, si alguien quiere uno que lo ponga
						case 8:	{color = new Color(Color::White);break;}
						case 9:	{color = new Color(Color::Cyan);break;}
						*/
					}
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
					restart = false;
					waiting = true;
					break;
				}
				//-4 significa que deberá esperar hasta que se pulse una tecla y cuando se haga borrar el texto y empezar desde el principio
				case -4:
				{
					//Por ahora lo único que hará será borrar el texto y esperar un segundo
					paused = true;
					restart = true;
					waiting = true;
					break;
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
			this->texto->addCharacter(nextChar,color);
			nextFrame++;
		}
		step += sp;
	}
	else if (paused && waiting)
	{
		if (game->getInput()->keyPressed(Input::kC))
		{
			if (restart)
			{
				this->texto->setText("");
				restart = false;
			}
			waiting = false;
			paused = false;
		}
		step++;
		if (step >= 30)
		{
			contFrame = (contFrame + 1)%2;
			tiledContinue->setTile(0, 0, 9+contFrame);
			step = 0;
		}
	}
	else if(step !=0)
	{
		step += sp;
		if (step >= 3)
			step =0;
	}
	// Hemos terminado
	else if (nextFrame >= charMap->size())
	{
		waiting = true;
		if (game->getInput()->keyPressed(Input::kC))
			instance_destroy();
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
	int** mapa = (int **) malloc(col *sizeof(int*));
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
	//marco->getMapImage();

	//Le digo que el grafico de esta entidad es el susodicho marco para que lo pinte siempre que esta esté en pantalla
	graphic = marco;

	//Lo semitransparentamos
	graphic->setAlpha(0.9f);

	// Botón de continuar
	int** map = (int**)malloc(sizeof(int*)*1);
	map[0] = (int*) malloc(sizeof(int));
	map[0][0] = 9;
	tiledContinue->setMap(map, 1, 1);
	contFrame = 0;

	//tiledContinue->getMapImage();

	//Reinicializamos variables de control
	paused = false;
	restart = false;
	waiting = false;
	nextFrame = 0;
	step = 0;
	color = Color::White;

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
	if (visible)
		if (charMap)
		{
			Entity::onRender();
			if (waiting)
				tiledContinue->render(x+8*(marco->getCols()-1), y+8*(marco->getRows()-1));
			texto->render(x + marco->getTileWidth(), y + marco->getTileHeight());
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
	waiting = false;
	nextFrame = 0;
	step = 0;
	color = Color::White;

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
	waiting = false;
	nextFrame = 0;
	step = 0;
	color = Color::White;

	//Si habia un texto guardado en charMap lo borro
	if (charMap)
	{
		delete charMap;
		charMap = NULL;
	}
}