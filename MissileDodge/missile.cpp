#include "missile.h"

// function that updates the missile every frame
void missile::update(SDL_Surface* gSurface) {

	// move the missile down and apply the modifier
	this->rect.y += speed;

	return;

}

// function to initialize values for the missile
void missile::init(int x, int y) {

	// initialize speed
	this->speed = missileConstants::BASE_SPEED;

	// initialize missile rect
	this->rect = { x, y, missileConstants::WIDTH, missileConstants::HEIGHT };
	
	// intialize sprite type
	type = MISSILE;

	return;

}