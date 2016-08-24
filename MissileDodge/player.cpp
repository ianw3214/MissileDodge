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
		// update animation state
		cState = LEFT;
		this->rect.x -= static_cast<int>(speed * delta);
		// make sure to leave a margin from the side
		if(rect.x < 10){
			this->rect.x = 10;
		}
	}
	if (rightDown && !leftDown) {
		// update animation state
		cState = RIGHT;
		this->rect.x += static_cast<int>(speed * delta);
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
			jumpCounter = playerConstants::BASE_JUMP_COOLDOWN;
		}
	}

	// update the y coordinates of the player
	this->rect.y -= static_cast<int>(yMove * delta);
	// make sure it doesn't go beneath the ground
	if (this->rect.y > (constants::GROUND_LEVEL-playerConstants::HEIGHT)) {
		// set the y to the ground level
		this->rect.y = constants::GROUND_LEVEL - playerConstants::HEIGHT;
		// set ymove to 0
	}
	// apply gravity
	yMove -= static_cast<int>(constants::GRAVITY * delta);
	// decrement the jump counter
	if (jumpCounter>0) {
		jumpCounter--;
	}

	// update shadow position
	if (cState == LEFT) {
		shadow->setPos(this->rect.x, (constants::GROUND_LEVEL-6));
	}
	else if (cState == RIGHT) {
		shadow->setPos((this->rect.x+8), (constants::GROUND_LEVEL-6));
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
void player::boonHandler(boonTypes type) {

	switch (type) {
	case HEALTH: {
		// call the heal function with a default of 2 health
		heal(boonConstants::BASE_HEAL);
	} break;

	case INVINCIBLE: {
		// turn the hero invincible and set a timer to revert to normal
		this->invincible = true;
		LOG("INVINCIBLE");
		SDL_TimerID temp = SDL_AddTimer( boonConstants::DURATION, boon_invincible, this);
	} break;

	case SPEED: {
		// turn the hero invincible and set a timer to revert to normal
		this->speed *= boonConstants::BASE_SPEED_MULTIPLIER;
		LOG(speed);
		SDL_TimerID temp = SDL_AddTimer(boonConstants::DURATION, boon_speed, this);
	} break;

	}

	return;
}

// function that makes the player slower from a gas missile
void player::slowDown() {

	this->speed *= missileConstants::gasMissile::SPEED_MULTIPLIER;
	SDL_TimerID temp = SDL_AddTimer(missileConstants::gasMissile::DURATION, condition_slow, this);

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

	// initialize copy rectangles dimensions
	SS_rect.w = playerConstants::WIDTH;
	SS_rect.h = playerConstants::HEIGHT;
	// initialize state of player animation to left
	cState = LEFT;

	// initialize sprite type
	type = PLAYER;

	// initialize a shadow for the player
	shadow = new sprite(this->rect.x, (constants::GROUND_LEVEL-6), "assets/SHADOW.png");

	// start sprite update timer
	spriteUpdateTimer = SDL_AddTimer(30, spriteUpdate, this);

	return;

}

// override the render function from sprite class
bool player::render(SDL_Surface * gSurface) {

	// render the player shadow first to put it behind player
	shadow->render(gSurface);

	// success flag
	bool success = true;

	// if the function failed
	if (SDL_BlitSurface(img, &SS_rect, gSurface, &rect) < 0) {
		// output the error
		std::cout << "Image unable to blit to surface, SDL_image ERROR : " << IMG_GetError() << std::endl;
		success = false;
	}

	// render boons on top of player sprite
	if (invincible) {
		sprite * temp = new sprite(rect.x + 50, rect.y-10, "assets/INVINCIBLE_EFFECT.png");
		temp->render(gSurface);
	}
	if (speed > playerConstants::BASE_SPEED) {
		sprite * temp = new sprite(rect.x-5, rect.y-10, "assets/SPEED_EFFECT.png");
		temp->render(gSurface);
	}

	// return the success boolean
	return success;

}

// timer functions
Uint32 player::boon_invincible(Uint32 interval, void * ptr) {

	player * temp = (player*)ptr;
	temp->invincible = false;

	return 0;

}

Uint32 player::boon_speed(Uint32 interval, void * ptr) {

	player * temp = (player*)ptr;
	temp->speed = playerConstants::BASE_SPEED;

	return 0;

}

Uint32 player::condition_slow(Uint32 interval, void * ptr) {

	player * temp = (player*)ptr;
	temp->speed = playerConstants::BASE_SPEED;

	return 0;
}

Uint32 player::spriteUpdate(Uint32 interval, void * ptr) {
	// get a reference to the player
	player * temp = (player*)ptr;

	// set the animation frame depending on the state of the hero
	switch (temp->cState) {
	case LEFT: {
		temp->SS_rect.x = 0;
		temp->SS_rect.y = 0;
	} break;
	case RIGHT: {
		temp->SS_rect.x = playerConstants::WIDTH;
		temp->SS_rect.y = 0;
	} break;
	}

	// update again at the same interval
	return interval;
}

// wait for all the player timers to finish to avoid multithreading problems
void player::waitTimer() {

	// player animation state update timer
	SDL_RemoveTimer(spriteUpdateTimer);

	return;

}