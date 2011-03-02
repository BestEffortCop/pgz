#include "Mask.h"

// Constructora, asignamos los parametros a los atributos correspondientes de Mask
Mask::Mask(int x, int y, int width, int height, string type){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
}

// Destructora por defecto
Mask::~Mask(){
}

vector<CollisionPair>* Mask::collide(Mask* other){
	//Consideramos Mask1 como nuestra máscara y Mask2 como 
	//la otra máscara con la que comprobamos colisión (other)

	int left1 = x;							// Límite izquierdo Mask1
    int left2 = other->x;					// Límite izquierdo Mask2
    int right1 = x + width;					// Límite derecho Mask1
    int right2 = other->x + other->width;	// Límite derecho Mask2
    int top1 = y;							// Límite superior Mask1
    int top2 = other->y;					// Límite superior Mask2
    int bottom1 = y + height;				// Límite inferior Mask1
    int bottom2 = other->y + other->height;	// Límite inferior Mask2

	// Vamos comprobando colisiones, 
	// Si no hay colisión devolvemos NULL
    if (bottom1 < top2)	return NULL;		// Si la parte inferior de una NO collisiona con la superior de la otra
	if (top1 > bottom2) return NULL;		// Si la parte superior de una NO collisiona con la inferior de la otra
	if (right1 < left2) return NULL;		// Si la parte derecha de una NO collisiona con la izquierda de la otra
	if (left1 > right2) return NULL; 		// Si la parte izquierda de una NO collisiona con la derecha de la otra
	
	// Si las comprobaciones anteriores fallan entonces las máscaras colisionan
	vector<CollisionPair> *collPairs = new vector<CollisionPair>();	// Creamos un vector de CollisionPair
	return collPairs;					// Devolvemos el vector de pares de collisión vacío
										// las clases que heredan se ocupan de rellenarlo
}

void Mask::flipAll(vector<CollisionPair>* vect){
	string aux;
	for (int i=0; i<vect->size(); i++){		// Para cada elemento del vector de pares
		aux = vect->at(i).a;				// Intercambiamos los valores
		vect->at(i).a = vect->at(i).b;		// Modificando los punteros de cada par
		vect->at(i).b = aux;
	}
}