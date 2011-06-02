/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//by helping making it better or by playing it in its actual state.					//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 2, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//	  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.			//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#include "SolidGrid.h"

// Constructoras y destructora

SolidGrid::SolidGrid(int x, int y, int** grid, int tileW, int tileH, int columns, int rows)
	// Llamamos a la constructora de la clase padre
	: Mask(x, y, columns*tileW, rows*tileH, "solidgrid")
{
	// grid = NULL para no inicializar la matriz
	if (grid == NULL) {
		grid = (int**) calloc(columns, sizeof(int));
		for(int i = 0; i < columns; i++)
		{
			grid[i] = (int*) calloc(rows, sizeof(int));
			grid[i] = 0;
		}
	}

	this->grid = grid;

	this->tileW = tileW;
	this->tileH = tileH;
	colNumber = columns;
	rowNumber = rows;
}

// Constructora desde archivo
SolidGrid::SolidGrid(string fname) : Mask(0, 0, 0, 0, "solidgrid") {

	// Abrimos el archivo para lectura, pasado por parámetro
	FILE* file = NULL;
	file = fopen(fname.c_str(), "r");

	// Leemos del archivo el nº col, nº fil, y ancho y alto de celda
	fscanf(file, "%d", &colNumber);
	fscanf(file, "%d", &rowNumber);
	fscanf(file, "%d", &tileW);
	fscanf(file, "%d", &tileH);

	// Reservamos memoria para albergar la matriz de enteros
	grid = (int**) malloc(colNumber*sizeof(int));
	for(int i = 0; i < colNumber; i++)
		grid[i] = (int*) malloc(rowNumber*sizeof(int));

	// Leemos del archivo cada celda de la matriz guardada por filas
	for (int j = 0; j < rowNumber; j++)
		for (int i = 0; i < colNumber; i++){
			int temp;
			fscanf(file, "%d", &temp);
			grid[i][j] = temp;
		}

	// Cerramos el fichero
	fclose(file);

	// Cambiamos los valores de anchura y altura
	width = colNumber*tileW;
	height = rowNumber*tileH;
}

// Destructora
SolidGrid::~SolidGrid(){
	if (grid != NULL) deleteGrid();
}

// Métodos de la clase

// Método privado que borra la matriz grid
void SolidGrid::deleteGrid(){
	for (int i = 0; i < colNumber; i++){
			delete grid[i];
			grid[i] = NULL;
		}
	delete grid;
	grid = NULL;
}

// Setters & Getters

// Devuelve el ancho de un tile
int SolidGrid::getTileW() { return tileW; }

// Establece el nuevo valor del ancho del tile
void SolidGrid::setTileW(int tileW) { this->tileW = tileW; }

// Devuelve el valor de la altura de cada una de las posiciones de la matriz
int SolidGrid::getTileH() { return tileH; }

// Establece un nuevo valor para la altura del tile
void SolidGrid::setTileH(int tileH) { this->tileH = tileH;}

// Obtiene el número de columnas de la matriz
int SolidGrid::getColNumber() { return colNumber; }

// Método privado que redimensiona la matriz
void SolidGrid::resizeGrid(int nCol, int nRow) {
	// Comprobamos que el nuevo tamaño es válido
	if (nCol > 0 && nRow > 0) {
		// Creamos una nueva matriz
		int** aux = (int**) calloc(nCol, sizeof(int*));
		for (int i = 0; i < nCol; i++)
			aux[i] = (int*) calloc(nRow, sizeof(int));

		// Copiamos los valores de la matriz antigua
		for (int i = 0; i < min(colNumber, nCol); i++)
			for (int j = 0; j < min(rowNumber, nRow); j++)
				aux[i][j] = grid[i][j];

		// Liberamos la matriz antigua
		if (grid != NULL) deleteGrid();

		// Asignamos la matriz auxiliar como la nueva matriz
		grid = aux;
	}
}

// Da un nuevo valor para el número de columnas de la matriz
void SolidGrid::setColNumber(int nCol) {
	// Sólo hacemos algo si se trata de un valor distinto al anterior
	if (nCol != colNumber) {
		// Redimensionamos la matriz
		resizeGrid(nCol, rowNumber);

		// Guardamos el nuevo valor de colNumber
		colNumber = nCol;
	}
}

// Obtiene el número de columnas de la matriz
int SolidGrid::getRowNumber() { return rowNumber; }

// Proporciona un valor nuevo para el número de filas de la matriz
void SolidGrid::setRowNumber(int nRow) {
	// Sólo hacemos algo si se trata de un valor distinto al anterior
	if (nRow != rowNumber) {
		// Redimensionamos la matriz
		resizeGrid(colNumber, nRow);

		// Guardamos el nuevo valor de rowNumber
		rowNumber = nRow;
	}
}

// Obtiene el valor del offset de la matriz (abscisa)
int SolidGrid::getXPos() {
	return x;
}

