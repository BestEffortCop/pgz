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
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <string>
#include "Game.h"
#include "Mask.h"
#include "Graphic.h"
#include "GameState.h"

using namespace std;

class Game;
class GameState;

//! Elemento del juego manejable por el motor.
/*!
	Entity representa cualquier elemento que tenga que actualizarse y renderizarse a lo largo de la vida del juego.
*/
class Entity
{
	friend class GameState;

	protected:
		void _update();
		bool place_free(int x, int y);
		bool position_free(int x, int y);
		Entity* place_meeting(int x, int y, string tipo);
		bool collides(Entity* other);
		void moveToContact(int x, int y);

	protected:
		Game* game;

	public:

	//! Posición sobre el eje x de la entidad
	int x; 
	
	//! Posición sobre el eje y de la entidad
	int y;
	
	//! Elemento de colisión de la entidad
	/*!
		Debe ser un descendiente de Mask.
		\sa Mask
	*/
	Mask* mask;
	
	//! Elemento de representación gráfica de la entidad
	/*!
		Debe ser un descendiente de Graphic.
	*/
	Graphic* graphic;
	
	//! GameState al que pertenece la entidad
	GameState* world;
	
	//! Profundidad de dibujo de la entidad
	/*!
		A mayor profundidad, antes se dibuja la entidad y más probabilidades
		hay de que la oculte otro elemento gráfico.
	*/
	int depth;
	
	//! Temporizadores propios de la entidad
	int timers[10];

	//! Flag de persistencia de la entidad.
	/*!
		Si está activado, la entidad no se destruirá al cambiar el GameState.
	*/
	bool persistent;
	
	//! Flag de activo de la entidad.
	/*!
		Si no está activado, la entidad no participa en el GameState,
		ni en cuanto a la parte de lógica ni en cuanto a la de dibujo.
	*/
	bool enabled;
	
	//! Flag que indica si la entidad puede colisionar con otras entidades.
	bool collidable;
	
	//! Flag de congelado de la entidad
	/*!
		Si está activado, la entidad no se actualiza, pero permite a
		otras interactuar con ella.
	*/
	bool frozen;
	
	//! Flag que indica si la entidad debe renderizarse en pantalla.
	bool visible;
	
	//! Flag que indica si la entidad representa un sólido del mapa.
	bool solid;

	//! Tipo propio de la entidad, para las máscaras
	string type;


	//! Inicia la entidad (constructora)
	/*!
		\param x coordenada x en que se crea la entidad
		\param y coordenada y en que se crea la entidad
		\param game puntero al juego
		\param world puntero al GameState al que pertenece
	*/
	Entity(int x, int y, Game* game, GameState* world);
	
	//! Destructora.
	virtual ~Entity();

	//! Destruye la entidad, indicándolo al GameState correspondiente.
	virtual void instance_destroy();
	
	//! Activa la entidad
	virtual void enable();
	
	//! Desactiva la entidad
	virtual void disable();

	//! Establece la visibilidad de la entidad
	/*!
		\param visible visibilidad de la entidad
	*/
	virtual void setVisible(bool visible);

	//! Comprueba si la entidad es visible
	/*!
		\return true si la entidad es visible, false si no lo es
	*/
	virtual bool isRenderable();

	//! Congela la entidad
	virtual void freeze();
	
	//! Descongela la entidad
	virtual void unfreeze();
	
	//! Comprueba si la entidad está congelada
	/*!
		\return true si la entidad está congelada, false si no lo está
	*/
	virtual bool isFrozen();

	//! Selecciona si la entidad recibe y produce eventos de colisión
	/*!
		\param collidable decide si puede o no recibir y producir eventos de colisión
	*/
	virtual void setCollidable(bool collidable);

	//! Compruebla si la entidad puede recibir y producir eventos de colisión
	/*!
		\return true si la entidad puede recibir y producir eventos de colisión, false si no
	*/
	virtual bool isCollidable();

	//! Comprueba el valor de un timer
	/*!
		\param number señala el timer del que se devolverá el valor
		\return el valor del timer seleccionado
	*/
	virtual int getTimer(int number);

	//! Establece el valor, en steps, de uno de los timers
	/*!
		\param number selecciona el timer
		\param count selecciona el tiempo que le vamos a dar al timer
	*/
	virtual void setTimer(int number,int count);

	//! Evento de Inicialización
	/*! Contendrá las acciones a realizar durante la inicialización. */
	virtual void onInit();

	//! Evento de actualización
	/*! Contendrá las acciones a realizar durante un paso del juego. */
	virtual void onStep();

	//! Evento de Renderizado
	/*! Acciones a realizar durante el render.
		Por defecto, mostrar el Graphic asociado a la entidad.
	*/
	virtual void onRender();

	//! Eventos de los Timers
	/*!
		Contendrá las acciones a realizar cuando se active un timer.
		\param timer indica que timer se activa
	*/
	virtual void onTimer(int timer);

	//! Evento de colisión
	/*!
		Contendrá las acciones a realizar cuando se produzca una colisión.
		\param other el par de colisión entre las máscaras, donde el primer campo se refiere a esta entidad y el segundo a la otra.
		\param e la entidad con la que colisiona
	*/
	virtual void onCollision(CollisionPair other, Entity* e);

	//! Evento de destrucción de la entidad
	/*! Contendrá las acciones a realizar cuando se destruya la entidad. */
	virtual void onDestroy();

	//! Evento personalizado.
	/*!
		Contendrá las acciones a realizar cuando ocurre un evento
		personalizado.
		\param event Código del evento personalizado.
	*/
	virtual void onCustomEvent(int event);

	//! Evento de inicio de paso del juego
	/*! Contendrá las acciones a realizar antes de comenzar
		el siguiente paso del juego. */
	virtual void onInitStep();

	//! Evento de final de paso del juego
	/*! Contendrá las acciones a realizar antes de finalizar
		un paso del juego. */
	virtual void onEndStep();

	//! Evento de inicio del GameState al que pertenece el juego.
	/*! Contendrá las acciones a realizar al iniciarse el GameState
		al que pertenece la entidad. */
	virtual void onInitWorld();

	//! Evento de final del GameState al que pertenece el juego.
	/*! Contendrá las acciones a realizar al finalizar el GameState
		al que pertenece la entidad. */
	virtual void onEndWorld();

};

#endif
