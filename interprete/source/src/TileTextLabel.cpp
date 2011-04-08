#include "TileTextLabel.h"


TileTextLabel::TileTextLabel(string texto, TileFont* font, GfxEngine* gfxEngine,int columns, int rows):TextLabel(texto)
{
	//Apuntamos al motor grafico
	this->gfxEngine = gfxEngine;
	//Creamos el tileMap con el tamaño de tile del tileset de la fuente
	tileMap = new TileMap(font->getTileW(),font->getTileH(),gfxEngine);
	//Indicamos al tileMap que su tileSet es el de la funte
	tileMap->setTileSet(font->getTileSet());
	//Escribimos el texto en el tileMap
	setText(texto);

	//Si no me pasan las filas y columnas las pongo yo como vea
	if (columns == 0 && rows == 0)
	{
		rows = font->getTileH();
		columns = font->getTileW()*texto.size();
	}
	setColumns(columns);
	setRows(rows);
}

/*
TileTextLabel::TileTextLabel(TileFont* font, GfxEngine* gfxEngine,int w, int h):TextLabel("")
{
	//Apuntamos al motor grafico
	this->gfxEngine = gfxEngine;
	//Creamos el tileMap con el tamaño de tile del tileset de la fuente
	tileMap = new TileMap(font->getTileW(),font->getTileH(),gfxEngine);
	//Indicamos al tileMap que su tileSet es el de la funte
	tileMap->setTileSet(font->getTileSet());
	if (w == 0 && h == 0)
	{
		h = font->getTileH();
		w = font->getTileW();
	}

}
*/

TileTextLabel::~TileTextLabel()
{
	//Si existe tileMap
	if (tileMap)
	{
		//Lo borramos
		delete(tileMap);
		tileMap=NULL;
	}
}

void TileTextLabel::setColumns(int columns){tileMap->setCols(columns);}
void TileTextLabel::setRows(int rows){tileMap->setRows(rows);}


void TileTextLabel::setScale(float scale)
{
	TextLabel::setScale(scale);
	tileMap->setScale(scale,scale);
	Graphic::setScale(scale,scale);
}


bool TileTextLabel::addCharacter(char c, Color color)
{
    //Si la latra que quieres añadir se sale del tamaño del tileMap devolvemos false
	if ((myText.size() + 1) >= tileMap->getCols() * tileMap->getRows())
		return false;
		
	//Le pregunto a la fuente donde tiene el caracter que yo quiero pintar
	int pos = font->getGlyphId(c);
	//Concateno ese caracter al texto que llevo
	myText = myText.append(&c);

	//Calculo el tamaño del texto para saber que en que posicion me toca esribir
	int size = myText.size();
	
	//Calculo a partir del caracter que va, en que posicion (x,y) toca escribir
	int x = size % tileMap->getWidth();
	int y = size / tileMap->getWidth();

	/* 
    dibuja sobre mapImage el tile de tileSet de coordenadas especificadas:
    (pos % tileSet->getColumns())*w 
    (pos / tileSet->getColumns())*h
    */
    if (tileMap->getMapImage() != NULL)
			//Si el sitio donde quiero pintar está dentro de la pantalla
            if ( ((TileFont*) font)->getTileSet()->getColumns() > 0 && ((TileFont*) font)->getTileSet()->getRows() > 0)
					//Pinto
                    gfxEngine->renderPartExt(((TileFont*) font)->getTileSet()->getImg(), //Imagen
					x*((TileFont*) font)->getTileW(), y*((TileFont*) font)->getTileH(), //Posicion en la que se va a pintar
					(pos % ((TileFont*) font)->getTileSet()->getColumns())*((TileFont*) font)->getTileSet()->getTileW(), //coordenada x de la posicion del tile en el tileSet
					(pos / ((TileFont*) font)->getTileSet()->getColumns())*((TileFont*) font)->getTileSet()->getTileH(), //coordenada y de la posicion del tile en el tileSet
					((TileFont*) font)->getTileSet()->getTileW(), ((TileFont*) font)->getTileSet()->getTileH(), //Ancho y alto de cada tile
					color, alpha, scaleH, scaleV, rotation, tileMap->getMapImage(), //Caracteristias de lo que se va a pintar y imagen sobre la que va a hacerlo
					((TileFont*) font)->getTileSet()->getTileW()/2, ((TileFont*) font)->getTileSet()->getTileH()/2); //origen????
	return true;
};


int TileTextLabel::setText(string myText, TextMode m)
{
	int fils = tileMap->getRows();
	int cols = tileMap->getCols();

	this->myText = myText;

	if ( cols == 0 && fils == 0)
	{
		fils = ((TileFont*) font)->getTileH();
		cols = (((TileFont*) font)->getTileW()*myText.size());
	}

	int** mapa = (int **) malloc(cols *sizeof(int));
    for(int i = 0; i < cols; i++)
            mapa[i] = (int *) malloc(fils*sizeof(int));


	for (int i = 0; i < fils; i++)
		for (int j = 0; j < cols; j++)
		{
			mapa[i][j] = myText.at((j*cols) + i);
		}
	tileMap->setMap(mapa, cols, fils);
	return 37;
}


void TileTextLabel::onRender(int x, int y)
{
	tileMap->render(x,y);
}


