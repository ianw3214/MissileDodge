#include "player.h"

// TODO	
// create an velocity tracker for the hero movement
// set a speed constant for hero movement
// set booleans to see if left/right keys are held down

//function that calls for every update
void player::eventHandler(SDL_Event e) {

	if (e.type == SDL_KEYDOWN) {
		// cases for each key press
		switch (e.key.keysym.sym) {
		case SDLK_a:		// A key
		case SDLK_LEFT:		// left key
			std::cout << "LEFT DOWN" << std::endl;
			// set the left down boolean to true
			leftDown = true;
			break;
		case SDLK_d:		// D key
		case SDLK_RIGHT:	// right key
			std::cout << "RIGHT DOWN" << std::endl;
			// set the right down boolean to true
			rightDown = true;
			break;
		}
	}
	// if the user releases a key
	else if (e.type == SDL_KEYUP) {
		// cases for each key press
		switch (e.key.keysym.sym) {
		case SDLK_a:		// A key
		case SDLK_LEFT:		// left key
			// set the left down boolean to false
			leftDown = false;
			break;
		case SDLK_d:		// D key
		case SDLK_RIGHT:	// right key
			// set the right down boolean to false
			rightDown = false;
			break;
		}
	}

}

// function that updates the player every frame
void player::update(SDL_Surface* gSurface) {

	// add to the players x coordinates if keys are pressed
	if (leftDown && !rightDown) {
		this->x -= speed;
	}
	if (rightDown && !leftDown) {
		this->x += speed;
	}
	
	// draw the image for this sprite
	drawImage(gSurface);

}