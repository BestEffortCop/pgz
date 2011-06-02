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

#include "Mask.h"

// Constructora, asignamos los parametros a los atributos correspondientes de Mask
Mask::Mask(int x, int y, int width, int height, string type, int xoffset, int yoffset){
	this->x = x;
	this->y = y;
    this->xoffset = xoffset;
	this->yoffset = yoffset;
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

	int left1 = x + xoffset;							    // Límite izquierdo Mask1
    int left2 = other->x + other->xoffset;					// Límite izquierdo Mask2
    int right1 = left1 + width;			        	    	// Límite derecho Mask1
    int right2 = left2 + other->width;	                    // Límite derecho Mask2
    int top1 = y + yoffset;					        		// Límite superior Mask1
    int top2 = other->y + other->yoffset;					// Límite superior Mask2
    int bottom1 = top1 + height;				            // Límite inferior Mask1
    int bottom2 = top2 + other->height;	                    // Límite inferior Mask2

	// Vamos comprobando colisiones,
	// Si no hay colisión devolvemos NULL
    if (bottom1 <= top2)	return NULL;		// Si la parte inferior de una NO collisiona con la superior de la otra
	if (top1 >= bottom2) return NULL;		// Si la parte superior de una NO collisiona con la inferior de la otra
	if (right1 <= left2) return NULL;		// Si la parte derecha de una NO collisiona con la izquierda de la otra
	if (left1 >= right2) return NULL; 		// Si la parte izquierda de una NO collisiona con la derecha de la otra

	// Si las comprobaciones anteriores fallan entonces las máscaras colisionan
	vector<CollisionPair> *collPairs = new vector<CollisionPair>();	// Creamos un vector de CollisionPair
	return collPairs;					// Devolvemos el vector de pares de collisión vacío
										// las clases que heredan se ocupan de rellenarlo
}

void Mask::setXY(int x, int y){
    this->x = x;
    this->y = y;
}

int Mask::posX(){
	return x + xoffset;
}

int Mask::posY(){
	return y + yoffset;
}

vector<CollisionPair>* Mask::flipAll(vector<CollisionPair>* vect){
	if (vect != NULL)
	{
		string aux;
		for (unsigned int i=0; i<vect->size(); i++){		// Para cada elemento del vector de pares
			aux = vect->at(i).a;				// Intercambiamos los valores
			vect->at(i).a = vect->at(i).b;		// Modificando los punteros de cada par
			vect->at(i).b = aux;
		}

		return vect;
	}
	else return NULL;
}
