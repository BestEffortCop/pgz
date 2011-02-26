#include "MaskCircle.h"

//Constructora MaskCircle, llamamos a la constructora de Mask con los parametros adecuados
MaskCircle::MaskCircle(int x, int y, int width, int height, string type, int xc, int yc, float r):Mask(x, y, width, height, type){
	xcenter = xc;
	ycenter = yc;
	radius = r;
}

vector<CollisionPair>* MaskCircle::collide(Mask* other){
	vector<CollisionPair>* collPairs = Mask::collide(other); // Llamamos al padre para comprobar colisión simple de las Masks
	if (collPairs == NULL)			// Comprobamos si hubo colisión
		return NULL;				// Si no hubo devolvemos NULL
	else {	// Hubo collisión, comprobamos si los elementos internos verdaderamente colisionan
		CollisionPair collPair;			// Preparamos un CollisionPair por si hay colisión 
		collPair.a = type;
		collPair.b = other->type;
				
		//--- Colisión MaskCircle con CircleMask ---//
		if (MaskCircle* maskC = dynamic_cast<MaskCircle *> (other)){	// Probamos hacer un cast a MaskCircle
			float collDistance = radius + maskC->radius;		// Distancia en la que collisionan las dos circunferencias
			float distance = getDistance(xcenter, maskC->x, ycenter, maskC->y);	// Distancia actual entre los las máscaras
			if (distance < collDistance){		// Hay colisión
				collPairs->push_back(collPair);	// Introducimos el par de collisión en el vector de colisiones
			}
		}

		//--- Colisión MaskCircle con MaskBox ---//
		else if (MaskBox* maskC = dynamic_cast<MaskBox *> (other)){
			float distance = -1.f;	// Guardaremos aquí la distancia del círculo a la esquina del MaskBox
			
			// Comprobamos casos en los que la MaskCircle NO está ubicada perpendicular respecto a los lados de la MaskBox
			if (x < maskC->x){		// Parte izquierda
				if (y < maskC->y)						// Esquina arriba-izquierda
					distance = getDistance(xcenter, maskC->x, ycenter, maskC->y);
				else if (y > maskC->y + maskC->height)	// Esquina abajo-izquierda
					distance = getDistance(xcenter, maskC->x, ycenter, maskC->y + maskC->height);
			}
			else if (x > maskC->x +	maskC->width){	// Parte derecha
				if (y < maskC->y)						// Esquina arriba-derecha
					distance = getDistance(xcenter, maskC->x + maskC->width, ycenter, maskC->y);
				else if (y > maskC->y + maskC->height)	// Esquina abajo-derecha
					distance = getDistance(xcenter, maskC->x + maskC->width, ycenter, maskC->y + maskC->height);
			}
			// Comprobamos si hubo cambio en distance, en cuyo caso tambien comprobamos la colisión
			if (distance >= 0 && distance < radius){ // Si la distancia a la esquina es menor que el radio colisionamos
				collPairs->push_back(collPair);	// Introducimos el par de collisión en el vector de colisiones
			}

			// La cirurferencia es perpendicular a los lados del MaskBox y por tanto se comporta como un cuadrado de lado radius
			else {
				// Averiguamos si colisionan
				if (checkBoxCollision(maskC->x, maskC->y, maskC->width, maskC->height))
					collPairs->push_back(collPair);	// Introducimos el par de collisión en el vector de colisiones
			}
		}

		//--- Colisión MaskCircle con MaskBox ---//
		else if (MaskList* maskC = dynamic_cast<MaskList *> (other)){
			// Si es una MaskList delegamos el trabajo (faltaria hacer un flip)
			vector<CollisionPair> *auxCollPairs = maskC->collide(this);
			if (auxCollPairs != NULL){
				vector<CollisionPair>::iterator it;		// Creamos un iterador de CollisionPair
				it = collPairs->end();					// Lo colocamos al final de collPairs
				// Añadimos las colisiones que se hayan producido con MaskList
				collPairs->insert(it, auxCollPairs->begin(), auxCollPairs->end());
			}
		}
	}
	return collPairs;	// Job done! devolvemos los resultados
}

float MaskCircle::getDistance (int x1, int x2, int y1, int y2){
	return sqrt((float)((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}

bool MaskCircle::checkBoxCollision(int bx, int by, int bwidth, int bheigth){
	int left1 = x;							// Límite izquierdo circunferencia
    int left2 = bx;							// Límite izquierdo rectángulo
    int right1 = x + width;					// Límite derecho circunferencia
    int right2 = bx + bwidth;				// Límite derecho rectángulo
    int top1 = y;							// Límite superior circunferencia
    int top2 = by;							// Límite superior rectángulo
    int bottom1 = y + height;				// Límite inferior circunferencia
    int bottom2 = by + bheigth;				// Límite inferior rectángulo

	// Vamos comprobando colisiones, 
	// Si no hay colisión devolvemos NULL
    if (bottom1 < top2)	return false;		// Si la parte inferior de una NO collisiona con la superior de la otra
	if (top1 > bottom2) return false;		// Si la parte superior de una NO collisiona con la inferior de la otra
	if (right1 < left2) return false;		// Si la parte derecha de una NO collisiona con la izquierda de la otra
	if (left1 > right2) return false; 		// Si la parte izquierda de una NO collisiona con la derecha de la otra
	
	// Si las comprobaciones anteriores fallan entonces las máscaras colisionan
	return true;	
}