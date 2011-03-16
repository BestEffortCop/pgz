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
        void init();

		// Añade la entidad a la lista lsólo si no existe en ella
		bool add_single(list<Entity*>* l, Entity* ent);

        // Añade una entidad al mundo de forma directa
        bool _add(Entity* e);
        // Borra una entidad del mundo de forma directa
        bool _remove(Entity* e);

        // Comprueba si una máscara colisiona o no con los elementos del mapa
        bool collide_mask(Mask* m);

		// Comprueba si una entidad colisiona o no con los elementos del mapa
		bool collide_entity(Entity* e);

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
		~GameState();

		//! Permite al usuario implementar acciones que se realicen cuando el estado pase a ser el actual.
		void onInit();

		//! Permite al usuario implementar acciones que se realicen cuando el estado deje de ser el actual.
		void onEnd();

		//! Actualiza por defecto las entidades y comprueba las colisiones.
		void _update();

		//! El usuario puede sobreescribir según sus necesidades el método _update().
		/*!
			\sa _update();
		*/
		virtual void onStep();

		//! Permite al usuario pintar lo que desee por debajo de los elementos del gameState.
		virtual void renderBG();

		//! Pinta todas las entidades renderizables del gameState.
		void onRender();

		//! Permite al usuario pintar lo que desee por encima de todos los elementos del gameState.
		virtual void renderFG();

		//! Añade un mapa al juego. Si existe ya uno, lo sustituye.
		/*!
			\param map Mapa que queremos poner.
		*/
		void addMap(Map* map);

		//! Borra todas las entidades que hay en GameState.
		void removeAll();

		/*********************************************************************\
		*	Métodos que tienen efecto al final del tick						  *
		\*********************************************************************/

		//! Añade una entidad al GameState.
		/*!
			\param e Entidad a añadir.
			\return True si la entidad se ha añadido correctamente, falso si ya existía.
		*/
		bool add(Entity* e);

		//! Elimina una entidad de las existentes en GameState.
		/*!
			\param e Entidad que vamos a eliminar.
			\return True si la entidad se ha borrado correctamente, falso si no existía.
		*/
		bool remove(Entity* e);

		//! Añade a GameState las entidades que contiene la lista de entrada.
		/*!
			\param l Lista de entidades a incorporar.
		*/
		void addList(vector<Entity*>* l);

		//! Borra las entidades de GameState que están en la lista de entrada.
		/*!
			\param l Lista de entidades a eleminar.
		*/
		void removeList(vector<Entity*>* l);

		//! Conmuta la propiedad renderable de la entidad.
		/*!
			\param e Entidad que modifica su estado.
		*/
		void changedRenderable(Entity* e);

		//! Conmuta la propiedad de colisión de la entidad.
		/*!
			\param e Entidad que modifica su estado.
		*/
		void changedCollidable(Entity*e);

		//! Conmuta la propiedad de presencia de la entidad.
		/*!
			\param e Entidad que modifica su estado.
		*/
		void changedEnabled(Entity*e);


	/*********************************************************************\
	*	Métodos relacionados con colisiones entre entidades				  *
	\*********************************************************************/

		//! Devuelve una lista con todas las entidades del GameState que correspondan a un determinado tipo
		/*!
			\param type Tipo dela entidad.
		*/
		vector<Entity*>* getType(std::string type);

		//! Comprueba si al posicionar la entidad en (x,y) colisiona con el mapa  y (semi)sólidos. No coloca la entidad.
		/*!
			\param x Coordenada x del mapa.
			\param y Coordenada y del mapa.
			\param e Entidad con la que se comprueba.
			\return Valor que representa si la entidad e colisiona con el mapa.
		*/
		bool place_free(int x, int y, Entity* e);

		//! Comprueba si la posición (x,y) del mapa está libre de entidades y (semi)sólidos. No coloca la entidad
		/*!
			\param x Coordenada x del mapa.
			\param y Coordenada y del mapa.
			\return Representa si la posición(del mapa) está libre o no.
		*/
		bool position_free(int x, int y);

		//! Comprueba si las entidades colisionan entre si.
		/*!
			\param a Primera entidad.
			\param b Segunda entidad.
			\return Valor booleano que determina si han colisionado o no.
		*/
		bool collides(Entity* a, Entity* b);

		//! Devuelve la entidad con la que se colisiona al mover la entidad de entrada a (x,y).
		/*!
			\param x Coordenada x del mapa.
			\param y Coordenada y del mapa.
			\param e Entidad que movemos.
			\param type Tipo de colisión.
			\return La entidad con la que se encuentra al moverse.
		*/
		Entity* place_meeting(int x, int y, Entity* e, std::string type);

		//! Devuelve una lista de entidades del tipo type que colisionan con la máscara dada.
		/*!
			\param mask Máscara de colisión.
			\param type Tipo de colisión.
			\return Lista de entidades que colisionan.
		*/
		vector<Entity*>* enclosedEntities(Mask* mask, std::string type);

		//! Mueve la entidad de entrada a la posición más cercana posible a (x,y) sin colisionar.
		/*!
			\param x Coordenada x del mapa.
			\param y Coordenada y del mapa.
			\param e Entidad que se va a mover.
		*/
		void moveToContact(int x, int y, Entity* e);

};

#endif
