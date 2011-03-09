#include "SolidGrid.h"

// Constructoras y destructora

SolidGrid::SolidGrid(int x, int y, int** grid, int tileW, int tileH, int columns, int rows)
	// Llamamos a la constructora de la clase padre
	: Mask(x, y, colNumber*tileW, rowNumber*tileH, "solidgrid")
{
	// grid = NULL para no inicializar la matriz
	if (grid != NULL) {
		grid = (int**) calloc(colNumber, sizeof(int));
		for(int i = 0; i < colNumber; i++)
			grid[i] = (int*) calloc(rowNumber, sizeof(int));
	}

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
	// Devolvemos NULL si no hay colisión
	if (!isMaskInbounds(other))
		return NULL;

	// Si no, es que hay colisión con la máscara => devolvemos los pares de colisión
	// Comprobamos de qué clase es instancia other
	if (MaskBox* m = dynamic_cast<MaskBox*>(other)) {
		// other es instancia de MaskBox
		int value = -1; 	// En esta variable se guarda temporalmente el valor de cada tile del SolidGrid
		CollisionPair cp; 	// Par de colisión para el tile actual
		cp.b = m->type;	// Tipo de la máscara de colisión en la que estamos

		// Instanciamos el vector de colisiones
		vector<CollisionPair>* coll_vector = new vector<CollisionPair>();

		// A partir del punto en el que comienza el MaskBox, comprobamos la colisión tile a tile
		for (int i = m->posX(); i <= (m->posX() + m->width); i += min(tileW, m->width))
			for (int j = m->posY(); j <= (m->posY() + m->height); j += min(tileH, m->height))

				// Si en la posición (i, j) hay un sólido...
				if ((value = getPosition(i, j)) > 0) {
					string t = "solid";	// A este string le añadiremos el tipo de sólido
					char* c = (char*) calloc(3, sizeof(char)); // Supongo que no tendremos más de 99 valores de sólidos
					t.append(itoa(value, c, 10));
					cp.a = t;
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
        int xcenter  = m->x + m->xoffset + m->radius;
        int ycenter  = m->y + m->yoffset + m->radius;

		// x del vértice superior izquierda del cuadrado que envuelve al círculo
		int x_or = m->x + m->xoffset;
		// y del vértice superior izquierda del cuadrado que envuelve al círculo
		int y_or = m->y + m->yoffset;

		int value = -1;
		int mlength = 2*m->radius;
		// A partir del punto en el que comienza el cuadrado del círculo, comprobamos la colisión tile a tile
		for (int i = x_or; i <= (x_or + mlength); i += min(tileW,mlength))
			for (int j = y_or; j <= (y_or + mlength); j += min(tileH,mlength))

				// Si en la posición (i, j) hay un sólido...
				if ((value = getPosition(i, j)) > 0) {
					string t = "solid";	// A este string le añadiremos el tipo de sólido
					char* c = (char*) calloc(3, sizeof(char)); // Supongo que no tendremos más de 99 valores de sólidos
					t.append(itoa(value, c, 10));
					// Creamos un MaskBox para el tile en cuestión
					MaskBox* tileMB = new MaskBox(getXPos() + getColumn(i)*tileW, getYPos() + getRow(j)*tileH, tileW, tileH, t);

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
bool SolidGrid::isMaskInbounds(Mask* mask) {
	// La máscara estará dentro del SolidGrid si lo está alguno de sus cuatro vértices
	// Vértice superior izquierdo
	int x1 = mask->x + mask->xoffset;
	int y1 = mask->y + mask->yoffset;
	// Vértice superior derecho
	int x2 = mask->x + mask->xoffset + mask->width;
	int y2 = mask->y + mask->yoffset + mask->height;

	return
		(isPointInbounds(x1, y1) ||						// Arriba-Izquierda
		 isPointInbounds(x1, y2) || 					// Abajo-Izquierda
		 isPointInbounds(x2, y1) || 					// Arriba-Derecha
		 isPointInbounds(x2, y2)); 	                    // Abajo-Derecha
}
