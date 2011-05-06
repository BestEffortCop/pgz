#include "TileTextLabel.h"


TileTextLabel::TileTextLabel(string texto, Font* font, GfxEngine* gfxEngine,int columns, int rows):TextLabel(texto)
{
	//Apuntamos al motor grafico
	this->gfxEngine = gfxEngine;
	//Me guardo la tileFont por si alguien la ha creado como una Font y no se ha preocupado de guardarla
	this->tileFont = (TileFont*) font;
	//Creamos el tileMap con el tamaño de tile del tileset de la fuente
	tileMap = new FriendlyTileMap(tileFont->getTileW(),tileFont->getTileH(),gfxEngine);
	//Indicamos al tileMap que su tileSet es el de la funte
	tileMap->setTileSet(tileFont->getTileSet());
	//Si no me pasan las filas y columnas las pongo yo como vea
	if (columns == 0 && rows == 0)
	{
		rows = 0;
		columns = 0;
		tileMap->setRows(rows);
		tileMap->setCols(columns);
		sizeSetted = false;
	}
	else
	{
		//Me creo el mapa de tiles que le voy a pasar al tileMap
		int** mapa = (int **) malloc(columns *sizeof(int*));
		for(int i = 0; i < columns; i++)
				mapa[i] = (int *) malloc(rows*sizeof(int));
		//Y se lo paso junto al tamaño a tileMap
		tileMap->setMap(mapa, columns, rows);

		//Le aviso de que cree su imagen con el tamaño que le he pedido
		//this->tileMap->getMapImage();
	}
	//Escribimos el texto en el tileMap
	setText(texto);
}


TileTextLabel::TileTextLabel(Font* font, GfxEngine* gfxEngine,int columns, int rows):TextLabel("")
{
	//Apuntamos al motor grafico
	this->gfxEngine = gfxEngine;
	//Me guardo la tileFont por si alguien la ha creado como una Font y no se ha preocupado de guardarla
	this->tileFont = (TileFont*) font;
	//Creamos el tileMap con el tamaño de tile del tileset de la fuente
	tileMap = new FriendlyTileMap(tileFont->getTileW(),tileFont->getTileH(),gfxEngine);
	//Indicamos al tileMap que su tileSet es el de la funte
	tileMap->setTileSet(tileFont->getTileSet());
	//Si no me pasan las filas y columnas las pongo yo como vea
	if (columns == 0 && rows == 0)
	{
		rows = 0;
		columns = 0;
		tileMap->setCols(columns);
		tileMap->setRows(rows);
		sizeSetted = false;
	}
	else
	{
		//Me creo el mapa de tiles que le voy a pasar al tileMap
		int** mapa = (int **) malloc(columns *sizeof(int*));
		for(int i = 0; i < columns; i++)
				mapa[i] = (int *) malloc(rows*sizeof(int));
		//Y se lo paso junto al tamaño a tileMap
		tileMap->setMap(mapa, columns, rows);

		//Le aviso de que cree su imagen con el tamaño que le he pedido
		//this->tileMap->getMapImage();
	}
}


TileTextLabel::~TileTextLabel()
{
	if (tileFont)
		tileFont = NULL;
	if (font)
		font = NULL;
	
	//Si existe tileMap
	if (tileMap)
	{
		//Lo borramos asegurándonos de no machacar la TileFont
		delete(tileMap);
		tileMap=NULL;
	}
}

void TileTextLabel::setSize(int rows, int columns)
{
	//Me creo el mapa de tiles que le voy a pasar al tileMap
	int** mapa = (int **) malloc(columns *sizeof(int*));
		for(int i = 0; i < columns; i++)
				mapa[i] = (int *) malloc(rows*sizeof(int));
	//Le paso al tileMap su nuevo mapa de tiles, sin nada por ahora
	tileMap->setMap(mapa, columns, rows);

	//Le aviso de que cree su imagen con el tamaño que le he pedido
	//this->tileMap->getMapImage();

	//Me guardo que el tamaño ha sido configurado por el usuario
	sizeSetted = true;
}


int TileTextLabel::getColumns(){return tileMap->getCols();}

int TileTextLabel::getRows(){return tileMap->getRows();}

int TileTextLabel::getTileH(){return tileMap->getTileset()->getTileH();}

int TileTextLabel::getTileW(){return tileMap->getTileset()->getTileW();}

int TileTextLabel::getWidth(){return tileMap->getWidth();}

int TileTextLabel::getHeight(){return tileMap->getHeight();}



void TileTextLabel::setScale(float scale)
{
	tileMap->setScale(scale,scale);
}

void TileTextLabel::setColor(Color c)
{
	tileMap->setColor(c);
}

void TileTextLabel::setRotation(float angle)
{
	tileMap->setRotation(angle);
}

void TileTextLabel::setAlpha(float alpha)
{
	tileMap->setAlpha(alpha);
}

bool TileTextLabel::addCharacter(char c, Color color)
{
    //Si la letra que quieres añadir se sale del tamaño del tileMap y el tamaño ha sido confugurado devolvemos false
	if ((myText.size() + 1) > tileMap->getCols() * tileMap->getRows())
		return false;

	//Le pregunto a la fuente donde tiene el caracter que yo quiero pintar
	int pos = tileFont->getGlyphId(c);

	//Concateno ese caracter al texto que llevo
	myText = myText.append(&c);

	//Calculo el tamaño del texto para saber que en que posicion me toca esribir
	int size = (myText.size()) - 1;

	//Calculo a partir del caracter que va, en que posicion (x,y) toca escribir
	int x = size % tileMap->getCols();
	int y = size / tileMap->getCols();

	//Pinto la nueva letra
	tileMap->setTileExt(x , y, pos, color, alpha, scale, scale, rotation);

	return true;
};


int TileTextLabel::setText(string text, TextMode m)
{
	
	//Me guardo las filas y columnas del tileMap
	int fils = tileMap->getRows();
	int cols = tileMap->getCols();
	
	//Si estoy en modo rewrite, paso de lo que hubiera escrito y escribo desde 0
	if (m == REWRITE)
		myText = text;
	//Si estoy en modo append concateno al final del texto lo que quiero escribir
	else if (m == APPEND)
		myText = myText.append(text);
		
	//Si no se han configurado nunca las filas y columnas y no cabe las apaño yo para que quepa
	if (!sizeSetted && myText.size() > cols*fils)
	{
		//Apaño las nuevas filas y columnas para que quepa
		fils = 1;
		cols = myText.size();
		//Me creo el mapa de tiles que le voy a pasar al tileMap
		int** mapa = (int **) malloc(cols *sizeof(int*));
		for(int i = 0; i < cols; i++)
				mapa[i] = (int *) malloc(fils*sizeof(int));
		//Le paso al tileMap su nuevo mapa de tiles, si nada por ahora
		tileMap->setMap(mapa, cols, fils);

		//Le aviso de que cree su imagen con el tamaño que le he pedido
		//this->tileMap->getMapImage();
	}
	//Limpio la imagen para que no pinte tiles encima de tiles y se emborrone con ello
	//gfxEngine->clearImageTransparent(tileMap->getMapImage());
	tileMap->clear();

	//Mientras no se haya acabado ni el espacio ni el texto voy pintando todos los tiles
	int i = 0;
	while((i < cols*fils) && (i < myText.size()))
	{
		tileMap->setTile(i % cols,i / cols,tileFont->getGlyphId(myText.at(i)));
		i++;
	}
	//Devuelvo el numero de tiles que he podido pintar
	return i + 1;
}


void TileTextLabel::render(int x, int y)
{
	tileMap->render(x,y);
}


