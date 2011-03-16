#include "MaskBox.h"

// Constructora vacía ya que la máscara es la global (la del padre)
MaskBox::MaskBox(int x, int y, int width, int height, string type, int xoffset, int yoffset):
	Mask(x, y, width, height, type, xoffset, yoffset){}

// Destructora vacía ya que lo hace el padre Mask
MaskBox::~MaskBox(){}

vector<CollisionPair>* MaskBox::collide(Mask* other){
	// Vemos primero si colisionan las máscaras globales (las del padre)
	vector<CollisionPair>* collPairs = Mask::collide(other);

	// Si no colisionan, entonces tampoco colisiona la caja, ya que son la misma
	if (collPairs == NULL) return NULL;
	else{ // Si colisionan las globales, las cajas también

		// Colisión con MaskBox
		if (MaskBox* maskB = dynamic_cast<MaskBox *> (other)){
			// Preparamos el par con los tipos de la colision
			CollisionPair collPair;
			collPair.a = type;
			collPair.b = other->type;
			// Metemos el par en el vector
			collPairs->push_back(collPair);
		}

		// Colisión con MaskCircle
		else if(MaskCircle* maskC = dynamic_cast<MaskCircle *> (other)){
			delete collPairs; // eliminamos el vector vacío creado en mask, para no dejar basura
			collPairs = maskC->collide(this); // delegamos el trabajo en la máscara círcular
			// Damos la vuelta a los pares de la lista, ya que la colisión realmente ha sido al revés
			Mask::flipAll(collPairs);
		}

		// Colisión con MaskList
		else if (MaskList* maskL = dynamic_cast<MaskList *> (other)){
			delete collPairs; // eliminamos el vector vacío creado en mask, para no dejar basura
			collPairs = maskL->collide(this); // delegamos el trabajo en la lista de máscaras
			// Damos la vuelta a los pares de la lista, ya que la colisión realmente ha sido al revés
			Mask::flipAll(collPairs);
		}

		// Colisión con SolidGrid
		else if (SolidGrid* grid = dynamic_cast<SolidGrid *> (other)){
			delete collPairs;
			collPairs = grid->collide(this);
			// Damos la vuelta a los pares de la lista, ya que la colisión realmente ha sido al revés
			Mask::flipAll(collPairs);
		}

		return collPairs; // devolvemos el vector de pares de colisiones

	} // Fin de else (han colisionado)
}
