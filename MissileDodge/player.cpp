#include "player.h"

// getter functions
int player::getHealth() { return this->health; }
bool player::getInvincibility() { return this->invincible; }

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
		case SDLK_SPACE:
			// set the space down boolean to true
			spaceDown = true;
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
		case SDLK_SPACE:
			// set the space down boolean to false
			spaceDown = false;
			break;
		}
	}

}

// function that updates the player every frame
void player::update(SDL_Surface* gSurface, double delta) {

	// add to the players x coordinates if keys are pressed
	if (leftDown && !rightDown) {
		this->rect.x -= speed * delta;
		// make sure to leave a margin from the side
		if(rect.x < 10){
			this->rect.x = 10;
		}
	}
	if (rightDown && !leftDown) {
		this->rect.x += speed * delta;
		// leave a margin
		if (rect.x > (constants::SCREEN_WIDTH - playerConstants::WIDTH - 10)) {
			this->rect.x = constants::SCREEN_WIDTH - playerConstants::WIDTH - 10;
		}
	}
	
	// handle the jump for the player
	if (spaceDown) {
		// if the counter is 0, let the player jump
		if (jumpCounter == 0) {
			// set the ymove variable to the desired velocity
			yMove = playerConstants::BASE_JUMP_VELOCITY;
			// reset the jump counter
			jumpCounter = playerConstants::BASE_JUMP_TIME;
		}
	}

	// update the y coordinates of the player
	this->rect.y -= yMove*delta;
	// make sure it doesn't go beneath the ground
	if (this->rect.y > (constants::GROUND_LEVEL-playerConstants::HEIGHT)) {
		// set the y to the ground level
		this->rect.y = constants::GROUND_LEVEL - playerConstants::HEIGHT;
		// set ymove to 0
	}
	// apply gravity
	yMove -= constants::GRAVITY*delta;
	// decrement the jump counter
	if (jumpCounter>0) {
		jumpCounter--;
	}

	// update invincible counter
	if (invincibleCounter > 0) {
		invincibleCounter--;
		if (invincibleCounter == 0) {
			LOG("NOT INVINCIBLE");
			this->invincible = false;
		}
	}

	return;

}

// function that handles damage, returns false upon death
bool player::takeDamage(int dmg) {

	// boolean to return death state
	bool alive = true;

	// take damage if the player isn't invincible
	if(!invincible){
		// apply the damage to the health
		this->health -= dmg;

		// test if the player is alive
		if (health <= 0) {
			alive = false;
		}
	}

	// true if alive, false if dead
	return alive;

}

// function to clear the key inputs of player
void player::setKeysNone() {
	this->leftDown = false;
	this->rightDown = false;
}

// function that restores player health
void player::heal(int inp) {

	this->health += inp;

	// if the resultant health is higher than base health
	if (this->health > playerConstants::BASE_HEALTH) {
		// set the health to the max
		this->health = playerConstants::BASE_HEALTH;
	}

	return;

}

// function that turns the player invincible and sets the counter off
void player::turnInvincible() {
	this->invincible = true;
	this->invincibleCounter = boonConstants::DURATION;
	return;
}

// function to initialize values for the missile
void player::init(int x, int y) {

	// initialize player stats
	this->speed = playerConstants::BASE_SPEED;
	this->health = playerConstants::BASE_HEALTH;
	this->invincible = false;
	this->invincibleCounter = 0;
	// initialize jump counter
	jumpCounter = 0;
	// initialize player rect
	this->rect = { x, y, playerConstants::WIDTH, playerConstants::HEIGHT };

	// initialize sprite type
	type = PLAYER;

	return;

}