#pragma once
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <string>
#include "Game.h"
#include "Mask.h"
#include "Graphic.h"

using namespace std;

//! Elemento del juego manejable por el motor.
/*!
	Entity representa cualquier elemento que tenga que actualizarse y renderizarse a lo largo de la vida del juego.
*/
class Entity
{
	private:
		void _update();
		bool place_free(int x, int y);
		bool position_free(int x, int y);
		Entity* place_meeting(int x, int y, string tipo);
		bool collides(Entity* other);

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
	
	//! Tipo propio de la entidad, para las máscaras
	string type;


	//! Inicia la entidad (constructora)
	/*!
		\param x coordenada x en que se crea la entidad
		\param y coordenada y en que se crea la entidad
		\param game puntero al juego
		\param world puntero al GameState al que pertenece
	*/
	Entity(int x, int y,Game* game, GameState* world);
	
	//! Destructora.
	~Entity();

	//! Destruye la entidad, indicándolo al GameState correspondiente.
	void instance_destroy();
	
	//! Activa la entidad
	void enable();
	
	//! Desactiva la entidad
	void disable();

	//! Establece la visibilidad de la entidad
	/*!
		\param visible visibilidad de la entidad
	*/
	void setVisible(bool visible);

	//! Comprueba si la entidad es visible
	/*!
		\return true si la entidad es visible, false si no lo es
	*/
	bool isRenderable();

	//! Congela la entidad
	void freeze();
	
	//! Descongela la entidad
	void unfreeze();
	
	//! Comprueba si la entidad está congelada
	/*!
		\return true si la entidad está congelada, false si no lo está
	*/
	bool isFrozen();

	//! Selecciona si la entidad recibe y produce eventos de colisión
	/*!
		\param collidable decide si puede o no recibir y producir eventos de colisión
	*/
	void setCollidable(bool collidable);

	//! Compruebla si la entidad puede recibir y producir eventos de colisión
	/*!
		\return true si la entidad puede recibir y producir eventos de colisión, false si no
	*/
	bool isCollidable();

	//! Comprueba el valor de un timer
	/*!
		\param number señala el timer del que se devolverá el valor
		\return el valor del timer seleccionado
	*/
	int getTimer(int number);

	//! Establece el valor, en steps, de uno de los timers
	/*!
		\param number selecciona el timer
		\param count selecciona el tiempo que le vamos a dar al timer
	*/
	void setTimer(int number,int count);

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
		\param other el otro elemento contra el que ha chocado la entidad.
	*/
	virtual void onCollision(CollisionPair other);

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
