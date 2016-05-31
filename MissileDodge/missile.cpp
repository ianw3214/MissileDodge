#include "missile.h"

// function that updates the missile every frame
void missile::update(SDL_Surface* gSurface) {

	// move the missile down and apply the modifier
	this->rect.y += speed;

	// draw the image for this sprite
	drawImage(gSurface);

}

// function to initialize values for the missile
void missile::init(int x, int y) {

	// initialize speed
	this->speed = BASE_SPEED;

	// initialize missile rect
	this->rect = { x, y, MISSILE_WIDTH, MISSILE_HEIGHT };
	
	// intialize sprite type
	type = MISSILE;

	return;

}