// Establece un nuevo valor para la coordenada X del offset de la matriz
void SolidGrid::setXPos(int xp) {
	// No modifica el valor si el nuevo es menor que 0
	if (xp >= 0)
		x = xp;
}

// Obtiene el valor del offset de la matriz (ordenada)
int SolidGrid::getYPos() {
	return y;
}

// Establece un nuevo valor para la coordenada Y del offset de la matriz
void SolidGrid::setYPos(int yp) {
	// No modifica el valor si el nuevo es menor que 0
	if (yp >= 0)
		y = yp;
}

// Obtiene el valor de la posición (i, j) de la matriz
// Devuelve -1 si (i, j) no es una posición válida
int SolidGrid::getCell(int i, int j){
    if ((i >= colNumber || j >= rowNumber) || ((i < 0) || (j < 0)))
        return -1;
    else
		return grid[i][j];
}

// Establece un nuevo valor para la posición (i, j) de la matriz
// No realiza cambios si (i, j) no es una posición válida
void SolidGrid::setCell(int i, int j, int type) {
    if ((i < colNumber) && (j < rowNumber) && (i > 0) && (j > 0))
        grid[i][j] = type;
}

// Obtiene el tipo de la celda de la matriz que contiene el punto (x, y)
int SolidGrid::getPosition(int x, int y) {
	// Comprobamos que se trata de una posición válida
	if (!isPointInbounds(x, y))
		return -1;
	// else, que no se pone
	// Vemos cuál es la celda a la que pertenece el punto (x, y)
	int i = getColumn(x);
	int j = getRow(y);
	// Devolvemos el valor de la posición (i, j) de la matriz
	if (i != -1 && j != -1)
		return grid[i][j];

	return -1;
}

// Establece el tipo de la celda de la matriz que contiene el punto (x, y)
void SolidGrid::setPosition(int x, int y, int type) {
	// Comprobamos que se trata de un punto válido de la matriz
	if (isPointInbounds(x, y)) {
		// vemos cuál es la celda a la que pertenece el punto (x, y)
		int i = getColumn(x);
		int j = getRow(y);
		// Modificamos el valor de la posición (i, j) de la matriz si type es un tipo válido
		if (type >= 0 && i != -1 && j != -1)
			grid[i][j] = type;
	}
	// Si no, no hacemos nada
}

// Obtiene la columna a la que pertenece la coordenada X
int SolidGrid::getColumn(int x) {
	// Si el tile tiene un ancho mayor que 0 y x está dentro de SolidGrid
	if (tileW > 0 && isPointInbounds(x, getYPos()))
		return (x - getXPos()) / tileW;

	return -1;
}

// Obtiene la fila a la que pertenece la coordenada Y
int SolidGrid::getRow(int y) {
	// Si el tile tiene una altura mayor que 0 e y está dentro de SolidGrid
	if (tileH > 0 && isPointInbounds(getXPos(), y))
		return (y - getYPos()) / tileH;

	return -1;
}

