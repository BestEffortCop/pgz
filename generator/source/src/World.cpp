#include "World.h"

// Constructora
World::World(int difficulty){
	// Asignamos dificultad
	worldDiff = difficulty;
}

// Destructora
World::~World(){}

// Setter Overworld
void World::setOverworld(Overworld* ow){
	overworld = ow;
}

int World::getWorldDiff(){
	return worldDiff;
}