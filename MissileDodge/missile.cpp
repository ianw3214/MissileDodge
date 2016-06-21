#include "missile.h"

// function that updates the missile every frame
void missile::update(SDL_Surface* gSurface, double delta) {
	
	// move the missile down and apply the modifier
	this->rect.y += speed * delta;

	return;

}

// function to initialize values for the missile
void missile::init(int x, int y) {

	// initialize speed with random modifier
	this->speed = missileConstants::BASE_SPEED + std::rand() % 500;
	// LOG(this->speed);		DEBUG CODE

	// initialize missile rect
	this->rect = { x, y, missileConstants::WIDTH, missileConstants::HEIGHT };
	
	// intialize sprite type
	type = MISSILE;

	return;

}