#include "World.h"

// Constructora
World::World(int difficulty){
	// Asignamos dificultad
	gameDiff = difficulty;
}

// Destructora
World::~World(){}

// Setter Overworld
void World::setOverworld(Overworld* ow){
	overworld = ow;
}