// Comprueba si una máscara colisiona con el SolidGrid
vector<CollisionPair>* SolidGrid::collide(Mask* other) {
	// Comprobamos la colisión con la máscara que envuelve al SolidGrid
	if (other == NULL)
		return NULL;

	// Devolvemos NULL si no hay colisión
	if (!isMaskInbounds(other))
		return NULL;

	// Si no, es que hay colisión con la máscara => devolvemos los pares de colisión
	// Comprobamos de qué clase es instancia other
	if (MaskBox* m = dynamic_cast<MaskBox*>(other)) {
		// other es instancia de MaskBox
		int value = -1; 	// En esta variable se guarda temporalmente el valor de cada tile del SolidGrid
		CollisionPair cp; 	// Par de colisión para el tile actual
		cp.a = m->type;	// Tipo de la máscara de colisión en la que estamos

		// Instanciamos el vector de colisiones
		vector<CollisionPair>* coll_vector = new vector<CollisionPair>();

		// Tomamos las esquinas de la máscara

		// límite izquierdo
		int i1 = (m->posX() - getXPos()) / tileW;
		// límite superior
		int j1 = (m->posY() - getYPos()) / tileH;
		// límite derecho
		int i2 = ((m->posX() + m->width - 1) - getXPos()) / tileW;
		// límite inferior
		int j2 = ((m->posY() + m->height - 1) - getYPos()) / tileH;

        for (int i = i1; i <= i2; i++)
            for (int j = j1; j <= j2; j++)
                if ((
					// comprobamos que las colisiones no se salen del solidgrid por la derecha
					((j < rowNumber) && (i < colNumber)) &&
					// comprobamos que las colisiones no se salen del solidgrid por la izquierda
                    (j >= 0) && (i >= 0)) &&
					// comprobamos que el valor tiene colisión
                    (grid[i][j] > 0))
					// si tiene colisión, la damos
                {
					string t = "solid";	// A este string le añadiremos el tipo de sólido
					char c[256]; // Supongo que no tendremos más de 99 valores de sólidos
					t.append(itoa(grid[i][j], c, 10));
					cp.b = t;
					// Añadimos el nuevo CollisionPair al vector
					coll_vector->push_back(cp);
                }

		// Devolvemos el vector de pares de colisión
		return coll_vector;
	}

	if (MaskCircle* m = dynamic_cast<MaskCircle*>(other)) {
		// other es instancia de MaskCircle

		// Instanciamos el vector de colisiones
		vector<CollisionPair>* coll_vector = new vector<CollisionPair>();

        // Centro de la circunferencia
        int xcenter  = m->x + m->xoffset + (int) m->radius;
        int ycenter  = m->y + m->yoffset + (int) m->radius;

		// x del vértice superior izquierda del cuadrado que envuelve al círculo
		int x_or = m->x + m->xoffset;
		// y del vértice superior izquierda del cuadrado que envuelve al círculo
		int y_or = m->y + m->yoffset;

		int value = -1;
		// lado del cuadrado que envuelve al círculo
		int mlength = (int) (2*m->radius);

		// Tomamos las esquinas del cuadrado que envuelve al círculo
		// límite izquierdo
		int i1 = (x_or - getXPos()) / tileW;
		// límite superior
		int j1 = (y_or - getYPos()) / tileH;
		// límite derecho
		int i2 = ((x_or + mlength - 1) - getXPos()) / tileW;
		// límite inferior
		int j2 = ((y_or + mlength - 1) - getYPos()) / tileH;


		// Checkeamos todos los tiles comprendidos dentro de las 4 esquinas de la máscara para ver
		// si son 0 (no hay colisión) o no (la hay)
        for (int i = i1; i <= i2; i++)
            for (int j = j1; j <= j2; j++)
                if ((
					// comprobamos que las colisiones no se salen del solidgrid por la derecha
					((j < rowNumber) && (i < colNumber)) &&
					// comprobamos que las colisiones no se salen del solidgrid por la izquierda
                    (j >= 0) && (i >= 0)) &&
					// comprobamos que el valor tiene colisión
                    (value = grid[i][j] > 0))
					// si tiene colisión, la damos
					{
						string t = "solid";	// A este string le añadiremos el tipo de sólido
						char c[256]; // Supongo que no tendremos más de 99 valores de sólidos
						t.append(itoa(value, c, 10));
						// Creamos un MaskBox para el tile en cuestión
						MaskBox* tileMB = new MaskBox(getXPos() + i*tileW, getYPos() + j*tileH, tileW, tileH, t);

						// Colisión circular
						vector<CollisionPair>* c_collision = m->collide((Mask*) tileMB);

						// Deleteamos la MaskBox que ya no nos hace falta
						delete tileMB;
						if (c_collision != NULL)
						{
							// Copiamos el resultado de la colisión circular al vector de colisiones que teníamos
							coll_vector->resize(coll_vector->size() + c_collision->size());
							vector<CollisionPair>::iterator it;
							for (it = c_collision->begin(); it < c_collision->end(); it++)
								coll_vector->push_back(*it);

							// Deleteamos el vector de colisiones circulares, que ya no hace falta (creo)
							delete c_collision;
						}
					}

		// Devolvemos el vector de pares de colisión
		return coll_vector;
	}

	if (MaskList* m = dynamic_cast<MaskList*>(other)) {
		// other es instancia de MaskList
		// Devolvemos el vector de pares de colisión de la colisión contraria (haciendo flipAll)
		return Mask::flipAll(m->collide(this));
	}

	return NULL;
}

// Comprueba si la posición indicada está dentro del SolidGrid
bool SolidGrid::isPointInbounds(int x, int y) {
	return
		(x >= getXPos() && y >= getYPos() &&
		 x < getXPos() + colNumber*tileW && y < getYPos() + rowNumber*tileH);
}

// Comprueba si la máscara en cuestión está dentro del SolidGrid
bool SolidGrid::isMaskInbounds(Mask* mask) 
{
	if (mask == NULL)
		return false;

	// La máscara estará dentro del SolidGrid si lo está alguno de sus cuatro vértices
	// Vértice superior izquierdo
	int x1 = mask->x + mask->xoffset;
	int y1 = mask->y + mask->yoffset;
	// Vértice inferior derecho
	int x2 = mask->x + mask->xoffset + mask->width;
	int y2 = mask->y + mask->yoffset + mask->height;

	return
		(isPointInbounds(x1, y1) ||						// Arriba-Izquierda
		 isPointInbounds(x1, y2) || 					// Abajo-Izquierda
		 isPointInbounds(x2, y1) || 					// Arriba-Derecha
		 isPointInbounds(x2, y2)); 	                    // Abajo-Derecha
}
