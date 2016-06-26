#include "missile.h"

// getter function
int missile::getSpeed() { return this->speed; }

// function that updates the missile every frame
void missile::update(SDL_Surface* gSurface, double delta) {
	
	// move the missile down and apply the modifier
	this->rect.y += static_cast<int>(speed * delta);

	return;

}

// function to initialize values for the missile
void missile::init(int x, int y, float speedModifier) {

	// initialize speed with random modifier
	this->speed = static_cast<int>(missileConstants::BASE_SPEED * speedModifier + std::rand() % 300);
	
	// initialize missile rect
	this->rect = { x, y, missileConstants::WIDTH, missileConstants::HEIGHT };
	
	// intialize sprite type
	type = MISSILE;

	return;

}