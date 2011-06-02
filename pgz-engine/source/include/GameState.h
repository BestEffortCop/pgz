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

#pragma once
#ifndef __GAMESTATEH__
#define __GAMESTATEH__

#include "Game.h"
#include "Entity.h"
#include "Mask.h"
#include "MaskBox.h"
#include "Map.h"

#include <vector>
#include <list>
#include <stdlib.h>

class Game;
class Entity;
class Mask;
class Map;

//! La clase GameState representa un estado del juego en un momento del tiempo.
/*!
	La clase GameState realiza una de las principales labores dentro de la parte lógica del motor:
	permite el desarrollo de entidades dentro del juego así como su interacción entre ellas. GameState representa un estado del juego en un cierto tiempo.
*/
/*!
	Dentro de GameState tenemos una lista de entidades que están presentes dentro del juego en este momento. Además puede contener un mapa del juego.
*/

/*!
	GameState se encarga de dos tareas principales: update y render.
*/

class GameState
{
    protected:

        // Listas de entidades
        list<Entity*>* entities;         // Todas las entidades dentro del juego
        list<Entity*>* enabled;          // Entidades que deben actualizarse
        list<Entity*>* collidable;       // Entidades susceptibles a colisionar entre ellas
        list<Entity*>* renderable;     // Entidades que deben pintarse, ordenadas según profundidad

        // Buffers de entidades. Su contenido se actualizará a las listas de entidades al final del tick
        list<Entity*>* addedEntitiesBuffer;      // Entidades a añadir
        list<Entity*>* deletedEntitiesBuffer;    // Entidades a borrar
        list<Entity*>* enabledBuffer;            // Entidades en las que ha cambiado su estado enabled
        list<Entity*>* collidableBuffer;         // Entidades en las que ha cambiado su estado collidable
        list<Entity*>* renderableBuffer;               // Entidades en las que ha cambiado su estado renderable


        Map* map;
        int roomw;
        int roomh;

        // Se encarga de inicializar tanto buffers como listas de entidades
        virtual void init();

		// Añade la entidad a la lista lsólo si no existe en ella
		virtual bool add_single(list<Entity*>* l, Entity* ent);

        // Añade una entidad al mundo de forma directa
        virtual bool _add(Entity* e);
        // Borra una entidad del mundo de forma directa
        virtual bool _remove(Entity* e);

        // Comprueba si una máscara colisiona o no con los elementos del mapa
        virtual bool collide_mask(Mask* m);

		// Comprueba si una entidad colisiona o no con los elementos del mapa
		virtual bool collide_entity(Entity* e);

		// Comprueba si una entidad va antes que otra para realizar el correcto renderizado
		static bool entity_compare(Entity* a, Entity* b);

	public:

		//!Referencia a la clase Game que lo ha creado
		Game* game;

		//! Constructora sin mapa.
		/*!
			\param g Juego al que pertenece el estado.
			\param roomw Ancho de la pantalla.
			\param roomh Alto de la pantalla.
		*/
		GameState(Game* g, int roomw, int roomh);

		//! Constructora con mapa.
		/*!
			\param g Juego al que pertenece el estado.
			\param m Mapa del juego.
			\param roomw Ancho de la pantalla.
			\param roomh Alto de la pantalla.
		*/
		GameState(Game* g, Map* m, int roomw, int roomh);

		//! Destructora por defecto.
		virtual ~GameState();

		//! Permite al usuario implementar acciones que se realicen cuando el estado pase a ser el actual.
		virtual void onInit();

		//! Permite al usuario implementar acciones que se realicen cuando el estado deje de ser el actual.
		virtual void onEnd();

		//! Actualiza por defecto las entidades y comprueba las colisiones.
		virtual void _update();

		//! El usuario puede sobreescribir según sus necesidades el método _update().
		/*!
			\sa _update();
		*/
		virtual void onStep();

		//! Permite al usuario pintar lo que desee por debajo de los elementos del gameState.
		virtual void renderBG();

		//! Pinta todas las entidades renderizables del gameState.
		virtual void onRender();

		//! Permite al usuario pintar lo que desee por encima de todos los elementos del gameState.
		virtual void renderFG();

