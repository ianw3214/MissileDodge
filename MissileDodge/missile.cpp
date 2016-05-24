#include "missile.h"

// function that updates the player every frame
void missile::update(SDL_Surface* gSurface) {

	// move the missile down and apply the modifier
	this->y += speed;

	// draw the image for this sprite
	drawImage(gSurface);

}

// function to initialize values for the missile
void missile::init() {

	// initialize speed
	this->speed = 10;

	return;

}