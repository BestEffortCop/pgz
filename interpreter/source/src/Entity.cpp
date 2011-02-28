#include "Entity.h"

// Constructora y destructora

Entity::Entity(int x, int y, Game* game, GameState* world) {
	this->x = x;
	this->y = y;
	this->game = game;
	this->world = world;

	// Inicializa los timers a -1
	for (int i = 0; i < 10; i++)
		timers[i] = -1;

	// Valores por defecto de los flags
	persistent = false;
	visible = true;
	collidable = false;
	enabled = true;
	frozen = false;
	
	mask = NULL;
	graphic = NULL;
	depth = 0;
}

// Libera la memoria correspondiente a la Mask y al Graphic
Entity::~Entity() {
	if (mask != NULL) { delete mask; mask = NULL; }
	if (graphic != NULL) { delete graphic; graphic = NULL; }
}

// Métodos de la clase

void Entity::instance_destroy() {
	// Informa al GameState al que pertenece la clase para que elimine la entidad
	world->remove(this); 
	// Llama al evento correspondiente
	onDestroy();
}

// Métodos para cambiar/consultar los flags de la entidad

// Activa la entidad e informa a su gameState
void Entity::enable() { enabled = true; world->changedEnabled(this); }

// Desactiva la entidad e informa a su gameState
void Entity::disable() { enabled = true; world->changedEnabled(this); }

// Indica si la entidad debe ser renderizada o no e informa a su gameState
void Entity::setVisible(bool visible) { 
	this->visible = visible; 
	world->changedRenderable(this); 
}

// Comprueba si la entidad debe ser renderizada
bool Entity::isRenderable() { return visible; }

// Congela la entidad e informa a su gameState
void Entity::freeze() { frozen = true; world->changedEnabled(this); }

// Descongela la entidad e informa a su gameState
void Entity::unfreeze() { frozen = false; world->changedEnabled(this); }

// Comprueba si la entidad está o no congelada
bool Entity::isFrozen() { return frozen; }

// Determina si la entidad es o no atravesable por otras e informa a su gameState
void Entity::setCollidable(bool collidable) { 
	this->collidable = collidable; 
	if (world != NULL) world->changedCollidable(this);
}

// Comprueba si la entidad es o no atravesable por otras
bool Entity::isCollidable() { return collidable; }

// Métodos de los timers

// Obtiene el valor de un timer concreto en el momento actual
int Entity::getTimer(int number) { 
	// Si number está fuera de rango no se levanta excepción
	if (number >= 0 && number < 10)
		return timers[number];
}

// Establece el valor de un timer concreto
void Entity::setTimer(int number, int count) {
	// Si number está fuera de rango no se levanta excepción
	if (number >= 0 && number < 10)
		timers[number] = count;
}

// Eventos

void Entity::onInit() {}

void Entity::onStep() {}

// Manda renderizarse al gráfico de la entidad
void Entity::onRender() {
	if (graphic != NULL && enabled && visible)
		graphic->render(x, y);
}

void Entity::onTimer(int timer) {}

void Entity::onCollision(Mask* other) {}

void Entity::onDestroy() {}

void Entity::onCustomEvent(int event) {}

void Entity::onInitStep() {}

void Entity::onEndStep() {}

void Entity::onInitWorld() {}

void Entity::onEndWorld() {}

// Actualización del estado de la entidad
void Entity::_update() {
	// actualiza timers
	for (int i = 0; i < 10; i++)
		if (timers[i] > 0) 
			timers[i]--;
		else 
			if (timers[i] == 0) {
				timers[i] = -1;
				onTimer(i);
			}

	// Evento de actualización propio de la entidad
	onStep();

	// auto-maneja la máscara (actualizar posición)
	if (mask != NULL) {
		mask->x = x;
		mask->y = y;
	}
	
	// actualiza gráfico
	if (graphic != NULL && visible && enabled)
		graphic->update();
}

// Encapsulado de los métodos de colisión del GameState

bool Entity::place_free(int x, int y) {
	if (world != NULL) return world->place_free(x, y, this);
}

bool Entity::position_free(int x, int y) {
	if (world != NULL) return world->position_free(x, y);
}

Entity* Entity::place_meeting(int x, int y, string tipo) {
	if (world != NULL) return world->place_meeting(x, y, this, tipo);
}

bool Entity::collides(Entity* other) {
	if (world != NULL) return world->collides(this, other);
}