		//! Añade un mapa al juego. Si existe ya uno, lo sustituye.
		/*!
			\param map Mapa que queremos poner.
		*/
		virtual void addMap(Map* map);

		//! Elimina el mapa del gamestate, borrándolo si se solicita.
		/*!
			\param deleteToo Si se debe borrar efectivamente el mapa o no.
		*/
		virtual void removeMap(bool deleteToo = true);

		//! Borra todas las entidades que hay en GameState.
		virtual void removeAll();

		/*********************************************************************\
		*	Métodos que tienen efecto al final del tick						  *
		\*********************************************************************/

		//! Añade una entidad al GameState.
		/*!
			\param e Entidad a añadir.
			\return True si la entidad se ha añadido correctamente, falso si ya existía.
		*/
		virtual bool add(Entity* e);

		//! Elimina una entidad de las existentes en GameState.
		/*!
			\param e Entidad que vamos a eliminar.
			\return True si la entidad se ha borrado correctamente, falso si no existía.
		*/
		virtual bool remove(Entity* e);

		//! Añade a GameState las entidades que contiene la lista de entrada.
		/*!
			\param l Lista de entidades a incorporar.
		*/
		virtual void addList(vector<Entity*>* l);

		//! Borra las entidades de GameState que están en la lista de entrada.
		/*!
			\param l Lista de entidades a eleminar.
		*/
		virtual void removeList(vector<Entity*>* l);

		//! Conmuta la propiedad renderable de la entidad.
		/*!
			\param e Entidad que modifica su estado.
		*/
		virtual void changedRenderable(Entity* e);

		//! Conmuta la propiedad de colisión de la entidad.
		/*!
			\param e Entidad que modifica su estado.
		*/
		virtual void changedCollidable(Entity*e);

		//! Conmuta la propiedad de presencia de la entidad.
		/*!
			\param e Entidad que modifica su estado.
		*/
		virtual void changedEnabled(Entity*e);


	/*********************************************************************\
	*	Métodos relacionados con colisiones entre entidades				  *
	\*********************************************************************/

		//! Devuelve una lista con todas las entidades del GameState que correspondan a un determinado tipo
		/*!
			\param type Tipo dela entidad.
		*/
		virtual vector<Entity*>* getType(std::string type);

		//! Comprueba si al posicionar la entidad en (x,y) colisiona con el mapa  y (semi)sólidos. No coloca la entidad.
		/*!
			\param x Coordenada x del mapa.
			\param y Coordenada y del mapa.
			\param e Entidad con la que se comprueba.
			\return Valor que representa si la entidad e colisiona con el mapa.
		*/
		virtual bool place_free(int x, int y, Entity* e);

		//! Comprueba si la posición (x,y) del mapa está libre de entidades y (semi)sólidos. No coloca la entidad
		/*!
			\param x Coordenada x del mapa.
			\param y Coordenada y del mapa.
			\return Representa si la posición(del mapa) está libre o no.
		*/
		virtual bool position_free(int x, int y);

		//! Comprueba si las entidades colisionan entre si.
		/*!
			\param a Primera entidad.
			\param b Segunda entidad.
			\return Valor booleano que determina si han colisionado o no.
		*/
		virtual bool collides(Entity* a, Entity* b);

		//! Devuelve la entidad con la que se colisiona al mover la entidad de entrada a (x,y).
		/*!
			\param x Coordenada x del mapa.
			\param y Coordenada y del mapa.
			\param e Entidad que movemos.
			\param type Tipo de colisión.
			\return La entidad con la que se encuentra al moverse.
		*/
		virtual Entity* place_meeting(int x, int y, Entity* e, std::string type);

		//! Devuelve una lista de entidades del tipo type que colisionan con la máscara dada.
		/*!
			\param mask Máscara de colisión.
			\param type Tipo de colisión.
			\return Lista de entidades que colisionan.
		*/
		virtual vector<Entity*>* enclosedEntities(Mask* mask, std::string type);

		//! Mueve la entidad de entrada a la posición más cercana posible a (x,y) sin colisionar.
		/*!
			\param x Coordenada x del mapa.
			\param y Coordenada y del mapa.
			\param e Entidad que se va a mover.
		*/
		virtual void moveToContact(int x, int y, Entity* e);
};

#endif
