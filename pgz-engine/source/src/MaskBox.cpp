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
