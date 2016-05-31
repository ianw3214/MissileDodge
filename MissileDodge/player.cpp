#include "player.h"

// getter functions
int player::getHealth() { return this->health; }

//function that calls for every update
void player::eventHandler(SDL_Event e) {

	if (e.type == SDL_KEYDOWN) {
		// cases for each key press
		switch (e.key.keysym.sym) {
		case SDLK_a:		// A key
		case SDLK_LEFT:		// left key
			// set the left down boolean to true
			leftDown = true;
			break;
		case SDLK_d:		// D key
		case SDLK_RIGHT:	// right key
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
		this->rect.x -= speed;
	}
	if (rightDown && !leftDown) {
		this->rect.x += speed;
	}
	
	// draw the image for this sprite
	drawImage(gSurface);

}

// function that handles damage, returns false upon death
bool player::takeDamage(int dmg) {

	// boolean to return death state
	bool alive = true;

	// apply the damage to the health
	this->health -= dmg;

	// test if the player is alive
	if (health < 0) {
		// change the return boolean if not
		alive = false;
	}

	// return the life state boolean
	return alive;

}

// function to initialize values for the missile
void player::init(int x, int y) {

	// initialize speed
	this->speed = BASE_SPEED;

	// initialize health
	this->health = BASE_HEALTH;

	// initialize missile rect
	this->rect = { x, y, PLAYER_WIDTH, PLAYER_HEIGHT };

	// initialize sprite type
	type = PLAYER;

	return;

}